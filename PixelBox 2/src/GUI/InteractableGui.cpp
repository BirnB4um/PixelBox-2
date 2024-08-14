#include "InteractableGui.h"
#include "../Application.h"

InteractableGui::InteractableGui() : GuiElement() {
	m_isInteractable = true;
}

void InteractableGui::setInteractable(bool interactable) {
	m_isInteractable = interactable;
}

bool InteractableGui::isInteractable() {
	return m_isInteractable;
}

sf::Vector2f InteractableGui::getMousePos() {
	if (m_parentGui == nullptr) {
		return static_cast<sf::Vector2f>(Application::mousePos);
	}
	else {
		return static_cast<sf::Vector2f>(Application::mousePos) - m_parentGui->getMouseOffset();
	}
}

bool InteractableGui::isMouseOver() {
	sf::Vector2f mouse = getMousePos();
	return m_bounds.contains(mouse) && ((m_parentGui == nullptr) ? true : m_parentGui->getInteractableArea().contains(mouse));
}