#include "HomeScreen.h"
#include "../../Application.h"

HomeScreen::HomeScreen() {
}

HomeScreen::~HomeScreen() {
}

void HomeScreen::init() {
	m_logo.setTexture(ResourceManager::getLogoTexture());

	m_worldsButton.reloadResources();
	m_worldsButton.setBorderWidth(4);
	m_worldsButton.setText("Worlds");
	m_worldsButton.setFunction([this]() {
		Application::instance().openScreen(ScreenID::WORLDSELECTION);
		});
	addGuiElement(&m_worldsButton);

	m_settingsButton.reloadResources();
	m_settingsButton.setBorderWidth(4);
	m_settingsButton.setText("Settings");
	m_settingsButton.setFunction([this]() {
		std::cout << "settings" << std::endl;
		});
	addGuiElement(&m_settingsButton);

	m_exitButton.reloadResources();
	m_exitButton.setBorderWidth(4);
	m_exitButton.setText("Exit");
	m_exitButton.setFunction([this]() {
		std::cout << "Exit" << std::endl;
		Application::instance().close();
		});
	addGuiElement(&m_exitButton);


	reloadGuiResources();
	onResize();
}

void HomeScreen::onResize() {
	sf::Vector2f buttonSize(200.0f, 60.0f);
	sf::Vector2i windowSize = Application::instance().getWindowSize();
	sf::Vector2f buttonPos = static_cast<sf::Vector2f>(Application::instance().getWindowSize()) / 2.0f - buttonSize / 2.0f;
	float padding = 10.0f;

	//logo
	float logoProp = static_cast<float>(m_logo.getTexture()->getSize().x) / static_cast<float>(m_logo.getTexture()->getSize().y);
	sf::Vector2f logoSize(600, 600 / logoProp);
	m_logo.setSize(logoSize);
	m_logo.setPosition((windowSize.x - logoSize.x) / 2, buttonPos.y - logoSize.y - 50);

	// buttons under logo
	m_worldsButton.setPosition(buttonPos);
	m_worldsButton.setSize(buttonSize);
	buttonPos.y += buttonSize.y + padding;

	m_settingsButton.setPosition(buttonPos);
	m_settingsButton.setSize(buttonSize);
	buttonPos.y += buttonSize.y + padding;

	m_exitButton.setPosition(buttonPos);
	m_exitButton.setSize(buttonSize);
	buttonPos.y += buttonSize.y + padding;

}

void HomeScreen::onClosing() {
}

void HomeScreen::onSwitch() {
	Screen::onSwitch();
}

bool HomeScreen::handleEvent(sf::Event& sfEvent) {
	if (handleGuiEvent(sfEvent))
		return true;

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		break;

	default:
		break;
	}

	return false;
}

void HomeScreen::update(float dt) {
	updateGui(dt);
}

void HomeScreen::render(sf::RenderTarget& window) {
	window.clear();

	window.draw(m_logo);
	renderGui(window);

	//draw debug lines every 100 pixels
	if (true) {
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(255, 255, 255, 50));

		rect.setSize(sf::Vector2f(1, window.getSize().y));
		for (int x = 0; x < window.getSize().x; x += 100) {
			rect.setPosition(x, 0);
			window.draw(rect);
		}

		rect.setSize(sf::Vector2f(window.getSize().x, 1));
		for (int y = 0; y < window.getSize().y; y += 100) {
			rect.setPosition(0, y);
			window.draw(rect);
		}
	}
}