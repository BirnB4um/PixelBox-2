#include "HomeScreen.h"
#include "../Application.h"

HomeScreen::HomeScreen() {
}

HomeScreen::~HomeScreen() {
}

void HomeScreen::init() {

	// init GUI
	m_worldSelectionButton.setFont(app->getResourceManager().getPixelFont());
	m_worldSelectionButton.setText("Worlds");
	m_worldSelectionButton.setFunction([this]() {
		app->openScreen(ScreenID::WORLDSELECTION);
		});
	m_guiElements.push_back(&m_worldSelectionButton);

	m_settingsButton.setFont(app->getResourceManager().getPixelFont());
	m_settingsButton.setText("Settings");
	m_settingsButton.setFunction([this]() {
		app->openScreen(ScreenID::SETTINGS);
		});
	m_guiElements.push_back(&m_settingsButton);

	m_testButton.setBounds(100, 100, 200,150);
	m_testButton.setTexturePatch(sf::IntRect(0, 0, 20, 10));
	m_testButton.setFunction([this]() {
		});
	m_guiElements.push_back(&m_testButton);

	m_slider.setPosition(100, 300);
	m_slider.setFunction([this]() {
		std::cout << "Slider Value: " << m_slider.getValue() << std::endl;
		});
	m_slider.setRange(0, 100);
	m_guiElements.push_back(&m_slider);

	m_slider2.setPosition(50, 350);
	m_slider2.setFunction([this]() {
		std::cout << "Slider Value: " << m_slider2.getValue() << std::endl;
		});
	m_slider2.setRange(1, -1);
	m_guiElements.push_back(&m_slider2);

	reloadGuiResources();
}

void HomeScreen::onResize() {
	// center Buttons
	sf::Vector2f buttonSize = sf::Vector2f(200 * GuiElement::getGuiScale(), 60 * GuiElement::getGuiScale());
	sf::Vector2f buttonPos = static_cast<sf::Vector2f>(app->getWindowSize())/2.0f - buttonSize/2.0f;
	int buttonSpacing = 10 * GuiElement::getGuiScale();

	m_worldSelectionButton.setSize(buttonSize);
	m_worldSelectionButton.setPosition(buttonPos);
	m_worldSelectionButton.setFontSize(24 * GuiElement::getGuiScale());
	buttonPos.y += buttonSize.y + buttonSpacing;

	m_settingsButton.setSize(buttonSize);
	m_settingsButton.setPosition(buttonPos);
	m_settingsButton.setFontSize(24 * GuiElement::getGuiScale());
	buttonPos.y += buttonSize.y + buttonSpacing;
}

void HomeScreen::onClosing() {
}

void HomeScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		break;

	default:
		break;
	}
}

void HomeScreen::update(float dt) {
	updateGui(dt);

	ImGui::Begin("TestButton");
	float value[] = { m_testButton.getPosition().x, m_testButton.getPosition().y };
	if (ImGui::SliderFloat2("X/Y", value, 0, app->getWindowSize().x)) {
		m_testButton.setPosition(value[0], value[1]);
	}
	value[0] = m_testButton.getSize().x;
	value[1] = m_testButton.getSize().y;
	if (ImGui::SliderFloat2("W/H", value, -50, 300)) {
		m_testButton.setSize(value[0], value[1]);
	}
	ImGui::Button("TexturePatch", ImVec2(100, 50));
	ImGui::End();
}

void HomeScreen::render(sf::RenderTarget& window) {
	window.clear();
	renderGui(window);
}