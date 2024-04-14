#include "Slider.h"
#include "../Application.h"

Slider::Slider() {

	m_nob.setFillColor(sf::Color(60, 120, 200));
	m_nob.setOutlineThickness(0);

	m_minValue = 0.0f;
	m_maxValue = 1.0f;
	m_nobSize = 20.0f;

	m_ninePatch.setPatches(PatchAtlas::angularIdle);
	setBounds(sf::FloatRect(0, 0, 80, 40));
	setBorderWidth(2);

	m_hovered = false;
	m_pressed = false;

	m_function = []() {};

}

Slider::~Slider() {
}

void Slider::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		updateValue();
		break;

	case sf::Event::MouseButtonPressed:
		if (m_hovered) {
			m_pressed = true;
			updateValue();
		}
		break;

	case sf::Event::MouseButtonReleased:
		m_pressed = false;
		updateInteraction();
		break;

	default:
		break;
	}
}

void Slider::updateInteraction() {
	if (m_bounds.contains(static_cast<sf::Vector2f>(Application::mousePos))) {
		if (!m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::angularHover);
		}
		m_hovered = true;
	}
	else {
		if (m_hovered && !m_pressed) {
			m_ninePatch.setPatches(PatchAtlas::angularIdle);
			m_hovered = false;
		}
	}
}

void Slider::update(float dt) {
}

void Slider::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
	window.draw(m_nob);
}

void Slider::reloadResources() {
	m_ninePatch.setTexture(m_texture);
}

void Slider::setFunction(std::function<void()> func) {
	m_function = func;
}

void Slider::setPosition(float x, float y) {
	m_bounds.left = x;
	m_bounds.top = y;
	updateSize();
}

void Slider::setPosition(sf::Vector2f position) {
	m_bounds.left = position.x;
	m_bounds.top = position.y;
	updateSize();
}

void Slider::setSize(float width, float height) {
	m_bounds.width = width;
	m_bounds.height = height;
	updateSize();
}

void Slider::setSize(sf::Vector2f size) {
	m_bounds.width = size.x;
	m_bounds.height = size.y;
	updateSize();
}

void Slider::setBounds(float x, float y, float width, float height) {
	m_bounds.left = x;
	m_bounds.top = y;
	m_bounds.width = width;
	m_bounds.height = height;
	updateSize();
}

void Slider::setBounds(sf::FloatRect bounds) {
	m_bounds = bounds;
	updateSize();
}

void Slider::setBorderWidth(float width) {
	m_borderWidth = width;
	m_ninePatch.setBorderWidth(width);
	updateSize();
}

sf::Vector2f Slider::getPosition() {
	return sf::Vector2f(m_bounds.left, m_bounds.top);
}

sf::Vector2f Slider::getSize() {
	return sf::Vector2f(m_bounds.width, m_bounds.height);
}

sf::FloatRect Slider::getBounds() {
	return m_bounds;
}

float Slider::getBorderWidth() {
	return m_borderWidth;
}

void Slider::updateSize() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}

float Slider::getValue() {
	return m_minValue + m_value * (m_maxValue - m_minValue);
}

void Slider::setValue(float value) {
	m_value = value;
	m_value = std::max(m_value, m_minValue);
	m_value = std::min(m_value, m_maxValue);
}

void Slider::setRange(float min, float max) {
	m_minValue = min;
	m_maxValue = max;
}

void Slider::updateNobPosition() {
}

void Slider::setNobSize(float size) {
	m_nobSize = size;
	updateSize();
}

void Slider::updateValue() {

}