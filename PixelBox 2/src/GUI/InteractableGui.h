#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"

class InteractableGui : public GuiElement
{
public:
	InteractableGui();
	
	void setInteractable(bool interactable);
	bool isInteractable();

protected:
	sf::Vector2f getMousePos();

	bool m_isInteractable;
};

