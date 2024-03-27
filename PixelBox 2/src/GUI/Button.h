#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"

class Application;

class Button : public GuiElement
{
public:

	Button();
	~Button();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;

	void setPosX(float x);
	void setPosY(float y);
	void setPosition(float x, float y);
	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);
	void setBounds(float x, float y, float width, float height);

	void setText(std::string text);

	void setFunction(std::function<void()> func);

	void setFont(sf::Font& font);

private:
	sf::RectangleShape m_rect;
	sf::Text m_text;
	bool m_hovered;
	bool m_pressed;
	float m_posX, m_posY, m_width, m_height;
	std::function<void()> m_function;

	void updateSize();
	float t;
};
