#pragma once
#include "../Screen.h"
#include "../../GUI/TextButton.h"
#include "../../GUI/TextInput.h"

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

	void onSwitch() override;

	bool handleEvent(sf::Event& sfEvent) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;

private:
	sf::RectangleShape m_logo;

	TextButton m_worldsButton;
	TextButton m_settingsButton;
	TextButton m_exitButton;

};
