#pragma once
#include "../Screen.h"
#include "../../GUI/GUI.h"

class WorldSelectionScreen : public Screen
{
public:

	WorldSelectionScreen();
	~WorldSelectionScreen();

	void init() override;

	//called when the window is resized
	void onResize() override;

	//called when the window is about to close
	void onClosing() override;

	void onSwitch() override;

	bool handleEvent(sf::Event& sfEvent) override;

	//update given deltatime dt in seconds
	void update(float dt) override;

	void render(sf::RenderTarget& window) override;

private:

	sf::Text m_title;

	ScrollPanel m_worldMenu;

	TextButton m_createNewWorldButton;

	TextButton button1, button2;

	TextInput textInput;
	HorizontalSlider textSlider;

	HorizontalValueSlider hValueSlider;
	VerticalValueSlider vValueSlider;

	Switch m_switch;
	TextSwitch m_textSwitch;
	SpriteSwitch m_spriteSwitch;

	TextStateSwitch m_textStateSwitch;
	SpriteStateSwitch m_spriteStateSwitch;

	TextRect m_textRect;

};
