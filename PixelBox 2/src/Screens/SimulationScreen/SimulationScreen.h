#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include "../Screen.h"
#include "../../World/World.h"
#include "../../World/DrawInstruction.h"
#include "../../World/PixelData.h"
#include "WorldInteractionManager.h"
#include "Inventory.h"
#include "../../Tools/DoubleMutex.h"

class SimulationScreen : public Screen
{
public:

	friend class WorldInteractionManager;
	friend class Inventory;

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

	inline void setMSPerTick(double msPerTick) { m_msPerTick = msPerTick; }
	inline double getMSPerTick() { return m_msPerTick; }



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
	bool m_updateOneTick;

	std::thread m_simulationThread;
	std::thread m_renderingThread;
	bool m_stopSimulationThread;
	bool m_stopRenderingThread;
	DoubleMutex m_bufferMutex; //mutex for all buffers in World

	bool m_hideGui;
	WorldInteractionManager m_worldInteractionManager;
	Inventory m_inventory;


	//for collecting instructions before copying to worlds instruction buffer
	std::mutex m_drawingMutex;
	std::vector<DrawInstruction> m_collectedDrawInstructions;

	void resetView();
	void updateView(float dt);

	void th_simulationLoop();
	void th_renderingLoop();

	void startSimulationThread();
	void stopSimulationThread();
	void startRenderingThread();
	void stopRenderingThread();

	sf::Vector2f getMouseWorldPos();
	sf::Vector2f toWorldPos(sf::Vector2f screenPos);

	void deleteWorld();



};

