#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/GuiElement.h"

class Application;

class Screen
{

public:
	static Application* app;

	Screen();
	~Screen();

	virtual void init();

	//called when the window is resized
	virtual void onResize();

	//called when the window is about to close
	virtual void onClosing();

	virtual void handleEvent(sf::Event& sfEvent);

	//update given deltatime dt in seconds
	virtual void update(float dt);

	virtual void render(sf::RenderTarget& window);


	void handleGuiEvent(sf::Event& sfEvent);
	void updateGui(float dt);
	void renderGui(sf::RenderTarget& window);
	void reloadGuiResources();



protected:
	std::vector<GuiElement*> m_guiElements;



};

