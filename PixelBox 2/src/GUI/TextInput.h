#pragma once

#include <SFML/Graphics.hpp>

#include "InteractableGui.h"
#include "NinePatch.h"

class TextInput : public InteractableGui
{
public:
	TextInput();
	~TextInput();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	std::string getInputText();
	void setDefaultText(std::string text);

private:
	std::string m_inputString;
	std::string m_defaultString;
	NinePatch m_ninePatch;

	sf::Text m_displayedText;
	sf::Color m_inputColor;
	sf::Color m_defaultColor;
	sf::View m_textView;

	void updateBounds() override;
	void updateTextView(const sf::Vector2u& windowSize);
};
