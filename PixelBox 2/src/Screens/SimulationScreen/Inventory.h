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

	void setInventoryVisible(bool visible);
	inline bool isInventoryVisible() const { return m_showInventory; }

	void setSelectedPixel(PixelData pixel);
	void setSelectedPixel(uint32_t pixel);
	inline PixelData getSelectedPixel() const { return m_selectedPixel; }

private:

	struct InventoryItem {
		TextRect name;
		SpriteButton button;
	};

	struct InventoryCategory {
		TextRect name;
		std::vector<InventoryItem> items;
	};

	bool m_showInventory;

	SimulationScreen* m_simulation;
	std::vector<GuiElement*> m_guiElement;

	PixelData m_selectedPixel;
	SpriteButton m_selectedPixelButton;

	ScrollPanel m_inventoryPanel;
	TextRect m_inventoryTitle;
	std::vector<InventoryCategory> m_inventoryCategories;

};

