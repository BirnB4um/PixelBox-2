#include "SettingsScreen.h"
#include "../../Application.h"

SettingsScreen::SettingsScreen() {
}

SettingsScreen::~SettingsScreen() {
}

void SettingsScreen::init() {
}

void SettingsScreen::onResize() {
}

void SettingsScreen::onClosing() {
}

void SettingsScreen::onSwitch() {
	Screen::onSwitch();
}

bool SettingsScreen::handleEvent(sf::Event& sfEvent) {
	if(handleGuiEvent(sfEvent))
		return true;

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		//std::cout << IO_DATA::chooseOpenFile() << std::endl;
		Application::instance().closeCurrentScreen();
		break;

	default:
		break;
	}

	return false;
}

void SettingsScreen::update(float dt) {
	updateGui(dt);
}

void SettingsScreen::render(sf::RenderTarget& window) {
	window.clear(sf::Color::Red);
	renderGui(window);
}