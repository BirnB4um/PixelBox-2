#include "World.h"

World::World() {
	m_metaData = WorldMetaData();
	m_worldDataFront = nullptr;
	m_worldDataBack = nullptr;
	m_worldRenderBuffer = nullptr;
}

World::World(WorldMetaData& metaData) : World() {
	setMetaData(metaData);
}

World::~World() {
	delete[] m_worldDataFront;
	delete[] m_worldDataBack;
	delete[] m_worldRenderBuffer;
}

const WorldMetaData& World::getMetaData() {
	return m_metaData;
}

void World::clearWorld() {
	if (isCreated()) {
		m_drawInstructionList.clear();
		memset(m_worldDataFront, 0, m_metaData.width * m_metaData.height * 4);
		memset(m_worldDataBack, 0, m_metaData.width * m_metaData.height * 4);
		memset(m_worldRenderBuffer, 0, m_metaData.width * m_metaData.height * 4);
		m_updateList.clear();
		m_updateListNext.clear();
		m_renderUpdates.clear();
	}
}

bool World::save() {
	//TODO:
	return true;
}

bool World::load(WorldMetaData& metaData) {
	//TODO:
	return true;
}

void World::setMetaData(WorldMetaData& metaData) {
	//change world
	if (isCreated()) {
		//TODO:
	}

	m_metaData = metaData;
}

bool World::isCreated() const {
	return m_worldDataFront != nullptr;
}

void World::createWorld() {
	delete[] m_worldDataFront;
	delete[] m_worldDataBack;
	delete[] m_worldRenderBuffer;

	//FIXME: allocate using uint32_t to ensure 4 byte alignment (for faster access)
	m_worldDataFront = new uint8_t[m_metaData.width * m_metaData.height * 4];
	m_worldDataBack = new uint8_t[m_metaData.width * m_metaData.height * 4];
	m_worldRenderBuffer = new uint8_t[m_metaData.width * m_metaData.height * 4];
	m_updateList.setMaxSize(m_metaData.width * m_metaData.height);
	m_updateListNext.setMaxSize(m_metaData.width * m_metaData.height);
	m_renderUpdates.setMaxSize(m_metaData.width * m_metaData.height);
	clearWorld();

	//DEBUG
	for (size_t i = 0; i < m_metaData.width * m_metaData.height * 4; i += 4) {
		m_worldRenderBuffer[i] = rand() % 255;
		m_worldRenderBuffer[i + 1] = rand() % 255;
		m_worldRenderBuffer[i + 2] = rand() % 255;
		m_worldRenderBuffer[i + 3] = 255;
	}
}

void World::tick() {
	if (!isCreated())
		return;

	//return if no pixels need to be updated
	int numPixelsToUpdate = m_updateList.size();
	if (numPixelsToUpdate == 0)
		return;

	//copy changed pixels
	for (size_t i : m_updateList.getItems()) {
		reinterpret_cast<uint32_t*>(m_worldDataBack)[i] = reinterpret_cast<uint32_t*>(m_worldDataFront)[i];
	}
	m_updateListNext.clear();

	//apply rules
	m_metaData.ruleset->updateAllPixels(this);

	//switch buffers
	m_updateList.swap(m_updateListNext);
	std::swap(m_worldDataFront, m_worldDataBack);
}

void World::drawToWorld() {
	if (isCreated() && m_drawInstructionList.size() > 0) {
		//TODO: draw to board. probably use mutex

		m_drawInstructionList.clear();
	}
}

void World::addDrawInstruction(DrawInstruction& drawInstruction) {
	if (isCreated()) {
		m_drawInstructionList.push_back(drawInstruction);
	}
}

void World::updateRenderBuffer() {
	for (size_t item : m_renderUpdates.getItems()) {
		reinterpret_cast<uint32_t*>(m_worldRenderBuffer)[item] = reinterpret_cast<uint32_t*>(m_worldDataFront)[item];
	}
	m_renderUpdates.clear();
}

bool World::renderBufferHasChanges() {
	return true;
	return m_renderUpdates.size() > 0;
}

uint8_t* World::getRenderBuffer() {
	return m_worldRenderBuffer;
}

void World::updateAllPixels() {
	for (size_t y = 1; y < m_metaData.height - 1; ++y) {
		for (size_t x = 1; x < m_metaData.width - 1; ++x) {
			size_t i = y * m_metaData.width + x;
			m_updateList.add(i);
		}
	}
}

void World::renderAllPixels() {
	for (size_t i = 0; i < m_metaData.width * m_metaData.height * 4; ++i) {
		m_worldRenderBuffer[i] = m_worldDataFront[i];
	}
	m_renderUpdates.add(0);
}