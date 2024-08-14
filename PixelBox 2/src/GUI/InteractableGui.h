#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"

class InteractableGui : public GuiElement
{
public:
	InteractableGui();
	
	void setInteractable(bool interactable);
	bool isInteractable();

	//checks if the mouse is over the interactable area
	//also works with recursiv parent containers
	bool isMouseOver();

protected:
	sf::Vector2f getMousePos();

	bool m_isInteractable;
};

