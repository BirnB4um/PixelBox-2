#include "GuiElement.h"

sf::Texture* GuiElement::m_texture = nullptr;
float GuiElement::m_guiScale = 1.0f;

void GuiElement::setTexture(sf::Texture* texture) {
	m_texture = texture;
}

void GuiElement::setGuiScale(float scale) {
	m_guiScale = scale;
}


GuiElement::GuiElement() {
}

GuiElement::~GuiElement() {
}

void GuiElement::handleEvent(sf::Event& sfEvent) {
}

void GuiElement::update(float dt) {
}

void GuiElement::render(sf::RenderTarget& window) {
}

void GuiElement::reloadResources() {
}