#pragma once

#include <SFML/Graphics.hpp>

#include "InteractableGui.h"
#include "NinePatch.h"
#include "../Tools/Timer.h"

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

	void setFontSize(unsigned int fontSize);
	void setMaxInputLength(unsigned int maxLength);

private:
	NinePatch m_ninePatch;
	std::string m_inputString;
	std::string m_defaultString;

	sf::Text m_displayedText;
	sf::Color m_inputColor;
	sf::Color m_defaultColor;
	sf::View m_textView;
	unsigned int m_maxInputLength;
	bool m_isFocused;

	sf::RectangleShape m_cursor;
	double m_cursorBlinkTime;
	bool m_cursorVisible;

	bool m_canInputNumbers, m_canInputAlphabet, m_canInputSpecial;
	void setInputFlags(bool numbers, bool alphabet, bool special);

	void updateBounds() override;
	void updateTextView(const sf::View& previousView);
	void updateText();
	void updateCursor();
	bool isInputEmpty();
};
