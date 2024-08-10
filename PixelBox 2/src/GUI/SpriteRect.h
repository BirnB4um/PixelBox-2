#pragma once

#include "GuiElement.h"

class SpriteRect : public GuiElement
{
public:
	SpriteRect();
	~SpriteRect();

	void render(sf::RenderTarget& window) override;

	//calculates the width based on the size ratio of the texture so it doesnt get distorted
	void setHeightWithRatio(float height);

	//calculates the height based on the size ratio of the texture so it doesnt get distorted
	void setWidthWithRatio(float Width);

protected:
	sf::RectangleShape m_rect;

	void updateBounds() override;

	//Ownership of the Texture stays with the caller
	void setTexture(sf::Texture* texture);
	void setTextureRect(sf::IntRect& rect);

	// returns the ratio of width/height
	float getTextureRatio();

};

