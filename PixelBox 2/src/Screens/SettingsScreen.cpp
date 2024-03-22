#include "SettingsScreen.h"
#include "../Application.h"

SettingsScreen::SettingsScreen() {

}

SettingsScreen::~SettingsScreen() {

}

void SettingsScreen::init() {

}

void SettingsScreen::run() {

}

void SettingsScreen::on_resize() {

}

void SettingsScreen::on_closing() {

}

void SettingsScreen::handle_events(sf::Event& sf_event) {
	switch (sf_event.type) {

	case sf::Event::MouseButtonPressed:
		IO_DATA::choose_open_file();
		app->close_current_screen();
		break;

	default:
		break;

	}
}

void SettingsScreen::update(float dt) {

}

void SettingsScreen::render(sf::RenderTarget& window) {
	window.clear(sf::Color::Red);


}