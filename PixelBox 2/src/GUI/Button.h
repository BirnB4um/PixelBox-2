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
	void reloadResources() override;

	void setFunction(std::function<void()> func);


	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float width, float height);
	void setSize(sf::Vector2f size);
	void setBounds(float x, float y, float width, float height);
	void setBounds(sf::FloatRect bounds);
	void setBorderWidth(float width);

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::FloatRect getBounds();
	float getBorderWidth();


protected:
	NinePatch m_ninePatch;
	bool m_hovered;
	bool m_pressed;
	float m_borderWidth;
	sf::FloatRect m_bounds;
	std::function<void()> m_function;

	virtual void updateSize();
	void updateInteraction();
};
