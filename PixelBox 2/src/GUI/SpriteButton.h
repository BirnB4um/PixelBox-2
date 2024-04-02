#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Button.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"

class Application;

class SpriteButton : public Button
{
public:

	SpriteButton();
	~SpriteButton();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setTexturePatch(sf::IntRect area);



protected:
	sf::Sprite m_sprite;

	void updateSize() override;
};
