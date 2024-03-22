#pragma once
#include "Screen.h"
#include "../Tools/IO_DATA.h"

class SettingsScreen : public Screen
{

public:

	SettingsScreen();
	~SettingsScreen();

	void init() override;

	void run() override;

	//called when the window is resized
	void on_resize() override;

	//called when the window is about to close
	void on_closing() override;

	void handle_events(sf::Event& sf_event) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;


private:


};

