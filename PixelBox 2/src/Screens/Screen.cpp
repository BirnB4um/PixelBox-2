#include "Screen.h"
#include "../Application.h"



Screen::Screen() {
}

Screen::~Screen() {
}

void Screen::init() {

}

void Screen::onResize() {
}

void Screen::onClosing() {
}

void Screen::onSwitch() {
	resetGuiInteraction();
}

bool Screen::handleGuiEvent(sf::Event& sfEvent) {
	for (GuiElement* guiElement : m_guiElements) {
		if (guiElement->handleEvent(sfEvent))
			return true;
	}
	return false;
}

void Screen::updateGui(float dt) {
	for (GuiElement* guiElement : m_guiElements) {
		guiElement->update(dt);
	}
}

void Screen::renderGui(sf::RenderTarget& window) {
	for (GuiElement* guiElement : m_guiElements) {
		guiElement->render(window);
	}
}

void Screen::reloadGuiResources() {
	for (GuiElement* guiElement : m_guiElements) {
		guiElement->reloadResources();
	}
}

void Screen::resetGuiInteraction() {
	for (GuiElement* guiElement : m_guiElements) {
		InteractableGui* interactable = dynamic_cast<InteractableGui*>(guiElement);
		if (interactable != nullptr)
			interactable->resetInteractionState();
	}
}

bool Screen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);
	return false;
}

void Screen::update(float dt) {
	updateGui(dt);
}


void Screen::render(sf::RenderTarget& window) {
	window.clear();
	renderGui(window);
}

void Screen::addGuiElement(GuiElement* element) {
	m_guiElements.push_back(element);
}