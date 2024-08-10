#pragma once
#include <iostream>
#include "../Screen.h"
#include "../../Tools/IO_DATA.h"

class SettingsScreen : public Screen
{

public:

	SettingsScreen();
	~SettingsScreen();

	void init() override;

	//called when the window is resized
	void onResize() override;

	//called when the window is about to close
	void onClosing() override;

	void onSwitch() override;

	void handleEvent(sf::Event& sfEvent) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;


private:


};

