#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Ruleset/Ruleset.h"
#include "../Ruleset/CircuitGridRuleset.h"
#include "../Ruleset/PixelBoxRuleset.h"
#include "../Ruleset/CustomRuleset.h"
#include "WorldMetaData.h"
#include "DrawInstruction.h"
#include "../Tools/ByteSet.h"
#include "../Tools/Utils.h"


class World
{
public:

	friend class Ruleset;
	friend class CircuitGridRuleset;
	friend class PixelBoxRuleset;
	friend class CustomRuleset;

	World();

	//create World from metaData
	World(WorldMetaData& metaData);
	
	~World();

	const WorldMetaData& getMetaData();

	//deletes all pixels
	void clearWorld();

	//reset pixels to default value
	void resetWorld();

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
	void redrawWorld();

	void addDrawInstruction(DrawInstruction& drawInstruction);
	void addDrawInstruction(std::vector<DrawInstruction>& drawInstructionList);

	void updateRenderBuffer();
	bool renderBufferHasChanges();

	uint8_t* getRenderBuffer();

	//add all pixels to update queue
	void updateAllPixels();

	uint32_t getPixel(size_t x, size_t y);

private:

	WorldMetaData m_metaData;
	uint8_t* m_worldDataFront;
	uint8_t* m_worldDataBack;
	uint8_t* m_worldRenderBuffer;

	ByteSet m_updateList;
	ByteSet m_updateListNext;
	ByteSet m_renderUpdates;//contains indecies of differences between now and last rendered frame

	std::vector<DrawInstruction> m_drawInstructionList;


};

