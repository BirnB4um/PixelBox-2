#include "GuiContainer.h"

GuiContainer::GuiContainer() {
	m_mouseOffset = sf::Vector2f(0.0f, 0.0f);
	m_interactableArea = sf::FloatRect(0.0f, 0.0f, 100000.0f, 100000.0f);
}

bool GuiContainer::handleEvent(sf::Event& sfEvent) {
	//TODO: return true if any element captures the event

	//switch (sfEvent.type)
	//{
	//default:
	//	break;
	//}

	for (GuiElement* element : m_elements) {
		element->handleEvent(sfEvent);
	}

	return false;
}

void GuiContainer::update(float dt) {
	for (GuiElement* element : m_elements) {
		element->update(dt);
	}
}

void GuiContainer::render(sf::RenderTarget& window) {
	for (GuiElement* element : m_elements) {
		element->render(window);
	}
}

void GuiContainer::reloadResources() {
	for (GuiElement* element : m_elements) {
		element->reloadResources();
	}
	updateBounds();
}

void GuiContainer::clearElements() {
	for (GuiElement* element : m_elements) {
		element->setParent(nullptr);
	}
	m_elements.clear();
}

void GuiContainer::addElement(GuiElement* element) {
	m_elements.push_back(element);
	element->setParent(this);
}


sf::Vector2f GuiContainer::getMouseOffset() {
	return (m_parentGui == nullptr) ? m_mouseOffset : m_mouseOffset + m_parentGui->getMouseOffset();
}

void GuiContainer::updateMouseOffset() {
	m_mouseOffset.x = m_bounds.left + m_borderWidth;
	m_mouseOffset.y = m_bounds.top + m_borderWidth;
}

sf::FloatRect GuiContainer::getInteractableArea() {
	if (m_parentGui == nullptr)
		return m_interactableArea;

	sf::FloatRect parentArea = m_parentGui->getInteractableArea();
	parentArea.left -= m_mouseOffset.x;
	parentArea.top -= m_mouseOffset.y;

	float x1 = std::max(parentArea.left, m_interactableArea.left);
	float x2 = std::min(parentArea.left + parentArea.width, m_interactableArea.left + m_interactableArea.width);
	float y1 = std::max(parentArea.top, m_interactableArea.top);
	float y2 = std::min(parentArea.top + parentArea.height, m_interactableArea.top + m_interactableArea.height);
	sf::FloatRect resultArea(x1, y1, x2 - x1, y2 - y1);
	return resultArea;
}