#include "SettingsScreen.h"
#include "../Application.h"

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

void SettingsScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		std::cout << IO_DATA::chooseOpenFile() << std::endl;
		app->closeCurrentScreen(); 
		break;

	default:
		break;
	}
}

void SettingsScreen::update(float dt) {
	updateGui(dt);
}

void SettingsScreen::render(sf::RenderTarget& window) {
	window.clear(sf::Color::Red);
	renderGui(window);
}