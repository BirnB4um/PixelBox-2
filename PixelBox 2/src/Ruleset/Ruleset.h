#pragma once
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>

class World;

class Ruleset
{
public:

	Ruleset();
	virtual ~Ruleset();

	inline uint64_t getID() {
		return m_id;
	}

	virtual void updateAllPixels(World* world);
	virtual const bool updatePixel (size_t&index) const;
	virtual void addSurrondingPixels(size_t& index) const;

	sf::Texture* getPixelTexture() {
		return &m_pixels;
	}

	sf::Texture* getDetailedPixelTexture() {
		return &m_detailedPixels;
	}


protected:
	uint64_t m_id;
	sf::Texture m_pixels;
	sf::Texture m_detailedPixels;

	//temp values for updating pixels
	World* world;
	size_t width;
	size_t height;
	uint8_t* frontBuffer;
	uint8_t* backBuffer;
};

