#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Button.h"
#include "NinePatch.h"
#include "../Tools/Utils.h"

class Application;

class TextButton : public Button
{
public:

	TextButton();
	~TextButton();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;

	void setText(std::string text);
	void setFont(sf::Font& font);
	void setFontSize(int size);



protected:
	sf::Text m_text;

	void updateSize() override;



};
