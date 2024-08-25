#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screens/Screen.h"
#include "Screens/HomeScreen/HomeScreen.h"
#include "Screens/SettingsScreen/SettingsScreen.h"
#include "Screens/WorldSelectionScreen/WorldSelectionScreen.h"
#include "Screens/WorldCreationScreen/WorldCreationScreen.h"
#include "Screens/SimulationScreen/SimulationScreen.h"
#include "ResourceManager.h"
#include "GUI/GuiElement.h"


enum class ScreenID {
	HOME, SETTINGS, WORLDSELECTION, WORLDCREATION, SIMULATION
};

class Application
{

public:

	static Application& instance();

	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	~Application();
	void init();
	void run();
	void closeCurrentScreen();
	void openScreen(ScreenID id);
	void close();
	sf::Vector2i getWindowSize();

	static sf::Vector2i mousePos;
	static sf::View normalView;

	Screen* currentScreen;
	HomeScreen homeScreen;
	SettingsScreen settingsScreen;
	WorldSelectionScreen worldSelectionScreen;
	WorldCreationScreen worldCreationScreen;
	SimulationScreen simulationScreen;

private:
	Application();

	//application data
	sf::RenderWindow m_window;
	sf::Event m_sfEvent;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;

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

	void createWindow(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync = false);
	void onResize();
	void onClosing();
	void handleEvents();
	void update();
	void draw();

};