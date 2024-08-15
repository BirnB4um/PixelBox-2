#pragma once

#include <cstdint>
#include <vector>

class World;

class Ruleset
{
public:

	Ruleset();
	~Ruleset();

	inline uint64_t getID();

	inline void updateAllPixels(World* world) const;


private:
	uint64_t m_id;
};

