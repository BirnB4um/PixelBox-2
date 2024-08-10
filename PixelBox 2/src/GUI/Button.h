#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "InteractableGui.h"
#include "NinePatch.h"
#include "PatchAtlas.h"
#include "../Tools/Utils.h"
#include "GuiContainer.h"

class Application;

class Button : public InteractableGui
{
public:

	Button();
	~Button();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setFunction(std::function<void()> func);

protected:
	NinePatch m_ninePatch;
	bool m_hovered;
	bool m_pressed;
	std::function<void()> m_function;

	void updateBounds() override;
	void updateInteraction();
};
