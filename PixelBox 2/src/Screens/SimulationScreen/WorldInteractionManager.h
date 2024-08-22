#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "../../World/DrawInstruction.h"
#include "../../GUI/GUI.h"

class SimulationScreen;

class WorldInteractionManager
{

public:
	WorldInteractionManager();
	~WorldInteractionManager();

	void init(SimulationScreen* simulation);
	bool handleEvent(sf::Event& sfEvent);
	void update(float dt);
	void render(sf::RenderTarget& window);
	void onResize();

	void resetAll();

	SpriteStateSwitch m_pauseSwitch;
	SpriteStateSwitch m_interactionSwitch;

	HorizontalValueSlider m_tpsSlider;
	HorizontalValueSlider m_brushSizeSlider;

	SpriteSwitch m_brushSwitch;
	SpriteSwitch m_lineSwitch;
	SpriteSwitch m_rectangleSwitch;
	SpriteSwitch m_circleSwitch;
	SpriteSwitch m_fillSwitch;
	SpriteSwitch m_selectionSwitch;

	SpriteSwitch m_gridSwitch;
	SpriteSwitch m_detailSwitch;
	SpriteButton m_resetButton;
	SpriteButton m_undoButton;

private:
	SimulationScreen* m_simulation;

	std::vector<GuiElement*> m_guiElements;

	bool m_isDrawing;
	sf::Vector2f m_startDrawingPosition;

	sf::RectangleShape m_linePreview;
	sf::RectangleShape m_rectPreview;
	sf::CircleShape m_circlePreview;

	void deactivateAllSwitches();




};

