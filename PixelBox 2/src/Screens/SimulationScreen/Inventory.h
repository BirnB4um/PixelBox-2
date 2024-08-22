#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "../../World/DrawInstruction.h"
#include "../../World/PixelData.h"
#include "../../Ruleset/Ruleset.h"
#include "../../GUI/GUI.h"

class SimulationScreen;

class Inventory
{
public:

	Inventory();
	~Inventory();

	void init(SimulationScreen* simulation);
	bool handleEvent(sf::Event& sfEvent);
	void update(float dt);
	void render(sf::RenderTarget& window);
	void onResize();

	void resetAll();
	void createFromRuleset(Ruleset* ruleset);

	inline PixelData getSelectedPixel() const { return m_selectedPixel; }

private:
	SimulationScreen* m_simulation;

	PixelData m_selectedPixel;
	SpriteButton m_selectedPixelButton;

	ScrollPanel m_inventoryPanel;
	TextRect m_inventoryTitle;
	std::vector<TextRect> m_inventoryCategories;
	std::vector<SpriteButton> m_inventoryButtons;
	std::vector<TextRect> m_inventoryButtonNames;

};

