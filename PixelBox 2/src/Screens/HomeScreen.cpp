#include "HomeScreen.h"
#include "../Application.h"

HomeScreen::HomeScreen() {
}

HomeScreen::~HomeScreen() {
}

void HomeScreen::init() {

	m_button.setFont(app->getResourceManager().getPixelFont());
	m_button.setText("Test");
	m_button.setBounds(100, 100, 200, 120);
	m_button.setFunction([this]() {
		std::cout << "Button pressed" << std::endl;
		});
	m_guiElements.push_back(&m_button);
}

void HomeScreen::onResize() {
}

void HomeScreen::onClosing() {
}

void HomeScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		//app->openScreen(ScreenID::SETTINGS);
		break;

	default:
		break;
	}
}

void HomeScreen::update(float dt) {
	updateGui(dt);
}

void HomeScreen::render(sf::RenderTarget& window) {
	window.clear();
	renderGui(window);
}