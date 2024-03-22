#include "HomeScreen.h"
#include "../Application.h"

HomeScreen::HomeScreen() {

}

HomeScreen::~HomeScreen() {

}

void HomeScreen::init() {

}

void HomeScreen::run() {

}

void HomeScreen::on_resize() {

}

void HomeScreen::on_closing() {

}

void HomeScreen::handle_events(sf::Event& sf_event) {
	switch (sf_event.type) {

	case sf::Event::MouseButtonPressed:
		app->open_screen(app->SETTINGS);
		break;

	default:
		break;

	}
}

void HomeScreen::update(float dt) {
	ImGui::Begin("Hallo");
	ImGui::Text("halloooooooooo");
	ImGui::ColorButton("Color", ImVec4(0.4f, 0.7f, 0.8f, 0.5f));
	ImVec4 color = ImVec4(0.4f, 0.7f, 0.8f, 0.5f);
	ImGui::ColorPicker3("MEINE FARBEEE", (float*)&color);
	ImGui::End();
}

void HomeScreen::render(sf::RenderTarget& window) {
	window.clear(sf::Color::Green);
}