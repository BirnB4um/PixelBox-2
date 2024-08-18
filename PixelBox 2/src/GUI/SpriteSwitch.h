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

protected:
	sf::Sprite m_sprite;

	void updateBounds() override;


};

