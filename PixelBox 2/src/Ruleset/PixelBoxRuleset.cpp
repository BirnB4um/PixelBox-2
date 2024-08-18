#include "PixelBoxRuleset.h"
#include "../World/World.h"


PixelBoxRuleset::PixelBoxRuleset() {
	m_id = 2;

	frontBuffer = nullptr;
	backBuffer = nullptr;
	width = 0;
	height = 0;
}

PixelBoxRuleset::~PixelBoxRuleset() {

}

void PixelBoxRuleset::updateAllPixels(World* world) {
	this->world = world;
	width = world->m_metaData.width;
	height = world->m_metaData.height;

	frontBuffer = world->m_worldDataFront;
	backBuffer = world->m_worldDataBack;

	//TODO: update from bottom to top

	for (size_t index : world->m_updateList.getItems()) {
		if (updatePixel(index)) {
			addSurrondingPixels(index);
		}
	}

}

const bool PixelBoxRuleset::updatePixel(size_t& index) const {

	//FIXME: optimize by using bitshift, calculating indecies on the fly (as rvalues)

	uint8_t* valueIndex = &world->m_worldDataFront[index * 4];

	//direct neighbours
	uint8_t* topIndex = valueIndex - width * 4;
	uint8_t* bottomIndex = valueIndex + width * 4;
	uint8_t* leftIndex = valueIndex - 4;
	uint8_t* rightIndex = valueIndex + 4;

	//corner neighbours
	uint8_t* topRightIndex = topIndex + 4;
	uint8_t* topLeftIndex = topIndex - 4;
	uint8_t* bottomRightIndex = bottomIndex + 4;
	uint8_t* bottomLeftIndex = bottomIndex - 4;


	//read from frontBuffer, write to backBuffer


	return false;
}

void PixelBoxRuleset::addSurrondingPixels(size_t& index) const {

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
		if (notTop) {
			world->m_updateListNext.add(index - width - 1);//top left
		}
		if (notBottom) {
			world->m_updateListNext.add(index + width - 1);//bottom left
		}
	}
	if (notRight) {
		world->m_updateListNext.add(index + 1);//right
		if (notTop) {
			world->m_updateListNext.add(index - width + 1);//top right
		}
		if (notBottom) {
			world->m_updateListNext.add(index + width + 1);//bottom right
		}
	}
	if (notTop) {
		world->m_updateListNext.add(index - width);//top
	}
	if (notBottom) {
		world->m_updateListNext.add(index + height);//bottom
	}

}