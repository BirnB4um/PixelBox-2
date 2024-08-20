#pragma once

#include <SFML/Graphics.hpp>
#include "Switch.h"

class SpriteSwitch : public Switch
{
public:
	SpriteSwitch();
	~SpriteSwitch();

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
