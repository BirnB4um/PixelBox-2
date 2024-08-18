#pragma once
#include <cstdint>
#include <vector>

class World;

class Ruleset
{
public:

	Ruleset();
	~Ruleset();

	inline uint64_t getID() {
		return m_id;
	}

	virtual void updateAllPixels(World* world);
	virtual const bool updatePixel (size_t&index) const;
	virtual void addSurrondingPixels(size_t& index) const;


protected:
	uint64_t m_id;

	//temp values for updating pixels
	World* world;
	size_t width;
	size_t height;
	uint8_t* frontBuffer;
	uint8_t* backBuffer;
};

