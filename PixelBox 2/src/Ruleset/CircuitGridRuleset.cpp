#include "CircuitGridRuleset.h"
#include "../World/World.h"


CircuitGridRuleset::CircuitGridRuleset() {
	m_id = 1;

	if (!m_pixels.loadFromFile("res/textures/CircuitGrid/pixels.png")) {
		throw std::runtime_error("Error loading res/textures/CircuitGrid/pixels.png");
	}

	if (!m_detailedPixels.loadFromFile("res/textures/CircuitGrid/detailed_pixels.png")) {
		throw std::runtime_error("Error loading res/textures/CircuitGrid/detailed_pixels.png");
	}

	frontBuffer = nullptr;
	backBuffer = nullptr;
	width = 0;
	height = 0;
}

CircuitGridRuleset::~CircuitGridRuleset() {

}

void CircuitGridRuleset::updateAllPixels(World* world) {
	this->world = world;
	width = world->m_metaData.width;
	height = world->m_metaData.height;

	frontBuffer = world->m_worldDataFront;
	backBuffer = world->m_worldDataBack;

	for (size_t index : world->m_updateList.getItems()) {
		if (updatePixel(index)) {
			addSurrondingPixels(index);
		}
	}

}

const bool CircuitGridRuleset::updatePixel(size_t& index) const {

	//FIXME: optimize by using bitshift, calculating indecies on the fly (as rvalues)

	uint8_t* valueIndex = &world->m_worldDataFront[index * 4];

	//direct neighbours
	uint8_t* topIndex = valueIndex - width * 4;
	uint8_t* bottomIndex = valueIndex + width * 4;
	uint8_t* leftIndex = valueIndex - 4;
	uint8_t* rightIndex = valueIndex + 4;



	//read from frontBuffer, write to backBuffer


	return false;
}

void CircuitGridRuleset::addSurrondingPixels(size_t& index) const {

	//update pixels from updateList, save next updates to updateListNext + renderUpdates

	world->m_updateListNext.add(index);
	world->m_renderUpdates.add(index);

	bool notTop = index >= width * 2;
	bool notBottom = index < width * height - width * 2;
	bool notLeft = index % width > 1;
	bool notRight = index % width < width - 2;

	//update direct neighbours
	if (notLeft) {
		world->m_updateListNext.add(index - 1);//left
	}
	if (notRight) {
		world->m_updateListNext.add(index + 1);//right
	}
	if (notTop) {
		world->m_updateListNext.add(index - width);//top
	}
	if (notBottom) {
		world->m_updateListNext.add(index + height);//bottom
	}

}