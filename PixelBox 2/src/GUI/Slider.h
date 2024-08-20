#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "InteractableGui.h"
#include "NinePatch.h"
#include "PatchAtlas.h"
#include "../Tools/Utils.h"

class Application;

class Slider : public InteractableGui
{
public:

	Slider();
	~Slider();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void resetInteractionState() override;

	//the given function gets called everytime the slider changes its value
	void setFunction(std::function<void()> func);
	void callFunction();

	float getValue();
	void setValue(float value);
	void setRange(float min, float max);
	void setNobSize(float size);


protected:
	NinePatch m_ninePatch;
	sf::RectangleShape m_nob;
	bool m_hovered;
	bool m_pressed;
	std::function<void()> m_function;
	float m_value; //should always be between 0 and 1
	float m_minValue, m_maxValue;
	float m_nobSize;
	sf::Vector2f m_mouseGrabOffset;

	virtual void updateBounds();
	void updateInteraction();
	virtual void updateNobPosition();
	virtual void updateValue();
};
