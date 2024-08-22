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
	item = { "Air", {0,0,0,0}, sf::IntRect(0, 0, 16, 16) }; category.items.push_back(item);
	item = { "Wire", {1,0,0,0}, sf::IntRect(0, 16, 16, 16) }; category.items.push_back(item);
	item = { "Output", {2,0,0,0}, sf::IntRect(0, 32, 16, 16) }; category.items.push_back(item);
	item = { "Battery", {3,0,0,0}, sf::IntRect(0, 48, 16, 16) }; category.items.push_back(item);
	item = { "Delay", {4,0,0,0}, sf::IntRect(0, 64, 16, 16) }; category.items.push_back(item);
	item = { "Bridge", {5,0,0,0}, sf::IntRect(0, 80, 16, 16) }; category.items.push_back(item);
	item = { "Lamp", {6,0,0,0}, sf::IntRect(0, 96, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	category.name = "Logic gates";
	category.items.clear();
	item = { "NOT", {9,0,0,0}, sf::IntRect(0, 112, 16, 16) }; category.items.push_back(item);
	item = { "OR", {10,0,0,0}, sf::IntRect(0, 128, 16, 16) }; category.items.push_back(item);
	item = { "NOR", {11,0,0,0}, sf::IntRect(0, 144, 16, 16) }; category.items.push_back(item);
	item = { "XOR", {12,0,0,0}, sf::IntRect(0, 160, 16, 16) }; category.items.push_back(item);
	item = { "XNOR", {13,0,0,0}, sf::IntRect(0, 176, 16, 16) }; category.items.push_back(item);
	item = { "AND", {14,0,0,0}, sf::IntRect(0, 192, 16, 16) }; category.items.push_back(item);
	item = { "NAND", {15,0,0,0}, sf::IntRect(0, 208, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	category.name = "Special";
	category.items.clear();
	item = { "Button", {7,0,0,0}, sf::IntRect(0, 224, 16, 16) }; category.items.push_back(item);
	item = { "Switch", {8,0,0,0}, sf::IntRect(0, 240, 16, 16) }; category.items.push_back(item);
	item = { "Clock", {16,0,0,0}, sf::IntRect(16, 0, 16, 16) }; category.items.push_back(item);
	item = { "Debug", {17,0,0,0}, sf::IntRect(16, 16, 16, 16) }; category.items.push_back(item);
	m_inventory.push_back(category);

	//DEBUG
	//for (InventoryCategory& category : m_inventory) {
	//	std::cout << category.name << "\n";
	//	for (InventoryItem& item : category.items) {
	//		std::cout << item.name << ", " << item.data.toUInt32() << ", " << item.rect.left << "/" << item.rect.top << "/" << item.rect.width << "/" << item.rect.height << "\n";
	//	}
	//	std::cout << "\n";
	//}
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