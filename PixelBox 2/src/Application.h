#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Screens/Screen.h"
#include "Screens/HomeScreen.h"
#include "Screens/SettingsScreen.h"


class Application
{
private:

	//application data
	sf::RenderWindow window;
	sf::View normal_view;
	sf::Event sf_event;
	sf::Clock deltaClock;
	sf::Time deltaTime;

	int window_width;
	int window_height;
	int windowed_width;
	int windowed_height;
	int fps;
	bool fullscreen;

	//screens
	std::vector<Screen*> screens;
	Screen* current_screen;
	HomeScreen homescreen;
	SettingsScreen settingsscreen;



	void create_window(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync = false);
	void on_resize();
	void on_closing();
	void handle_events();
	void update();
	void draw();

public:
	enum SCREEN_ID {
		HOME, SETTINGS
	};

	Application();
	~Application();
	void run();
	void close_current_screen();
	void open_screen(SCREEN_ID id);
};
