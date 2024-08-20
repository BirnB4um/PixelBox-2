#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Button.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"
#include "../ResourceManager.h"

class SpriteButton : public Button
{
public:

	SpriteButton();
	~SpriteButton();

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setTexture(sf::Texture* texture);
	void setTexturePatch(sf::IntRect area);

	void setSpritePadding(float padding);
	inline float getSpritePadding() { return m_spritePadding; }

protected:
	sf::Sprite m_sprite;
	float m_spritePadding;

	void updateBounds() override;
};
