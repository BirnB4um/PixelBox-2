#pragma once

#include <functional>
#include "InteractableGui.h"
#include "NinePatch.h"
#include "PatchAtlas.h"

class Application;

class Switch : public InteractableGui
{
public:
	Switch();
	~Switch();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void resetInteractionState() override;

	void setFunction(std::function<void()> func);

	bool isActivated();

protected:
	NinePatch m_ninePatch;
	bool m_hovered;
	bool m_pressed;
	bool m_activated;
	std::function<void()> m_function;

	void updateBounds() override;
	void updateInteraction();

};

