#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "NinePatch.h"
#include "PatchAtlas.h"
#include "../Tools/Utils.h"

class Application;

class Slider : public GuiElement
{
public:

	Slider();
	~Slider();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	//the given function gets called everytime the slider changes its value
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

	float getValue();
	void setValue(float value);
	void setRange(float min, float max);
	void setNobSize(float size);


protected:
	NinePatch m_ninePatch;
	sf::RectangleShape m_nob;
	bool m_hovered;
	bool m_pressed;
	float m_borderWidth;
	sf::FloatRect m_bounds;
	std::function<void()> m_function;
	float m_value;
	float m_minValue, m_maxValue;
	float m_nobSize;

	virtual void updateSize();
	void updateInteraction();
	virtual void updateNobPosition();
	virtual void updateValue();
};
