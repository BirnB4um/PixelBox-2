#pragma once

#include "../Screen.h"
#include "../../World/World.h"

class SimulationScreen : public Screen
{
public:
	SimulationScreen();
	~SimulationScreen();

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

	//ownership gets transfered
	void setWorld(World* world);

private:

	World* m_world;


};

