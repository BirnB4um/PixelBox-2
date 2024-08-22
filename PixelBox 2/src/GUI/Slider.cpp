#include "Slider.h"
#include "../Application.h"

Slider::Slider(): InteractableGui() {
	m_nob.setFillColor(sf::Color(60, 120, 200));
	m_nob.setOutlineThickness(0);

	m_value = 0.0f;
	m_minValue = 0.0f;
	m_maxValue = 1.0f;
	m_nobSize = 20.0f;
	m_mouseGrabOffset = sf::Vector2f(0.0f, 0.0f);

	m_ninePatch.setPatches(PatchAtlas::angularIdle);
	setBounds(sf::FloatRect(0, 0, 80, 40));
	setBorderWidth(1);

	m_hovered = false;
	m_pressed = false;

	m_function = []() {};
}

Slider::~Slider() {
}

bool Slider::handleEvent(sf::Event& sfEvent) {
	if (!m_isInteractable)
		return false;

	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		updateValue();
		if (m_pressed)
			return true;
		break;

	case sf::Event::MouseButtonPressed:
		if (sfEvent.mouseButton.button == sf::Mouse::Left) {
			if (m_hovered) {
				if (m_nob.getGlobalBounds().contains(getMousePos())) {
					m_pressed = true;
					m_mouseGrabOffset = getMousePos() - m_nob.getPosition();
					updateValue();
				}
				return true;
			}
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (sfEvent.mouseButton.button == sf::Mouse::Left) {
			m_pressed = false;
			updateInteraction();
		}
		break;

	case sf::Event::MouseWheelScrolled:
		if (isMouseOver()) {
			float delta = -sfEvent.mouseWheelScroll.delta;
			setValue(getValue() + delta);
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}

void Slider::updateInteraction() {
	sf::Vector2f mouse = getMousePos();
	if (isMouseOver()) {
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
	if (!m_isInteractable)
		return;

}

void Slider::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
	window.draw(m_nob);
}

void Slider::reloadResources() {
	m_ninePatch.reloadResources();
}

void Slider::setFunction(std::function<void()> func) {
	m_function = func;
}

void Slider::callFunction() {
	m_function();
}

void Slider::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}

float Slider::getValue() {
	return m_minValue + m_value * (m_maxValue - m_minValue);
}

void Slider::setValue(float value) {
	value = value;
	value = std::max(value, m_minValue);
	value = std::min(value, m_maxValue);
	m_value = (value - m_minValue) / (m_maxValue - m_minValue);

	updateNobPosition();
	m_function();
}

void Slider::setRange(float min, float max) {
	if (min == max)
		max += 0.0001f;
	
	m_minValue = min;
	m_maxValue = max;

}

void Slider::updateNobPosition() {
}

void Slider::setNobSize(float size) {
	m_nobSize = size;
	updateBounds();
}

void Slider::updateValue() {
}

void Slider::resetInteractionState() {
	m_pressed = false;
	m_hovered = false;
	m_ninePatch.setPatches(PatchAtlas::angularIdle);
	updateInteraction();
}