#include "SimulationScreen.h"
#include "../../Application.h"

SimulationScreen::SimulationScreen() {
	m_world = nullptr;
	m_zoomLevel = 1.0f;
	m_targetZoomLevel = 1.0f;
	m_pixelSprite.setPosition(0, 0);
	m_isSimulationPaused = true;
	m_stopRenderingThread = false;
	m_stopRenderingThread = false;
	m_boardGrabbed = false;
}

SimulationScreen::~SimulationScreen() {
}

void SimulationScreen::init() {
}

void SimulationScreen::onResize() {
}

void SimulationScreen::onClosing() {
	stopSimulationThread();
	stopRenderingThread();
}

void SimulationScreen::onSwitch() {
	Screen::onSwitch();
}

bool SimulationScreen::handleEvent(sf::Event& sfEvent) {
	if (handleGuiEvent(sfEvent))
		return true;

	switch (sfEvent.type)
	{
	case sf::Event::KeyPressed:
		break;

	case sf::Event::KeyReleased:
		if (sfEvent.key.code == sf::Keyboard::Space) { // (un-)pause simulation
			m_isSimulationPaused = !m_isSimulationPaused;
			return true;
		}
		else if (sfEvent.key.code == sf::Keyboard::Escape) {
			stopRenderingThread();
			stopSimulationThread();
			deleteWorld();
			Application::instance().closeCurrentScreen();
			return true;
		}
		else if (sfEvent.key.code == sf::Keyboard::Num0) {
			resetView();
			return true;
		}
		break;

	case sf::Event::MouseWheelScrolled:
		{
			float delta = sfEvent.mouseWheelScroll.delta; // up = 1 ; down = -1
			float zoomAmount = delta > 0 ? 1.0f/0.8f : delta < 0 ? 0.8f : 0.0f;
			m_targetZoomLevel = std::max(0.2f, std::min(2000.0f, m_targetZoomLevel * zoomAmount));

			
			//FIXME: zooming in on mouse works, but the animation is not direct because zoomLevel and center approximate
			// their respective target independently
			
			//sf::Vector2f originalMousePos = getMouseWorldPos();
			//sf::Vector2f diff = originalMousePos - m_targetViewCenter;
			//m_targetViewCenter = originalMousePos - diff / zoomAmount;

			return true;
		}

		break;


	case sf::Event::MouseButtonPressed:
		if (sfEvent.mouseButton.button == sf::Mouse::Middle) {
			m_startGrabbedMousePos = Application::mousePos;
			m_startGrabbedViewCenter = m_targetViewCenter;
			m_boardGrabbed = true;
			return true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (sfEvent.mouseButton.button == sf::Mouse::Middle) {
			m_boardGrabbed = false;
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}

void SimulationScreen::update(float dt) {
	updateGui(dt);

	updateView(dt);
}

void SimulationScreen::render(sf::RenderTarget& window) {
	window.clear();

	window.setView(m_pixelView);
	window.draw(m_pixelSprite, ResourceManager::getPixelShader());
	window.setView(Application::normalView);

	renderGui(window);
}

void SimulationScreen::setWorld(World* world) {
	stopSimulationThread();
	stopRenderingThread();

	deleteWorld();
	m_world = world;
	m_pixelTexture.create(world->getMetaData().width, world->getMetaData().height);
	m_pixelSprite.setTexture(m_pixelTexture, true);
	resetView();
	m_zoomLevel = 1.0f;
	m_pixelView.setCenter(m_targetViewCenter);
	updateView(0.0f);
	m_isSimulationPaused = false;
	m_msPerTick = 100.0;
	m_msPerFrame = 25.0;
	m_boardGrabbed = false;

	//set shader texture uniforms
	ResourceManager::getPixelShader()->setUniform("worldSize", sf::Vector2f(world->getMetaData().width, world->getMetaData().height));

	startSimulationThread();
	startRenderingThread();
}

void SimulationScreen::resetView() {
	m_targetZoomLevel = 1;
	m_targetViewCenter = static_cast<sf::Vector2f>(m_pixelTexture.getSize()) / 2.0f;
}

void SimulationScreen::updateView(float dt) {

	//move view with keys
	float moveSpeed = dt * (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 3000.0f : 800.0f) / m_zoomLevel;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_targetViewCenter.y -= moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_targetViewCenter.y += moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_targetViewCenter.x -= moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_targetViewCenter.x += moveSpeed;
	}

	//move view with mouse
	if (m_boardGrabbed) {
		m_targetViewCenter = m_startGrabbedViewCenter + static_cast<sf::Vector2f>(m_startGrabbedMousePos - Application::mousePos) / m_zoomLevel;
	}


	//update view center
	sf::Vector2f dCenter = m_targetViewCenter - m_pixelView.getCenter();
	if (Utils::getLength(dCenter) < 1.0f / m_zoomLevel) {
		m_pixelView.setCenter(m_targetViewCenter);
	}
	else {
		m_pixelView.setCenter(m_pixelView.getCenter() + dCenter * dt * 20.0f);
	}

	//update zoom level
	float dZoom = m_targetZoomLevel - m_zoomLevel;
	if (std::abs(dZoom) < 0.001f) {
		m_zoomLevel = m_targetZoomLevel;
	}
	else {
		m_zoomLevel += dZoom * dt * 10.0f;
	}

	//float a = -(std::log10(m_zoomLevel) / std::log10(0.5));
	//float b = -(std::log10(m_targetZoomLevel) / std::log10(0.5));
	//float dZoom = (b - a) * 0.3f;
	//a += dZoom;
	//m_zoomLevel = std::pow(0.5, -a);

	m_pixelView.setSize(static_cast<sf::Vector2f>(Application::instance().getWindowSize()) / m_zoomLevel);

	//update shader uniforms
	ResourceManager::getPixelShader()->setUniform("zoomLevel", m_zoomLevel);
}

void SimulationScreen::th_simulationLoop() {
	Timer timer;
	int waitTime;

	while (!m_stopSimulationThread) {
		{
			std::lock_guard<std::mutex> lock(m_bufferMutex);

			timer.start();

			if (!m_isSimulationPaused) {
				m_world->tick();
			}

			timer.stop();
		}

		//wait for next tick
		waitTime = static_cast<int>(std::max(0.0, m_msPerTick - timer.getDuration()));
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	}
}

void SimulationScreen::th_renderingLoop() {
	Timer timer;
	int waitTime;
	bool updateTexture;

	while (!m_stopRenderingThread) {
		//process updates
		{
			std::lock_guard<std::mutex> lock(m_bufferMutex);

			timer.start();

			updateTexture = m_world->renderBufferHasChanges();
			if (updateTexture) {
				m_world->updateRenderBuffer();
			}

			timer.stop();
		}

		//upload to GPU
		timer.start();
		if (updateTexture) {
			m_pixelTexture.update(m_world->getRenderBuffer());
		}
		timer.stop();

		//wait for next tick
		waitTime = static_cast<int>(std::max(0.0, m_msPerFrame - timer.getDuration()));
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	}
}

void SimulationScreen::startSimulationThread() {
	stopSimulationThread();
	m_stopSimulationThread = false;
	m_simulationThread = std::thread(&SimulationScreen::th_simulationLoop, this);
}

void SimulationScreen::stopSimulationThread() {
	m_stopSimulationThread = true;
	if (m_simulationThread.joinable())
		m_simulationThread.join();
}

void SimulationScreen::startRenderingThread() {
	stopRenderingThread();
	m_stopRenderingThread = false;
	m_renderingThread = std::thread(&SimulationScreen::th_renderingLoop, this);
}

void SimulationScreen::stopRenderingThread() {
	m_stopRenderingThread = true;
	if (m_renderingThread.joinable())
		m_renderingThread.join();
}

sf::Vector2f SimulationScreen::getMouseWorldPos() {
	return m_pixelView.getCenter() + static_cast<sf::Vector2f>(Application::mousePos - Application::instance().getWindowSize() / 2) / m_zoomLevel;
}

void SimulationScreen::deleteWorld() {
	delete m_world;
	m_world = nullptr;
}