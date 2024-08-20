#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include "../Screen.h"
#include "../../World/World.h"
#include "WorldInteractionManager.h"

class SimulationScreen : public Screen
{
public:

	friend class WorldInteractionManager;

	SimulationScreen();
	~SimulationScreen();

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



	//ownership gets transferred
	void setWorld(World* world);


private:

	World* m_world;

	sf::Texture m_pixelTexture;
	sf::Sprite m_pixelSprite;

	sf::View m_pixelView;
	sf::Vector2f m_targetViewCenter;
	float m_zoomLevel;
	float m_targetZoomLevel;

	sf::Vector2i m_startGrabbedMousePos;
	sf::Vector2f m_startGrabbedViewCenter;
	bool m_boardGrabbed;

	bool m_isSimulationPaused;
	double m_msPerTick;
	double m_msPerFrame;

	std::thread m_simulationThread;
	std::thread m_renderingThread;
	bool m_stopSimulationThread;
	bool m_stopRenderingThread;
	std::mutex m_bufferMutex; //mutex for all buffers in World

	WorldInteractionManager m_worldInteractionManager;

	uint32_t m_selectedPixelData;

	void resetView();
	void updateView(float dt);

	void th_simulationLoop();
	void th_renderingLoop();

	void startSimulationThread();
	void stopSimulationThread();
	void startRenderingThread();
	void stopRenderingThread();

	sf::Vector2f getMouseWorldPos();

	void deleteWorld();



};

