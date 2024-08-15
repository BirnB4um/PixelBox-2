#include "Ruleset.h"
#include "../World/World.h"

Ruleset::Ruleset() {
	m_id = 0;
}

Ruleset::~Ruleset() {

}


uint64_t Ruleset::getID() {
	return m_id;
}

void Ruleset::updateAllPixels(World* world) const {
	unsigned int width = world->m_metaData.width;
	unsigned int height = world->m_metaData.height;

	uint8_t* frontBuffer = world->m_worldDataFront;
	uint8_t* backBuffer = world->m_worldDataBack;

	
	//read from frontBuffer, write to backBuffer + renderBuffer
	//update pixels from updateList, save next updates to updateListNext


}