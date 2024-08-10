#include "SimulationScreen.h"
#include "../../Application.h"

SimulationScreen::SimulationScreen() {
	m_world = nullptr;
}

SimulationScreen::~SimulationScreen() {

}

void SimulationScreen::init() {

}

void SimulationScreen::onResize() {

}

void SimulationScreen::onClosing() {

}

void SimulationScreen::onSwitch() {

}

void SimulationScreen::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sfEvent.key.code == sf::Keyboard::Escape) {
			delete m_world;
			Application::instance().closeCurrentScreen();
		}
		break;
	default:
		break;
	}


	handleGuiEvent(sfEvent);
}

void SimulationScreen::update(float dt) {
	updateGui(dt);
}

void SimulationScreen::render(sf::RenderTarget& window) {
	window.clear();

	renderGui(window);
}

void SimulationScreen::setWorld(World* world) {
	m_world = world;
}
