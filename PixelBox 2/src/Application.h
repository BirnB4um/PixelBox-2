#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Screens/Screen.h"
#include "Screens/HomeScreen.h"
#include "Screens/SettingsScreen.h"
#include "Screens/WorldSelectionScreen.h"
#include "ResourceManager.h"
#include "GUI/GuiElement.h"

enum class ScreenID {
	HOME, WORLDSELECTION, SETTINGS
};

class Application
{

public:

	static Application* currentInstance;
	static sf::Vector2i mousePos;

	Application();
	~Application();
	void run();
	void closeCurrentScreen();
	void openScreen(ScreenID id);
	ResourceManager& getResourceManager();
	void close();
	sf::Vector2i getWindowSize();


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
	bool m_shouldClose;

	//screens
	std::vector<Screen*> m_openScreens;
	std::vector<Screen*> m_allScreens;
	Screen* m_currentScreen;
	HomeScreen m_homescreen;
	SettingsScreen m_settingsscreen;
	WorldSelectionScreen m_worldselectionscreen;

	void createWindow(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync = false);
	void onResize();
	void onClosing();
	void handleEvents();
	void update();
	void draw();
	bool loadResources();

};
