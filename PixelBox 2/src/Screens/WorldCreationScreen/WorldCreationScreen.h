#pragma once

#include "../Screen.h"
#include "../../GUI/TextButton.h"
#include "../../World/World.h"
#include "../../World/WorldMetaData.h"

class WorldCreationScreen : public Screen
{
public:
	WorldCreationScreen();
	~WorldCreationScreen();

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

	TextButton m_backButton;
	TextButton m_createWorldButton;

	//caller has ownership of world
	World* createNewWorld();


};

