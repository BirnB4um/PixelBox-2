#pragma once
#include "../Screen.h"
#include "../../GUI/Panel.h"
#include "../../GUI/ScrollPanel.h"

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

	void onSwitch() override;

	void handleEvent(sf::Event& sfEvent) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;

private:

	sf::Text m_title;

	ScrollPanel m_worldMenu;

	TextButton m_createNewWorldButton;

	TextButton button1, button2;


};
