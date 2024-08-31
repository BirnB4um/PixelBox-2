#pragma once

#include <SFML/Graphics.hpp>
#include "GuiElement.h"

class GuiRect : public GuiElement
{
public:
	GuiRect();
	~GuiRect();

	void render(sf::RenderTarget& window) override;

	void setFillColor(sf::Color color) { m_rect.setFillColor(color); }
	const sf::Color& getFillColor() const { return m_rect.getFillColor(); }

	void setOutlineColor(sf::Color color) { m_rect.setOutlineColor(color); }
	const sf::Color& getOutlineColor() const { return m_rect.getOutlineColor(); }


private:
	sf::RectangleShape m_rect;

	void updateBounds() override;
};

