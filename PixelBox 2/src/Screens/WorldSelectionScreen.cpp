#include "WorldSelectionScreen.h"
#include "../Application.h"

WorldSelectionScreen::WorldSelectionScreen() {
}

WorldSelectionScreen::~WorldSelectionScreen() {
}

void WorldSelectionScreen::init() {
	m_button.setBounds(100, 100, 100, 60);
	m_button.setFunction([this]() {
		app->close();
		});
	m_guiElements.push_back(&m_button);

	reloadGuiResources();
}

void WorldSelectionScreen::onResize() {
}

void WorldSelectionScreen::onClosing() {
}

void WorldSelectionScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		break;

	default:
		break;
	}
}

void WorldSelectionScreen::update(float dt) {
	updateGui(dt);
}

void WorldSelectionScreen::render(sf::RenderTarget& window) {
	window.clear();
	renderGui(window);
}