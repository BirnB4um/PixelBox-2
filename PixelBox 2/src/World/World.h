#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Ruleset/Ruleset.h"
#include "WorldMetaData.h"
#include "DrawInstruction.h"
#include "../Tools/ByteSet.h"


class World
{
public:

	friend class Ruleset;

	World();

	//create World from metaData
	World(WorldMetaData& metaData);
	
	~World();

	const WorldMetaData& getMetaData();

	//deletes all pixels
	void clearWorld();

	//save the world to file
	//worldName determines the filename 
	bool save();

	//load from file
	bool load(WorldMetaData& metaData);

	//create the world from the metaData
	void createWorld();

	//set new MetaData for World.
	//if world is already created it gets changed to fit the new metaData
	void setMetaData(WorldMetaData& metaData);

	//returns true if the world is created
	inline bool isCreated() const;

	//tick simulation one step
	void tick();

	//draw all DrawInstructions to World
	void drawToWorld();

	void addDrawInstruction(DrawInstruction& drawInstruction);

	void updateRenderBuffer();

private:

	WorldMetaData m_metaData;
	uint8_t* m_worldDataFront;
	uint8_t* m_worldDataBack;
	uint8_t* m_worldRenderBuffer;

	ByteSet m_updateList;
	ByteSet m_updateListNext;
	ByteSet m_renderUpdates;//contains differences between last frame

	std::vector<DrawInstruction> m_drawInstructionList;


};

