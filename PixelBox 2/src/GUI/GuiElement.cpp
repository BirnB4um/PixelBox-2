#include "GuiElement.h"

GuiElement::GuiElement() {
	m_bounds = sf::FloatRect(0, 0, 0, 0);
	m_borderWidth = 0;

	m_parentGui = nullptr;
}

GuiElement::~GuiElement() {
}

bool GuiElement::handleEvent(sf::Event& sfEvent) {
	return false;
}

void GuiElement::update(float dt) {
}

void GuiElement::render(sf::RenderTarget& window) {
}

void GuiElement::reloadResources() {
}


void GuiElement::setPosition(float x, float y) {
	m_bounds.left = x;
	m_bounds.top = y;
	updateBounds();
}

void GuiElement::setPosition(sf::Vector2f position) {
	m_bounds.left = position.x;
	m_bounds.top = position.y;
	updateBounds();
}

void GuiElement::setSize(float width, float height) {
	m_bounds.width = std::max(0.0f, width);
	m_bounds.height = std::max(0.0f, height);
	updateBounds();
}

void GuiElement::setSize(sf::Vector2f size) {
	m_bounds.width = std::max(0.0f, size.x);
	m_bounds.height = std::max(0.0f, size.y);
	updateBounds();
}

void GuiElement::setBounds(float x, float y, float width, float height) {
	m_bounds.left = x;
	m_bounds.top = y;
	m_bounds.width = std::max(0.0f, width);
	m_bounds.height = std::max(0.0f, height);
	updateBounds();
}

void GuiElement::setBounds(sf::FloatRect bounds) {
	m_bounds = bounds;
	m_bounds.width = std::max(0.0f, m_bounds.width);
	m_bounds.height = std::max(0.0f, m_bounds.height);
	updateBounds();
}

void GuiElement::setBorderWidth(float width) {
	m_borderWidth = std::max(0.0f, width);
	updateBounds();
}

void GuiElement::setParent(GuiContainer* parent) {
	m_parentGui = parent;
}


sf::Vector2f GuiElement::getPosition() {
	return sf::Vector2f(m_bounds.left, m_bounds.top);
}

sf::Vector2f GuiElement::getSize() {
	return sf::Vector2f(m_bounds.width, m_bounds.height);
}

sf::FloatRect GuiElement::getBounds() {
	return m_bounds;
}

float GuiElement::getBorderWidth() {
	return m_borderWidth;
}

GuiContainer* GuiElement::getParent() {
	return m_parentGui;
}


void GuiElement::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);
}
