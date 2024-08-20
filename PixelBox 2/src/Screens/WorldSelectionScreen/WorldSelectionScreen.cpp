#include "WorldSelectionScreen.h"
#include "../../Application.h"

WorldSelectionScreen::WorldSelectionScreen() {
}

WorldSelectionScreen::~WorldSelectionScreen() {
}

void WorldSelectionScreen::init() {
	m_title.setFont(*ResourceManager::getPixelFont());
	m_title.setString("Worlds");

	m_worldMenu.setScrollable(true, true);
	addGuiElement(&m_worldMenu);

	m_createNewWorldButton.setFont(*ResourceManager::getPixelFont());
	m_createNewWorldButton.setFontSize(20);
	m_createNewWorldButton.setText("New World");
	m_createNewWorldButton.setFunction([this]() {
		Application::instance().openScreen(ScreenID::WORLDCREATION);
		});
	addGuiElement(&m_createNewWorldButton);

	button1.setFontSize(20);
	button1.setText("Button1");
	button1.setBounds(100, 100, 200, 60);
	m_worldMenu.addElement(&button1);

	button2.setFontSize(20);
	button2.setText("Button2");
	button2.setBounds(1000, 1000, 200, 60);
	m_worldMenu.addElement(&button2);

	textInput.setBounds(300, 300, 500, 120);
	textInput.setDefaultText("Text");
	m_worldMenu.addElement(&textInput);

	textSlider.setBounds(300, 250, 200, 30);
	textSlider.setFunction([this]() {
		textInput.setFontSize(textSlider.getValue());
		hValueSlider.setRange(-1, textSlider.getValue());
		});
	textSlider.setRange(0, 200);
	textSlider.setValue(50);
	m_worldMenu.addElement(&textSlider);

	hValueSlider.setBounds(200, 500, 200, 30);
	hValueSlider.setRange(-400, -100);
	hValueSlider.setValue(0);
	hValueSlider.setFunction([this]() {
		//std::cout << hValueSlider.getValue() << std::endl;
		});
	m_worldMenu.addElement(&hValueSlider);

	vValueSlider.setBounds(150, 500, 30, 200);
	vValueSlider.setRange(-100, 300);
	vValueSlider.setValue(10);
	vValueSlider.setFunction([this]() {
		//std::cout << vValueSlider.getValue() << std::endl;
		});
	m_worldMenu.addElement(&vValueSlider);

	m_switch.setBounds(400, 100, 80, 60);
	m_switch.setFunction([this]() {
		std::cout << (m_switch.isActivated() ? "Switch activated" : "Switch deactivated") << std::endl;
		});
	m_worldMenu.addElement(&m_switch);

	m_textSwitch.setBounds(500, 100, 120, 60);
	m_textSwitch.setText("nice");
	m_textSwitch.setFunction([this]() {
		std::cout << (m_textSwitch.isActivated() ? "TextSwitch activated" : "TextSwitch deactivated") << std::endl;
		});
	m_worldMenu.addElement(&m_textSwitch);

	m_spriteSwitch.setBounds(650, 100, 120, 80);
	m_spriteSwitch.setTexturePatch(sf::IntRect(0, 0, 64, 64));
	m_spriteSwitch.setFunction([this]() {
		std::cout << (m_spriteSwitch.isActivated() ? "SpriteSwitch activated" : "SpriteSwitch deactivated") << std::endl;
		});
	m_worldMenu.addElement(&m_spriteSwitch);


	m_textStateSwitch.setBounds(800, 100, 120, 80);
	m_textStateSwitch.addState({ 1, "State1" });
	m_textStateSwitch.addState({ 2, "State2" });
	m_textStateSwitch.setFunction([this]() {
		std::cout << "Current state: " << m_textStateSwitch.getCurrentState().name << std::endl;
		});
	m_worldMenu.addElement(&m_textStateSwitch);

	m_spriteStateSwitch.setBounds(950, 100, 120, 80);
	m_spriteStateSwitch.addState({ 1, sf::IntRect(0, 0, 15, 15) });
	m_spriteStateSwitch.addState({ 2, sf::IntRect(50, 0, 15, 20) });
	m_spriteStateSwitch.setFunction([this]() {
		std::cout << "Current state: " << m_spriteStateSwitch.getCurrentState().id << std::endl;
		});
	m_worldMenu.addElement(&m_spriteStateSwitch);


	m_worldMenu.resetSliders();

}

void WorldSelectionScreen::onResize() {
	sf::Vector2i windowSize = Application::instance().getWindowSize();

	m_title.setCharacterSize(40);
	m_title.setPosition(30, 30);

	float padding = 50;
	m_worldMenu.setPosition(padding, 100);
	m_worldMenu.setSize(windowSize.x - padding * 2.0f, windowSize.y - 100 - padding);

	m_createNewWorldButton.setSize(200, 50);
	m_createNewWorldButton.setPosition(m_worldMenu.getPosition().x + m_worldMenu.getSize().x - m_createNewWorldButton.getSize().x - 10,
		m_worldMenu.getPosition().y - m_createNewWorldButton.getSize().y - 10);
}

void WorldSelectionScreen::onClosing() {
}

void WorldSelectionScreen::onSwitch() {
	Screen::onSwitch();
}

bool WorldSelectionScreen::handleEvent(sf::Event& sfEvent) {
	if (handleGuiEvent(sfEvent))
		return true;

	switch (sfEvent.type) {
	case sf::Event::MouseButtonPressed:
		break;

	case sf::Event::KeyReleased:
		if (sfEvent.key.code == sf::Keyboard::Escape) {
			Application::instance().closeCurrentScreen();
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}

void WorldSelectionScreen::update(float dt) {
	updateGui(dt);
}

void WorldSelectionScreen::render(sf::RenderTarget& window) {
	window.clear();

	window.draw(m_title);

	renderGui(window);
}