#pragma once

#include "Switch.h"

class TextSwitch : public Switch
{
public:
	TextSwitch();
	~TextSwitch();

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setText(std::string text);
	void setFont(sf::Font& font);
	void setFontSize(int size);

protected:
	sf::Text m_text;

	void updateBounds() override;
};

