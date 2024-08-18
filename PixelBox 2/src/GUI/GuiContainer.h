#pragma once
#include "InteractableGui.h"

//only a base class
class GuiContainer : public InteractableGui
{
public:
	GuiContainer();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void resetInteractionState() override;

	// clear all elements and set their parent to null
	virtual void clearElements();
	// Ownership of element retains with the caller
	virtual void addElement(GuiElement* element);

	//get offset of new origin
	sf::Vector2f getMouseOffset();
	virtual void updateMouseOffset();

	//get area relative to parent origin
	sf::FloatRect getInteractableArea();

protected:
	sf::Vector2f m_mouseOffset;
	sf::FloatRect m_interactableArea;
	std::vector<GuiElement*> m_elements;

};

