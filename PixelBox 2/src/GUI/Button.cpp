#include "Button.h"

Button::Button() : InteractableGui() {
	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	setBounds(sf::FloatRect(0, 0, 100, 60));
	setBorderWidth(4);

	m_hovered = false;
	m_pressed = false;

	m_function = []() {};
}

Button::~Button() {
}

bool Button::handleEvent(sf::Event& sfEvent) {
	if (!m_isInteractable)
		return false;

	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		if (m_pressed)
			return true;
		break;

	case sf::Event::MouseButtonPressed:
		if (sfEvent.mouseButton.button == sf::Mouse::Left) {
			if (m_hovered) {
				m_ninePatch.setPatches(PatchAtlas::roundedPressed);
				m_pressed = true;
				return true;
			}
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (sfEvent.mouseButton.button == sf::Mouse::Left) {
			if (m_hovered && m_pressed) {
				m_ninePatch.setPatches(PatchAtlas::roundedHover);
				m_function();
				m_pressed = false;
				return true;
			}
		}
		m_pressed = false;
		break;

	default:
		break;
	}

	return false;
}

void Button::updateInteraction() {
	if (isMouseOver()) {
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
	if (!m_isInteractable)
		return;

}

void Button::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
}

void Button::reloadResources() {
	m_ninePatch.reloadResources();
}

void Button::setFunction(std::function<void()> func) {
	m_function = func;
}

void Button::callFunction() {
	m_function();
}

void Button::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}

void Button::resetInteractionState() {
	m_pressed = false;
	m_hovered = false;
	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	updateInteraction();
}