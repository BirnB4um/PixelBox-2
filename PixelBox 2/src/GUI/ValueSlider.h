#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "NinePatch.h"
#include "InteractableGui.h"

class Application;

class ValueSlider : public InteractableGui
{
public:
	ValueSlider();
	~ValueSlider();

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

	//returns true if the slider is currently being interacted with
	inline bool isInteracted() { return m_pressed; }

protected:
	NinePatch m_ninePatch;
	sf::RectangleShape m_nob;
	sf::RectangleShape m_zeroLine;
	bool m_drawZeroLine;
	bool m_hovered;
	bool m_pressed;
	std::function<void()> m_function;
	float m_value;
	float m_minValue, m_maxValue;

	void updateInteraction();
	virtual void updateBounds();
	virtual void updateNobPosition();
	virtual void updateValue();
	virtual void updateZeroLine();

};

