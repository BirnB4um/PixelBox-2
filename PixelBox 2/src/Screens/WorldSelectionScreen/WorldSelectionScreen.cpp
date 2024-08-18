#include "WorldSelectionScreen.h"
#include "../../Application.h"

WorldSelectionScreen::WorldSelectionScreen() {
}

WorldSelectionScreen::~WorldSelectionScreen() {
}

void WorldSelectionScreen::init() {
	m_title.setFont(*ResourceManager::getPixelFont());
	m_title.setString("Worlds");

	m_worldMenu.reloadResources();
	m_worldMenu.setScrollable(true, true);
	addGuiElement(&m_worldMenu);


	m_createNewWorldButton.reloadResources();
	m_createNewWorldButton.setFont(*ResourceManager::getPixelFont());
	m_createNewWorldButton.setFontSize(20);
	m_createNewWorldButton.setText("New World");
	m_createNewWorldButton.setFunction([this]() {
		Application::instance().openScreen(ScreenID::WORLDCREATION);
		});
	addGuiElement(&m_createNewWorldButton);


	button1.reloadResources();
	button1.setFontSize(20);
	button1.setText("Button1");
	button1.setBounds(100, 100, 200, 60);
	m_worldMenu.addElement(&button1);

	button2.reloadResources();
	button2.setFontSize(20);
	button2.setText("Button2");
	button2.setBounds(1000, 1000, 200, 60);
	m_worldMenu.addElement(&button2);

	textInput.reloadResources();
	textInput.setBounds(300, 300, 500, 120);
	textInput.setDefaultText("Text");
	m_worldMenu.addElement(&textInput);

	textSlider.reloadResources();
	textSlider.setBounds(300, 250, 200, 30);
	textSlider.setFunction([this]() {
		textInput.setFontSize(textSlider.getValue());
		hValueSlider.setRange(-1, textSlider.getValue());
		});
	textSlider.setRange(0, 200);
	textSlider.setValue(50);
	m_worldMenu.addElement(&textSlider);

	hValueSlider.reloadResources();
	hValueSlider.setBounds(200, 500, 200, 30);
	hValueSlider.setRange(-400, -100);
	hValueSlider.setValue(0);
	hValueSlider.setFunction([this]() {
		std::cout << hValueSlider.getValue() << std::endl;
		});
	m_worldMenu.addElement(&hValueSlider);

	vValueSlider.reloadResources();
	vValueSlider.setBounds(150, 500, 30, 200);
	vValueSlider.setRange(-100, 300);
	vValueSlider.setValue(10);
	vValueSlider.setFunction([this]() {
		std::cout << vValueSlider.getValue() << std::endl;
		});
	m_worldMenu.addElement(&vValueSlider);
	
	m_worldMenu.resetSliders();


	reloadGuiResources();
	onResize();
}

void WorldSelectionScreen::onResize() {

	sf::Vector2i windowSize = Application::instance().getWindowSize();

	m_title.setCharacterSize(40);
	m_title.setPosition(30, 30);

	float padding = 50;
	m_worldMenu.setPosition(padding, 100);
	m_worldMenu.setSize(windowSize.x - padding*2.0f, windowSize.y - 100 - padding);

	m_createNewWorldButton.setSize(200, 50);
	m_createNewWorldButton.setPosition(m_worldMenu.getPosition().x + m_worldMenu.getSize().x - m_createNewWorldButton.getSize().x - 10,
										m_worldMenu.getPosition().y - m_createNewWorldButton.getSize().y - 10);


}

void WorldSelectionScreen::onClosing() {
}

void WorldSelectionScreen::onSwitch() {

}

void WorldSelectionScreen::handleEvent(sf::Event& sfEvent) {
	handleGuiEvent(sfEvent);

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		break;

	default:
		break;
	}
}

void WorldSelectionScreen::update(float dt) {
	updateGui(dt);
}

void WorldSelectionScreen::render(sf::RenderTarget& window) {
	window.clear();

	window.draw(m_title);

	renderGui(window);
}