#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "../ResourceManager.h"

class TextRect : public GuiElement
{
public:

	enum class Alignment {
		TopLeft,
		TopCenter,
		TopRight,
		CenterLeft,
		Center,
		CenterRight,
		BottomLeft,
		BottomCenter,
		BottomRight
	};

	TextRect();

	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	inline void setAlignment(const Alignment alignment) { m_textAlignment = alignment; }
	inline Alignment getAlignment() { return m_textAlignment; }

	inline void setText(const std::string& text) { m_text.setString(text); }
	inline std::string getText() const { return m_text.getString(); }

	inline void setFont(const sf::Font& font) { m_text.setFont(font); }
	inline const sf::Font* getFont() const { return m_text.getFont(); }

	inline void setFontSize(const unsigned int fontSize) { m_text.setCharacterSize(fontSize); }
	inline unsigned int getFontSize() const { return m_text.getCharacterSize(); }

	void setBorderWidth(float width) { };

	inline void setLineSpacing(float spacing) { m_text.setLineSpacing(spacing); }
	inline float getLineSpacing() const { return m_text.getLineSpacing(); }

	inline void setLetterSpacing(float spacing) { m_text.setLetterSpacing(spacing); }
	inline float getLetterSpacing() const { return m_text.getLetterSpacing(); }


	//TODO:
	//void scaleFontSizeToFit();

protected:
	sf::Text m_text;
	sf::View m_textView;
	Alignment m_textAlignment;

	//TODO: automatic wrap around flag

	void updateTextView(const sf::View& previousView);
};

