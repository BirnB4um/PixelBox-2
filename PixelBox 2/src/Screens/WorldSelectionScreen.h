#pragma once
#include "Screen.h"
#include "../GUI/Button.h"

class WorldSelectionScreen : public Screen
{
public:

	WorldSelectionScreen();
	~WorldSelectionScreen();

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

	Button m_button;


};
