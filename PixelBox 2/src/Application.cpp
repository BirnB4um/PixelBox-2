#include "Application.h"
#include "ResourceManager.h"

sf::Vector2i Application::mousePos = sf::Vector2i(0, 0);
sf::View Application::normalView = sf::View(sf::FloatRect(0, 0, 1, 1));

Application& Application::instance() {
	static Application app;
	return app;
}

Application::Application() {

}

void Application::init() {
	m_shouldClose = false;

	// load resources
	if (!ResourceManager::loadResources()) {
		throw std::runtime_error("Error loading resources");
	}

	createWindow(1200, 800, false, 60, "PixelBox 2", true);

	m_allScreens.push_back(&homeScreen);
	m_allScreens.push_back(&settingsScreen);
	m_allScreens.push_back(&worldSelectionScreen);
	m_allScreens.push_back(&worldCreationScreen);
	m_allScreens.push_back(&simulationScreen);

	for (Screen* screen : m_allScreens) {
		screen->init();
		screen->reloadGuiResources();
		screen->onResize();
	}
	openScreen(ScreenID::HOME);
}


Application::~Application() {

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

	currentScreen = m_openScreens.back();
	currentScreen->onSwitch();
}

void Application::openScreen(ScreenID id) {
	m_openScreens.push_back(m_allScreens[static_cast<int>(id)]);
	currentScreen = m_openScreens.back();
	currentScreen->onSwitch();
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
	normalView.setCenter(static_cast<float>(m_windowWidth) / 2.0f, static_cast<float>(m_windowHeight) / 2.0f);

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

		switch (m_sfEvent.type)
		{
		case sf::Event::GainedFocus:
			m_window.setFramerateLimit(m_fps);
			break;

		case sf::Event::LostFocus:
			m_window.setFramerateLimit(20);
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

		currentScreen->handleEvent(m_sfEvent);
	}
}

void Application::update() {
	currentScreen->update(m_deltaTime.asSeconds());
}

void Application::draw() {
	m_window.clear();
	m_window.setView(normalView);

	currentScreen->render(m_window);

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

