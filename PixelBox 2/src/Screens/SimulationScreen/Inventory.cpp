#include "Inventory.h"

#include "../../Application.h"
#include "SimulationScreen.h"


Inventory::Inventory() {
	m_simulation = nullptr;
	m_showInventory = true;
	m_hideGui = false;

}

Inventory::~Inventory() {

}

void Inventory::init(SimulationScreen* simulation) {
	m_simulation = simulation;

	m_inventoryPanel.setSliderWidth(20.0f);
	m_inventoryPanel.setScrollable(true, false);
	m_guiElement.push_back(&m_inventoryPanel);

	m_selectedPixelButton.setBorderWidth(4.0f);
	m_selectedPixelButton.setSpritePadding(1.0f);
	m_selectedPixelButton.setFunction(
		[this]() {
			setInventoryVisible(!isInventoryVisible());
		}
	);
	m_guiElement.push_back(&m_selectedPixelButton);

	for (GuiElement* element : m_guiElement) {
		element->reloadResources();
	}
	onResize();
}

bool Inventory::handleEvent(sf::Event& sfEvent) {

	if (!m_hideGui) {
		if (m_selectedPixelButton.handleEvent(sfEvent))
			return true;

		if (m_inventoryPanel.handleEvent(sfEvent) && m_showInventory)
			return true;
	}

	switch (sfEvent.type)
	{

	case sf::Event::KeyReleased:
		if (sfEvent.key.code == sf::Keyboard::E) {
			m_selectedPixelButton.callFunction();
			return true;
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (sfEvent.mouseButton.button == sf::Mouse::Right) {

			//select pixel
			sf::FloatRect worldRect = sf::FloatRect(0.0f, 0.0f, m_simulation->m_world->getMetaData().width, m_simulation->m_world->getMetaData().height);
			sf::Vector2i mouse = static_cast<sf::Vector2i>(m_simulation->getMouseWorldPos());
			if (worldRect.contains(m_simulation->getMouseWorldPos())) {
				setSelectedPixel(m_simulation->m_world->getPixel(mouse.x, mouse.y));
				return true;
			}
			

		}
		break;
	default:
		break;
	}
	return false;
}

void Inventory::update(float dt) {
	if (!m_hideGui) {
		if (m_showInventory)
			m_inventoryPanel.update(dt);

		m_selectedPixelButton.update(dt);
	}
}

void Inventory::render(sf::RenderTarget& window) {
	if (!m_hideGui) {
		if (m_showInventory)
			m_inventoryPanel.render(window);

		m_selectedPixelButton.render(window);
	}
}

void Inventory::onResize() {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());
	float panelWidth = 300.0f;
	m_inventoryPanel.setBounds(windowSize.x - panelWidth, 0.0f, panelWidth, windowSize.y);

	float width = 60.0f;
	float padding = 5.0f;
	m_selectedPixelButton.setBounds(windowSize.x - (m_showInventory ? panelWidth : 0.0f) - width - padding, padding, width, width);


	//resize inventory
	panelWidth -= m_inventoryPanel.getSliderWidth() - m_inventoryPanel.getBorderWidth() * 2.0f;

	m_inventoryTitle.setBounds(0.0f, 0.0f, panelWidth, 50.0f);

	float y = 60.0f;
	float x = 5.0f;
	width = 50.0f;
	padding = 12.0f;
	int buttonsPerRow = floor((panelWidth - x) / (width + padding));

	for (InventoryCategory& category : m_inventoryCategories) {

		category.name.setBounds(x, y, panelWidth - x, 30);

		y += 35.0f;

		int colCount = 0;
		float buttonX = x;

		for (InventoryItem& item : category.items) {
			item.button.setBounds(buttonX, y, width, width);
			item.name.setBounds(buttonX - padding / 2.0f, y + width, width + padding, 20);

			colCount++;
			buttonX += width + padding;
			if (colCount >= buttonsPerRow) {
				y += width + 25.0f;
				buttonX = x;
				colCount = 0;
			}
		}

		y += width + 50.0f;
	}

}

void Inventory::resetAll() {
	m_inventoryPanel.resetInteractionState();

	m_inventoryPanel.resetInteractionState();

}

void Inventory::createFromRuleset(Ruleset* ruleset) {


	m_selectedPixelButton.setTexture(ruleset->getInventoryTexture());

	m_inventoryPanel.clearElements();

	//Title
	m_inventoryTitle.reloadResources();
	m_inventoryTitle.setText("Inventory");
	m_inventoryTitle.setAlignment(TextRect::Alignment::CenterLeft);
	m_inventoryTitle.setFontSize(30);
	m_inventoryPanel.addElement(&m_inventoryTitle);


	//Categories
	m_inventoryCategories.clear();


	for (const Ruleset::InventoryCategory& category : ruleset->getInventory()) {

		InventoryCategory invCategory;

		//Category name
		invCategory.name.reloadResources();
		invCategory.name.setText(category.name);
		invCategory.name.setFontSize(20);
		invCategory.name.setAlignment(TextRect::Alignment::CenterLeft);

		//Category items
		for (const Ruleset::InventoryItem& item : category.items) {

			InventoryItem invItem;
			
			//Button
			invItem.button.reloadResources();
			invItem.button.setTexturePatch(item.rect);
			invItem.button.setFunction([this, item]() {
				setSelectedPixel(item.data);
				});
			invItem.button.setSpritePadding(1.0f);
			invItem.button.setTexture(ruleset->getInventoryTexture());


			//Name
			invItem.name.reloadResources();
			invItem.name.setText(item.name);
			invItem.name.setFontSize(9);
			invItem.name.setAlignment(TextRect::Alignment::Center);


			invCategory.items.push_back(invItem);

		}

		m_inventoryCategories.push_back(invCategory);
	}

	//add to panel
	for (InventoryCategory& category : m_inventoryCategories) {
		m_inventoryPanel.addElement(&category.name);
		for (InventoryItem& item : category.items) {
			m_inventoryPanel.addElement(&item.button);
			m_inventoryPanel.addElement(&item.name);
		}
	}

	//set initial item
	bool foundItem = false;
	for (InventoryCategory& category : m_inventoryCategories) {
		for (InventoryItem& item : category.items) {
			item.button.callFunction();
			foundItem = true;
			break;
		}
		if (foundItem)
			break;
	}

	m_inventoryPanel.resetSliders();

	onResize();
}

void Inventory::setInventoryVisible(bool visible) {
	m_showInventory = visible;
	onResize();
}

void Inventory::setSelectedPixel(PixelData pixel) {
	setSelectedPixel(pixel.toUInt32());
}

void Inventory::setSelectedPixel(uint32_t pixel) {
	m_selectedPixel.fromUInt32(pixel);

	//get texture rect from id
	sf::IntRect area = m_simulation->m_world->getMetaData().ruleset->getItemFromID(m_selectedPixel.id).rect;
	m_selectedPixelButton.setTexturePatch(area);
}