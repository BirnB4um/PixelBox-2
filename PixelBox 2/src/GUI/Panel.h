#pragma once

#include "GuiContainer.h"
#include "NinePatch.h"

class Panel : public GuiContainer
{
public:
	Panel();
	~Panel();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;


protected:
	//TODO: change from rendering to a seperate texture to clipping by manipulating the view + viewport

	NinePatch m_ninePatch;
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_renderSprite;
	sf::View m_textureView;
	sf::FloatRect m_textureViewRect;

	void updateBounds() override;
	inline void updateViewFromRect(sf::FloatRect& rect);
	void updateMouseOffset() override;
	

};

