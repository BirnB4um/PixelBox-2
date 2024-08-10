#include "SpriteRect.h"

SpriteRect::SpriteRect() : GuiElement() {
	m_bounds.width = 100.0f;
	m_bounds.height = 80.0f;
}

SpriteRect::~SpriteRect() {

}

void SpriteRect::render(sf::RenderTarget& window) {
	window.draw(m_rect);
}

void SpriteRect::updateBounds() {
	GuiElement::updateBounds();

	m_rect.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
	m_rect.setPosition(m_bounds.left, m_bounds.top);
}

void SpriteRect::setTexture(sf::Texture* texture) {
	m_rect.setTexture(texture, true);
}

void SpriteRect::setTextureRect(sf::IntRect& rect) {
	m_rect.setTextureRect(rect);
}

float SpriteRect::getTextureRatio() {
	sf::Vector2f size = static_cast<sf::Vector2f>(m_rect.getTexture()->getSize());
	return size.x / size.y;
}

void SpriteRect::setHeightWithRatio(float height) {
	setSize(height * getTextureRatio(), height);
}

void SpriteRect::setWidthWithRatio(float width) {
	setSize(width, width / getTextureRatio());
}