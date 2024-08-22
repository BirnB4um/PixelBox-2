#pragma once
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../World/PixelData.h"

class World;

class Ruleset
{
public:

	struct InventoryItem {
		std::string name = "";
		PixelData data;
		sf::IntRect rect;
	};
	struct InventoryCategory {
		std::string name;
		std::vector<InventoryItem> items;
	};

	Ruleset();
	virtual ~Ruleset();

	inline uint64_t getID() {
		return m_id;
	}

	virtual void updateAllPixels(World* world);
	virtual const bool updatePixel (size_t&index) const;
	virtual void addSurrondingPixels(size_t& index) const;

	inline sf::Texture* getPixelTexture() {
		return &m_pixels;
	}

	inline sf::Texture* getDetailedPixelTexture() {
		return &m_detailedPixels;
	}

	inline sf::Texture* getInventoryTexture() {
		return &m_inventoryTexture;
	}

	inline const std::vector<InventoryCategory>& getInventory() const {
		return m_inventory;
	}

	InventoryItem getItemFromID(uint8_t id);


protected:
	uint64_t m_id;
	sf::Texture m_pixels;
	sf::Texture m_detailedPixels;
	sf::Texture m_inventoryTexture;


	std::vector<InventoryCategory> m_inventory;

	//temp values for updating pixels
	World* world;
	size_t width;
	size_t height;
	uint8_t* frontBuffer;
	uint8_t* backBuffer;

	virtual void createInventory();
};

