#include "Switch.h"
#include "../Application.h"


Switch::Switch() : InteractableGui() {
	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	setBounds(sf::FloatRect(0, 0, 100, 60));
	setBorderWidth(4);

	m_hovered = false;
	m_pressed = false;
	m_activated = false;

	m_function = []() {};
}

Switch::~Switch() {
}

bool Switch::handleEvent(sf::Event& sfEvent) {
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
				if (m_activated) {
					m_ninePatch.setPatches(PatchAtlas::roundedIdle);
				}
				else {
					m_ninePatch.setPatches(PatchAtlas::roundedPressed);
				}
				m_pressed = true;
				return true;
			}
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (sfEvent.mouseButton.button == sf::Mouse::Left) {
			if (m_hovered && m_pressed) {
				m_ninePatch.setPatches(PatchAtlas::roundedHover);
				callFunction();
				m_pressed = false;
				return true;
			}
			m_pressed = false;
		}
		break;

	default:
		break;
	}

	return false;
}

void Switch::updateInteraction() {
	sf::Vector2f mouse = getMousePos();

	if (isMouseOver()) {
		if (m_pressed) {
			if (m_activated) {
				m_ninePatch.setPatches(PatchAtlas::roundedIdle);
			}
			else {
				m_ninePatch.setPatches(PatchAtlas::roundedPressed);
			}
		}
		else if (!m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::roundedHover);
		}
		m_hovered = true;
	}
	else {
		if (m_hovered) {
			if (m_activated) {
				m_ninePatch.setPatches(PatchAtlas::roundedPressed);
			}
			else {
				m_ninePatch.setPatches(PatchAtlas::roundedIdle);
			}
		}
		m_hovered = false;
	}
}

void Switch::update(float dt) {
	if (!m_isInteractable)
		return;

}

void Switch::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
}

void Switch::reloadResources() {
	m_ninePatch.reloadResources();
}

void Switch::setFunction(std::function<void()> func) {
	m_function = func;
}

void Switch::callFunction() {
	m_activated = !m_activated;
	m_function();
	m_ninePatch.setPatches(m_activated ? PatchAtlas::roundedPressed : PatchAtlas::roundedIdle);
}

void Switch::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}

bool Switch::isActivated() {
	return m_activated;
}

void Switch::setActivated(bool activated) {
	m_activated = activated;
	m_ninePatch.setPatches(m_activated ? PatchAtlas::roundedPressed : PatchAtlas::roundedIdle);
}

void Switch::resetInteractionState() {
	m_pressed = false;
	m_hovered = false;
	m_activated = false;//TODO: should activate be reset???
	if (m_activated) {
		m_ninePatch.setPatches(PatchAtlas::roundedPressed);
	}
	else {
		m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	}
	updateInteraction();
}