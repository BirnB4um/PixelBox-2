#include "Button.h"
#include "../Application.h"

Button::Button() {

	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	setBounds(sf::FloatRect(0, 0, 100, 60));
	setBorderWidth(4);

	m_hovered = false;
	m_pressed = false;

	m_function = []() {};

}

Button::~Button() {
}

void Button::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		break;

	case sf::Event::MouseButtonPressed:
		if (m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::roundedPressed);
			m_pressed = true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (m_hovered && m_pressed) {
			m_ninePatch.setPatches(PatchAtlas::roundedHover);
			m_function();
		}
		m_pressed = false;
		break;

	default:
		break;
	}
}

void Button::updateInteraction() {
	if (m_bounds.contains(static_cast<sf::Vector2f>(Application::mousePos))) {
		if (m_pressed) {
			m_ninePatch.setPatches(PatchAtlas::roundedPressed);
		}
		else if (!m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::roundedHover);
		}
		m_hovered = true;
	}
	else {
		if (m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::roundedIdle);
		}
		m_hovered = false;
	}
}

void Button::update(float dt) {
}

void Button::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
}

void Button::reloadResources() {
	m_ninePatch.setTexture(m_texture);
}

void Button::setFunction(std::function<void()> func) {
	m_function = func;
}

void Button::setPosition(float x, float y) {
	m_bounds.left = x;
	m_bounds.top = y;
	updateSize();
}

void Button::setPosition(sf::Vector2f position) {
	m_bounds.left = position.x;
	m_bounds.top = position.y;
	updateSize();
}

void Button::setSize(float width, float height) {
	m_bounds.width = width;
	m_bounds.height = height;
	updateSize();
}

void Button::setSize(sf::Vector2f size) {
	m_bounds.width = size.x;
	m_bounds.height = size.y;
	updateSize();
}

void Button::setBounds(float x, float y, float width, float height) {
	m_bounds.left = x;
	m_bounds.top = y;
	m_bounds.width = width;
	m_bounds.height = height;
	updateSize();
}

void Button::setBounds(sf::FloatRect bounds) {
	m_bounds = bounds;
	updateSize();
}

void Button::setBorderWidth(float width) {
	m_borderWidth = width;
	m_ninePatch.setBorderWidth(width);
	updateSize();
}

sf::Vector2f Button::getPosition() {
	return sf::Vector2f(m_bounds.left, m_bounds.top);
}

sf::Vector2f Button::getSize() {
	return sf::Vector2f(m_bounds.width, m_bounds.height);
}

sf::FloatRect Button::getBounds() {
	return m_bounds;
}

float Button::getBorderWidth() {
	return m_borderWidth;
}

void Button::updateSize() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}