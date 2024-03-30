#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"
#include <imgui.h>
#include <imgui-SFML.h>

class Application;

class Button : public GuiElement
{
public:

	Button();
	~Button();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setPosX(int x);
	void setPosY(int y);
	void setPosition(int x, int y);
	void setWidth(int width);
	void setHeight(int height);
	void setSize(int width, int height);
	void setBounds(int x, int y, int width, int height);
	void setBorderWidth(int width);

	int getPosX();
	int getPosY();
	sf::Vector2i getPosition();
	int getWidth();
	int getHeight();
	sf::Vector2i getSize();
	int getBorderWidth();

	void setText(std::string text);

	void setFunction(std::function<void()> func);

	void setFont(sf::Font& font);

private:
	NinePatch m_ninePatch;
	sf::Text m_text;
	bool m_hovered;
	bool m_pressed;
	int m_posX, m_posY, m_width, m_height, m_borderWidth;
	std::function<void()> m_function;

	void updateSize();
	void updateInteraction();
};
