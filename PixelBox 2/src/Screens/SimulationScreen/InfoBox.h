#pragma once
#include <SFML/Graphics.hpp>
#include "../../GUI/GUI.h"

class SimulationScreen;

class InfoBox
{
public:
	InfoBox();
	~InfoBox();

	void init(SimulationScreen* simulation);

	bool handleEvent(sf::Event& sfEvent);
	void update(float dt);
	void render(sf::RenderTarget& window);

	void onResize();
	void resetAll();

	void setHideGui(bool hide);

private:
	SimulationScreen* m_simulation;
	bool m_hideGui;

	Panel m_panel;
	TextRect m_infoTitle;
	TextRect m_infoText;
	TextRect m_dataText;

	int m_selectedData;
	GuiRect m_selectedDataRect;

	bool m_overPixel;
	sf::Vector2i m_hoveredPixelPos;
	uint32_t m_lastPixelData;

	std::vector<GuiElement*> m_guiElements;


};

