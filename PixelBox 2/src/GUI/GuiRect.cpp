#include "GuiRect.h"

GuiRect::GuiRect() : GuiElement() {
	m_borderWidth = 0.0f;
}

GuiRect::~GuiRect() {
}

void GuiRect::render(sf::RenderTarget& window) {
	window.draw(m_rect);
}

void GuiRect::updateBounds() {
	m_rect.setPosition(m_bounds.left + m_borderWidth, m_bounds.top + m_borderWidth);
	m_rect.setSize(sf::Vector2f(m_bounds.width - 2.0f * m_borderWidth, m_bounds.height - 2.0f * m_borderWidth));
	m_rect.setOutlineThickness(m_borderWidth);
}