#pragma once

#include <SFML/Graphics.hpp>


class GuiElement
{
public:

	GuiElement();
	~GuiElement();

	virtual void handleEvent(sf::Event& sfEvent);
	virtual void update(float dt);
	virtual void render(sf::RenderTarget& window);
	virtual void reloadResources();

	static void setGuiScale(float scale);
	static void setTexture(sf::Texture* texture);

protected:
	static float m_guiScale;
	static sf::Texture* m_texture;

};
