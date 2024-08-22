#include "Inventory.h"

#include "../../Application.h"
#include "SimulationScreen.h"


Inventory::Inventory() {
	m_simulation = nullptr;

}

Inventory::~Inventory() {

}

void Inventory::init(SimulationScreen* simulation) {
	m_simulation = simulation;

	m_inventoryPanel.setSliderWidth(20.0f);
	m_inventoryPanel.setScrollable(true, false);
	m_simulation->addGuiElement(&m_inventoryPanel);
}

bool Inventory::handleEvent(sf::Event& sfEvent) {
	return false;
}

void Inventory::update(float dt) {

}

void Inventory::render(sf::RenderTarget& window) {

}

void Inventory::onResize() {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());
	float width = 300.0f;
	m_inventoryPanel.setBounds(windowSize.x - width, 0.0f, width, windowSize.y);
}

void Inventory::resetAll() {
	m_inventoryPanel.resetInteractionState();

}

void Inventory::createFromRuleset(Ruleset* ruleset) {
	m_inventoryPanel.clearElements();
	float panelWidth = m_inventoryPanel.getSize().x - m_inventoryPanel.getSliderWidth() - m_inventoryPanel.getBorderWidth() * 2.0f;

	//Title
	m_inventoryTitle.reloadResources();
	m_inventoryTitle.setBounds(0.0f, 0.0f, panelWidth, 50.0f);
	m_inventoryTitle.setText("Inventory");
	m_inventoryTitle.setAlignment(TextRect::Alignment::CenterLeft);
	m_inventoryTitle.setFontSize(30);
	m_inventoryPanel.addElement(&m_inventoryTitle);


	//Categories
	m_inventoryCategories.clear();
	m_inventoryButtons.clear();
	m_inventoryButtonNames.clear();

	float y = 50.0f;
	float x = 5.0f;
	float width = 50.0f;
	float padding = 12.0f;
	int buttonsPerRow = floor((panelWidth - x) / (width + padding));

	for (const Ruleset::InventoryCategory& category : ruleset->getInventory()) {

		//Category name
		TextRect categoryName;
		categoryName.reloadResources();
		categoryName.setText(category.name);
		categoryName.setFontSize(20);
		categoryName.setAlignment(TextRect::Alignment::CenterLeft);
		categoryName.setBounds(x, y, panelWidth - x, 30);
		m_inventoryCategories.push_back(categoryName);

		y += 35.0f;

		//Category items
		int colCount = 0;
		float buttonX = x;
		for (const Ruleset::InventoryItem& item : category.items) {
			
			//Button
			SpriteButton button;
			button.reloadResources();
			button.setBounds(buttonX, y, width, width);
			button.setTexturePatch(item.rect);
			button.setFunction([this, item]() {
				m_selectedPixel = item.data;
				});
			button.setSpritePadding(1.0f);
			button.setTexture(ruleset->getInventoryTexture());
			m_inventoryButtons.push_back(button);


			//Name
			TextRect itemName;
			itemName.reloadResources();
			itemName.setText(item.name);
			itemName.setFontSize(9);
			itemName.setAlignment(TextRect::Alignment::Center);
			itemName.setBounds(buttonX - padding/2.0f, y + width, width+padding, 20);
			m_inventoryButtonNames.push_back(itemName);

			
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

	//add to panel
	for (SpriteButton& button : m_inventoryButtons) {
		m_inventoryPanel.addElement(&button);
	}
	for (TextRect& name : m_inventoryButtonNames) {
		m_inventoryPanel.addElement(&name);
	}
	for (TextRect& category : m_inventoryCategories) {
		m_inventoryPanel.addElement(&category);
	}


	m_inventoryPanel.resetSliders();
}