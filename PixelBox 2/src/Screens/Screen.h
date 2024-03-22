#pragma once
#include <SFML/Graphics.hpp>

class Application;

class Screen
{

public:
	static Application* app;

	Screen();
	~Screen();

	virtual void init();

	virtual void run();

	//called when the window is resized
	virtual void on_resize();

	//called when the window is about to close
	virtual void on_closing();

	virtual void handle_events(sf::Event& sf_event);

	//update given deltatime dt in seconds
	virtual void update(float dt);

	virtual void render(sf::RenderTarget& window);


private:


};

