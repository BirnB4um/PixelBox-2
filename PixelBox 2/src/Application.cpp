#include "Application.h"

Application* Application::currentInstance = nullptr;
sf::Vector2i Application::mousePos = sf::Vector2i(0, 0);

Application::Application() {
	currentInstance = this;

	m_shouldClose = false;

	// load resources
	if (!loadResources()) {
		throw std::runtime_error("Error loading resources");
	}

	m_allScreens.push_back(&m_homescreen);
	m_allScreens.push_back(&m_worldselectionscreen);
	m_allScreens.push_back(&m_settingsscreen);

	Screen::app = this;
	m_homescreen.init();
	m_settingsscreen.init();
	m_worldselectionscreen.init();
	openScreen(ScreenID::HOME);

	createWindow(800, 600, false, 60, "PixelBox 2");

	ImGui::SFML::Init(m_window);
}

Application::~Application() {
	ImGui::SFML::Shutdown();
}

ResourceManager& Application::getResourceManager() {
	return m_resourceManager;
}

bool Application::loadResources() {
	if (!m_resourceManager.loadResources()) {
		return false;
	}

	GuiElement::setTexture(m_resourceManager.getGuiTexture());

	return true;
}

void Application::createWindow(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	m_windowWidth = width;
	m_windowHeight = height;
	m_fps = fps;
	m_fullscreen = fullscreen;
	m_title = title;

	if (fullscreen) {
		m_window.create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen, settings);
	}
	else {
		m_windowedWidth = width;
		m_windowedHeight = height;
		m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Resize, settings);
	}
	m_window.setFramerateLimit(fps);
	m_window.setVerticalSyncEnabled(vsync);

	onResize();
}

void Application::closeCurrentScreen() {
	if (m_openScreens.size() > 1)
		m_openScreens.pop_back();

	m_currentScreen = m_openScreens.back();
}

void Application::openScreen(ScreenID id) {
	m_openScreens.push_back(m_allScreens[static_cast<int>(id)]);
	m_currentScreen = m_openScreens.back();
}

void Application::onClosing() {
	for (Screen* screen : m_allScreens) {
		screen->onClosing();
	}

	m_window.close();
}

void Application::onResize() {
	m_windowWidth = m_window.getSize().x;
	m_windowHeight = m_window.getSize().y;
	if (!m_fullscreen) {
		m_windowedWidth = m_windowWidth;
		m_windowedHeight = m_windowHeight;
	}
	normalView.setSize(m_windowWidth, m_windowHeight);
	normalView.setCenter(m_windowWidth / 2, m_windowHeight / 2);

	for (Screen* screen : m_allScreens) {
		screen->onResize();
	}
}

sf::Vector2i Application::getWindowSize() {
	return sf::Vector2i(m_windowWidth, m_windowHeight);
}

void Application::close() {
	m_shouldClose = true;
}

void Application::handleEvents() {
	while (m_window.pollEvent(m_sfEvent)) {
		ImGui::SFML::ProcessEvent(m_window, m_sfEvent);

		switch (m_sfEvent.type)
		{
		case sf::Event::GainedFocus:
			break;

		case sf::Event::LostFocus:
			break;

		case sf::Event::Closed:
			onClosing();
			break;

		case sf::Event::Resized:
			onResize();
			break;

		case sf::Event::KeyPressed:

			// toggle fullscreen
			if (m_sfEvent.key.code == sf::Keyboard::F10) {
				m_fullscreen = !m_fullscreen;
				createWindow(m_windowedWidth, m_windowedHeight, m_fullscreen, m_fps, m_title);
			}

			break;

		case sf::Event::MouseMoved:
			mousePos = sf::Mouse::getPosition(m_window);
			break;

		default:
			break;
		}

		//if mouse is captured by imgui, don't handle events
		if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
			continue;

		m_currentScreen->handleEvent(m_sfEvent);
	}
}

void Application::update() {
	ImGui::SFML::Update(m_window, m_deltaTime);

	ImGui::Begin("gui");
	float scale = GuiElement::getGuiScale();
	if (ImGui::SliderFloat("gui scale", &scale, 0.1f, 2.0f)) {
		GuiElement::setGuiScale(scale);
		onResize();
	}
	ImGui::End();

	m_currentScreen->update(m_deltaTime.asSeconds());
}

void Application::draw() {
	m_window.clear();
	m_window.setView(normalView);

	m_currentScreen->render(m_window);

	ImGui::SFML::Render(m_window);

	m_window.display();
}

void Application::run() {
	while (m_window.isOpen())
	{
		m_deltaTime = m_deltaClock.restart();

		handleEvents();

		update();

		draw();

		if (m_shouldClose)
			onClosing();
	}
}