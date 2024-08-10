#pragma once

#include <cstdint>
#include <string>
#include "../Ruleset/Ruleset.h"
#include "WorldMetaData.h"

class World
{
public:

	World();

	//create World from metaData
	World(WorldMetaData& metaData);
	
	~World();

	//deletes all pixels
	void clear();

	//save the world to file
	bool save();

	//load from file
	bool load(WorldMetaData& metaData);

	//set new name, dimensions and ruleset.
	//if dimensions changed either extend or shrink the board
	//if world isn't created yet, create it from the metaData
	void setMetaData(WorldMetaData& metaData);

private:

	WorldMetaData m_metaData;
	uint8_t* m_worldData;

};

