#pragma once

#include <functional>
#include <vector>
#include "InteractableGui.h"
#include "NinePatch.h"


class StateSwitch : public InteractableGui
{
public:
	StateSwitch();
	~StateSwitch();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void resetInteractionState() override;

	void setFunction(std::function<void()> func);
	void callFunction();

	virtual void setState(size_t id);


protected:
	NinePatch m_ninePatch;
	bool m_hovered;
	bool m_pressed;
	std::function<void()> m_function;

	size_t m_currentState;

	void updateBounds() override;
	void updateInteraction();

	virtual void incrementState();

};

