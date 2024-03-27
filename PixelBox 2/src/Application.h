#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Screens/Screen.h"
#include "Screens/HomeScreen.h"
#include "Screens/SettingsScreen.h"
#include "ResourceManager.h"
#include "GUI/GuiElement.h"

enum class ScreenID {
	HOME, SETTINGS
};

class Application
{

public:

	static Application* currentInstance;

	Application();
	~Application();
	void run();
	void closeCurrentScreen();
	void openScreen(ScreenID id);
	ResourceManager& getResourceManager();


private:

	//application data
	sf::RenderWindow m_window;
	sf::Event m_sfEvent;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;
	sf::View normalView;
	ResourceManager m_resourceManager;

	std::string m_title;
	int m_windowWidth;
	int m_windowHeight;
	int m_windowedWidth;
	int m_windowedHeight;
	int m_fps;
	bool m_fullscreen;

	//screens
	std::vector<Screen*> m_screens;
	Screen* m_currentScreen;
	HomeScreen m_homescreen;
	SettingsScreen m_settingsscreen;

	void createWindow(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync = false);
	void onResize();
	void onClosing();
	void handleEvents();
	void update();
	void draw();
	bool loadResources();

};
