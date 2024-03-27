#include "Panel.h"

Panel::Panel() {

}

Panel::~Panel() {

}

void Panel::handleEvent(sf::Event& sfEvent) {
	for(GuiElement& gui_element: m_guiElements) {
		gui_element.handleEvent(sfEvent);
	}
}

void Panel::update(float dt) {
	for (GuiElement& gui_element : m_guiElements) {
		gui_element.update(dt);
	}
}

void Panel::render(sf::RenderTarget& window) {
	for (GuiElement& gui_element : m_guiElements) {
		gui_element.render(window);
	}
}