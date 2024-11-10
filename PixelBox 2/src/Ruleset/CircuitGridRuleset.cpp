#include "CircuitGridRuleset.h"
#include "../World/World.h"
#include "../Application.h"

CircuitGridRuleset::CircuitGridRuleset() {
	m_id = 1;

	if (!m_pixels.loadFromFile("res/textures/CircuitGrid/pixels.png")) {
		throw std::runtime_error("Error loading res/textures/CircuitGrid/pixels.png");
	}

	if (!m_detailedPixels.loadFromFile("res/textures/CircuitGrid/detailed_pixels.png")) {
		throw std::runtime_error("Error loading res/textures/CircuitGrid/detailed_pixels.png");
	}

	if (!m_inventoryTexture.loadFromFile("res/textures/CircuitGrid/inventory.png")) {
		throw std::runtime_error("Error loading res/textures/CircuitGrid/inventory.png");
	}

	createInventory();

	frontBuffer = nullptr;
	backBuffer = nullptr;
	width = 0;
	height = 0;
}

CircuitGridRuleset::~CircuitGridRuleset() {
}

void CircuitGridRuleset::createInventory() {
	InventoryCategory category;
	InventoryItem item;

	category.name = "Stuff";
	category.items.clear();
	item = { "Air", {AIR,0,0,0}, sf::IntRect(0, 0, 16, 16) }; category.items.push_back(item);
	item = { "Wire", {WIRE,1,0,0}, sf::IntRect(0, 16, 16, 16) }; category.items.push_back(item);
	item = { "Output", {OUTPUT,1,0,0}, sf::IntRect(0, 32, 16, 16) }; category.items.push_back(item);
	item = { "Battery", {BATTERY,2,0,0}, sf::IntRect(0, 48, 16, 16) }; category.items.push_back(item);
	item = { "Delay", {DELAY,1,3,0}, sf::IntRect(0, 64, 16, 16) }; category.items.push_back(item);
	item = { "Bridge", {BRIDGE,1,1,0}, sf::IntRect(0, 80, 16, 16) }; category.items.push_back(item);
	item = { "Lamp", {LAMP,1,0,0}, sf::IntRect(0, 96, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	category.name = "Logic gates";
	category.items.clear();
	item = { "NOT", {NOT,0,0,0}, sf::IntRect(0, 112, 16, 16) }; category.items.push_back(item);
	item = { "OR", {OR,0,0,0}, sf::IntRect(0, 128, 16, 16) }; category.items.push_back(item);
	item = { "NOR", {NOR,0,0,0}, sf::IntRect(0, 144, 16, 16) }; category.items.push_back(item);
	item = { "XOR", {XOR,0,0,0}, sf::IntRect(0, 160, 16, 16) }; category.items.push_back(item);
	item = { "XNOR", {XNOR,0,0,0}, sf::IntRect(0, 176, 16, 16) }; category.items.push_back(item);
	item = { "AND", {AND,0,0,0}, sf::IntRect(0, 192, 16, 16) }; category.items.push_back(item);
	item = { "NAND", {NAND,0,0,0}, sf::IntRect(0, 208, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	category.name = "Special";
	category.items.clear();
	item = { "Button", {BUTTON,1,0,0}, sf::IntRect(0, 224, 16, 16) }; category.items.push_back(item);
	item = { "Switch", {SWITCH,1,0,0}, sf::IntRect(0, 240, 16, 16) }; category.items.push_back(item);
	item = { "Clock", {CLOCK,0,100,0}, sf::IntRect(16, 0, 16, 16) }; category.items.push_back(item);
	item = { "Debug", {DEBUG,0,0,0}, sf::IntRect(16, 16, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	//create default pixeldata
	for (InventoryCategory& category : m_inventory) {
		for (InventoryItem& item : category.items) {
			m_defaultPixelData[item.data.id] = item.data.toUInt32();
		}
	}
}

PixelData CircuitGridRuleset::getPixelInteractionResult(PixelData pixel) {

	if (pixel.id == SWITCH or pixel.id == BUTTON) {
		if (pixel.data1 == 1) {
			pixel.data1 = 2;
		}
		else if (pixel.data1 == 2) {
			pixel.data1 = 0;
		}
	}

	return pixel;
}

void CircuitGridRuleset::updateAllPixels(World* world) {
	this->world = world;
	width = world->m_metaData.width;
	height = world->m_metaData.height;
	frontBuffer = world->m_worldDataFront;
	backBuffer = world->m_worldDataBack;

	for (size_t index : world->m_updateList) {
		if (updatePixel(index)) {
			addSurroundingPixels(index);
		}
	}
}

void CircuitGridRuleset::addSurroundingPixels(size_t& index) const {
	//update pixels from updateList, save next updates to updateListNext + renderUpdates

	world->m_updateListNext.add(index);

	world->m_renderUpdates.add(index);
	//reinterpret_cast<uint32_t*>(world->m_worldRenderBuffer)[index] = reinterpret_cast<uint32_t*>(world->m_worldDataBack)[index];

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

const bool CircuitGridRuleset::updatePixel(size_t& index) const {
	//FIXME: optimize by using bitshift, calculating indecies on the fly (as rvalues)

	uint8_t* valuePtr = &frontBuffer[index * 4];
	uint8_t* nextValuePtr = &backBuffer[index * 4];

	//direct neighbours
	uint8_t* topIndex = valuePtr - width * 4;
	uint8_t* bottomIndex = valuePtr + width * 4;
	uint8_t* leftIndex = valuePtr - 4;
	uint8_t* rightIndex = valuePtr + 4;

	//read from frontBuffer, write to backBuffer

	switch (*valuePtr)
	{
	case AIR:
		return false;

	case WIRE:

	{
		uint8_t surrounding_data = 0;//0b01:nachbar ist 0; 0b10:nachbar ist 2

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE) {
			if (leftIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (leftIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE) {
			if (rightIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (rightIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		if (*(valuePtr + 1) == 0) {//if off -> normal
			nextValuePtr[1] = 1;
		}
		else if (*(valuePtr + 1) == 2 && surrounding_data & 0b1) {//if on && surrounding off -> off
			nextValuePtr[1] = 0;
		}
		else if (*(valuePtr + 1) == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}

	case OUTPUT:
	{
		//set off
		nextValuePtr[1] = 0;

		//up
		if (*topIndex >= BUTTON) {
			if (topIndex[1] > 1) {
				nextValuePtr[1] = 2;
			}
		}
		//left
		if (*leftIndex >= BUTTON) {
			if (leftIndex[1] > 1) {
				nextValuePtr[1] = 2;
			}
		}
		//right
		if (*rightIndex >= BUTTON) {
			if (rightIndex[1] > 1) {
				nextValuePtr[1] = 2;
			}
		}
		//down
		if (*bottomIndex >= BUTTON) {
			if (bottomIndex[1] > 1) {
				nextValuePtr[1] = 2;
			}
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case BATTERY:
		return false;
		break;

	case DELAY:
	{
		uint8_t surrounding_data = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE) {
			if (leftIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (leftIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE) {
			if (rightIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (rightIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		if (valuePtr[1] == 0) {//if off -> normal
			nextValuePtr[1] = 1;
		}
		else if (valuePtr[1] > 1) {
			if (surrounding_data & 0b1) {//if on && surrounding off -> off
				nextValuePtr[1] = 0;
			}
			else if (valuePtr[1] > 2) {//if over activ -> --
				nextValuePtr[1] = valuePtr[1] - 1;
			}
		}
		else if (valuePtr[1] == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
			nextValuePtr[1] = valuePtr[2];
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case BRIDGE:
	{
		uint8_t surrounding_data_vertical = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2
		uint8_t surrounding_data_horizonatal = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data_vertical = surrounding_data_vertical | 0b1;
			}
			else if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data_vertical = surrounding_data_vertical | 0b10;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data_vertical = surrounding_data_vertical | 0b1;
			}
			else if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data_vertical = surrounding_data_vertical | 0b10;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE) {
			if (leftIndex[1] == 0) {
				surrounding_data_horizonatal = surrounding_data_horizonatal | 0b1;
			}
			else if (leftIndex[1] == 2) {
				surrounding_data_horizonatal = surrounding_data_horizonatal | 0b10;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE) {
			if (rightIndex[1] == 0) {
				surrounding_data_horizonatal = surrounding_data_horizonatal | 0b1;
			}
			else if (rightIndex[1] == 2) {
				surrounding_data_horizonatal = surrounding_data_horizonatal | 0b10;
			}
		}

		//vertical
		if (valuePtr[2] == 0) {//if off -> normal
			nextValuePtr[2] = 1;
		}
		else if (valuePtr[2] == 2 && surrounding_data_vertical & 0b1) {//if on && surrounding off -> off
			nextValuePtr[2] = 0;
		}
		else if (valuePtr[2] == 1 && surrounding_data_vertical & 0b10) {//if normal && surrounding on -> on
			nextValuePtr[2] = 2;
		}

		//horizontal
		if (valuePtr[1] == 0) {//if off -> normal
			nextValuePtr[1] = 1;
		}
		else if (valuePtr[1] == 2 && surrounding_data_horizonatal & 0b1) {//if on && surrounding off -> off
			nextValuePtr[1] = 0;
		}
		else if (valuePtr[1] == 1 && surrounding_data_horizonatal & 0b10) {//if normal && surrounding on -> on
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case LAMP:
	{
		uint8_t surrounding_data = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}
		else if (*topIndex == LAMP) {
			if (topIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (topIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}
		else if (*bottomIndex == LAMP) {
			if (bottomIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (bottomIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE) {
			if (leftIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (leftIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}
		else if (*leftIndex == LAMP) {
			if (leftIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (leftIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE) {
			if (rightIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (rightIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}
		else if (*rightIndex == LAMP) {
			if (rightIndex[1] == 0) {
				surrounding_data = surrounding_data | 0b1;
			}
			else if (rightIndex[1] == 2) {
				surrounding_data = surrounding_data | 0b10;
			}
		}

		if (valuePtr[1] == 0) {//if off -> normal
			nextValuePtr[1] = 1;
		}
		else if (valuePtr[1] == 2 && surrounding_data & 0b1) {//if on && surrounding off -> off
			nextValuePtr[1] = 0;
		}
		else if (valuePtr[1] == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case BUTTON:
	{
		bool surrounding_on = false;

		//up
		if (*topIndex == BUTTON) {
			if (topIndex[1] > 1) {
				surrounding_on = true;
			}
		}
		//left
		if (*leftIndex == BUTTON) {
			if (leftIndex[1] > 1) {
				surrounding_on = true;
			}
		}
		//right
		if (*rightIndex == BUTTON) {
			if (rightIndex[1] > 1) {
				surrounding_on = true;
			}
		}
		//down
		if (*bottomIndex == BUTTON) {
			if (bottomIndex[1] > 1) {
				surrounding_on = true;
			}
		}

		if (valuePtr[1] == 0) {//if off -> neutral
			nextValuePtr[1] = 1;
		}
		else if (valuePtr[1] == 2) {//if on -> off
			nextValuePtr[1] = 0;
		}
		else if (surrounding_on) {//if other on -> on
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case SWITCH:
	{
		bool surrounding_on = false;
		bool surrounding_off = false;

		//up
		if (*topIndex == SWITCH) {
			if (topIndex[1] > 1) {
				surrounding_on = true;
			}
			else if (topIndex[1] == 0) {
				surrounding_off = true;
			}
		}
		//left
		if (*leftIndex == SWITCH) {
			if (leftIndex[1] > 1) {
				surrounding_on = true;
			}
			else if (leftIndex[1] == 0) {
				surrounding_off = true;
			}
		}
		//right
		if (*rightIndex == SWITCH) {
			if (rightIndex[1] > 1) {
				surrounding_on = true;
			}
			else if (rightIndex[1] == 0) {
				surrounding_off = true;
			}
		}
		//down
		if (*bottomIndex == SWITCH) {
			if (bottomIndex[1] > 1) {
				surrounding_on = true;
			}
			else if (bottomIndex[1] == 0) {
				surrounding_off = true;
			}
		}

		if (valuePtr[1] == 0) {//if off -> neutral
			nextValuePtr[1] = 1;
		}
		else if (valuePtr[1] == 2 && surrounding_off) {//if on -> off
			nextValuePtr[1] = 0;
		}
		else if (surrounding_on) {//if other on -> on
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case NOT:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count > 0) {
			nextValuePtr[1] = 0;
		}
		else {
			nextValuePtr[1] = 2;
		}

		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case OR:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count > 0) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case NOR:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count == 0) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case XOR:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count == 1) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case XNOR:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count != 1) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case AND:
	{
		uint8_t surrounding_electricity_count = 0;
		uint8_t surrounding_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		if (surrounding_electricity_count == surrounding_count) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case NAND:
	{
		uint8_t surrounding_electricity_count = 0;
		uint8_t surrounding_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
			surrounding_count++;
		}

		if (surrounding_electricity_count != surrounding_count) {
			nextValuePtr[1] = 2;
		}
		else {
			nextValuePtr[1] = 0;
		}
		return *reinterpret_cast<uint32_t*>(valuePtr) != *reinterpret_cast<uint32_t*>(nextValuePtr);
	}
	break;

	case CLOCK:
	{
		int next_value = valuePtr[3];
		next_value -= world->getTimeSinceLastTick() / 10;
		next_value = Utils::constrain(next_value, 0, 255);
		if (next_value == 0) {
			nextValuePtr[1] = 2;
			next_value = valuePtr[2];
		}
		else {
			nextValuePtr[1] = 0;
		}
		nextValuePtr[3] = next_value;

		return true;
	}
	break;

	case DEBUG:
	{
		uint8_t surrounding_electricity_count = 0;

		//up
		if (*topIndex > AIR && *topIndex <= BRIDGE && *topIndex != OUTPUT) {
			if (topIndex[*topIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//down
		if (*bottomIndex > AIR && *bottomIndex <= BRIDGE && *bottomIndex != OUTPUT) {
			if (bottomIndex[*bottomIndex == BRIDGE ? 2 : 1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//left
		if (*leftIndex > AIR && *leftIndex <= BRIDGE && *leftIndex != OUTPUT) {
			if (leftIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		//right
		if (*rightIndex > AIR && *rightIndex <= BRIDGE && *rightIndex != OUTPUT) {
			if (rightIndex[1] == 2) {
				surrounding_electricity_count++;
			}
		}

		if (surrounding_electricity_count > 0) {
			Application::instance().simulationScreen.setSimulationPaused(true);
			return true;
		}

		return false;
	}
	break;

	default:
		return false;
	}

}