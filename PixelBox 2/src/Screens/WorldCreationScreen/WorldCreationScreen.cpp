#include "WorldCreationScreen.h"
#include "../../Application.h"

WorldCreationScreen::WorldCreationScreen() {

}

WorldCreationScreen::~WorldCreationScreen() {

}

void WorldCreationScreen::init() {

	m_backButton.reloadResources();
	m_backButton.setFontSize(20);
	m_backButton.setFunction([this]() {
		Application::instance().closeCurrentScreen();
		});
	m_backButton.setText("Back");
	addGuiElement(&m_backButton);

	m_createWorldButton.reloadResources();
	m_createWorldButton.setFontSize(20);
	m_createWorldButton.setFunction([this]() {
		World* world = createNewWorld();
		Application::instance().simulationScreen.setWorld(world);
		Application::instance().closeCurrentScreen();
		Application::instance().openScreen(ScreenID::SIMULATION);
		});
	m_createWorldButton.setText("Create world");
	addGuiElement(&m_createWorldButton);


	onResize();
}

void WorldCreationScreen::onResize() {

	m_backButton.setSize(200, 60);
	m_backButton.setPosition(50, Application::instance().getWindowSize().y - m_backButton.getSize().y - 50);

	m_createWorldButton.setSize(250, 60);
	m_createWorldButton.setPosition(Application::instance().getWindowSize().x - m_createWorldButton.getSize().x - 50, 
									Application::instance().getWindowSize().y - m_createWorldButton.getSize().y - 50);

}

void WorldCreationScreen::onClosing() {

}

void WorldCreationScreen::onSwitch() {

}

void WorldCreationScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);
}

void WorldCreationScreen::update(float dt) {
	updateGui(dt);
}

void WorldCreationScreen::render(sf::RenderTarget& window) {
	window.clear();

	renderGui(window);
}

World* WorldCreationScreen::createNewWorld() {
	//TODO: create a new world based on all infos the user entered in the fields

	WorldMetaData metaData;
	metaData.width = 256;
	metaData.height = 128;
	metaData.worldName = "TestWorld";
	metaData.ruleset = nullptr;

	World* world = new World;
	world->setMetaData(metaData);
	world->createWorld();

	return world;
}