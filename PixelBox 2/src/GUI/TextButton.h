#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"
#include "../ResourceManager.h"

class TextButton : public Button
{
public:

	TextButton();
	~TextButton();

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void setText(std::string text);
	void setFont(sf::Font& font);
	void setFontSize(int size);



protected:
	sf::Text m_text;

	void updateBounds() override;



};
