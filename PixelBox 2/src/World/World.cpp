#include "World.h"

World::World() {
	m_metaData = WorldMetaData();
	m_worldData = nullptr;
}

World::World(WorldMetaData& metaData): World() {
	setMetaData(metaData);
}

World::~World() {
	delete[] m_worldData;
}

void World::clear() {

}

bool World::save() {
	return true;
}

bool World::load(WorldMetaData& metaData) {
	return true;
}

void World::setMetaData(WorldMetaData& metaData) {

	//create new world
	if (m_worldData == nullptr) {
		m_metaData = metaData;
		m_worldData = new uint8_t[m_metaData.width * m_metaData.height * 4];
		memset(m_worldData, 0, m_metaData.width * m_metaData.height * 4);

	}

	//change world
	else {
		//TODO:

	}


}




