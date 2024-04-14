#pragma once
#include "Screen.h"
#include "../GUI/TextButton.h"
#include "../GUI/SpriteButton.h"
#include "../GUI/HorizontalSlider.h"
#include "../GUI/VerticalSlider.h"

class HomeScreen : public Screen
{
public:

	HomeScreen();
	~HomeScreen();

	void init() override;

	//called when the window is resized
	void onResize() override;

	//called when the window is about to close
	void onClosing() override;

	void handleEvent(sf::Event& sfEvent) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;

private:

	TextButton m_worldSelectionButton;
	TextButton m_settingsButton;
	SpriteButton m_testButton;
	HorizontalSlider m_slider;
	VerticalSlider m_slider2;




};
