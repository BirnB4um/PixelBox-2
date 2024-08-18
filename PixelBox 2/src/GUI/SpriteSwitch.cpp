#include "SpriteSwitch.h"


SpriteSwitch::SpriteSwitch() : Switch() {
	m_sprite.setPosition(0.0f, 0.0f);
}

SpriteSwitch::~SpriteSwitch() {
}

void SpriteSwitch::render(sf::RenderTarget& window) {
	Switch::render(window);
	window.draw(m_sprite);
}

void SpriteSwitch::reloadResources() {
	Switch::reloadResources();
	m_sprite.setTexture(*ResourceManager::getGuiTexture(), false);
}

void SpriteSwitch::setTexture(sf::Texture* texture) {
	m_sprite.setTexture(*texture, false);
}

void SpriteSwitch::setTexturePatch(sf::IntRect area) {
	m_sprite.setTextureRect(area);
	updateBounds();
}

void SpriteSwitch::updateBounds() {
	Switch::updateBounds();

	sf::IntRect spriteSize = m_sprite.getTextureRect();
	float spriteRatio = static_cast<float>(spriteSize.width) / static_cast<float>(spriteSize.height);
	float buttonRatio = (m_bounds.width - 2.0f * m_borderWidth) / (m_bounds.height - 2.0f * m_borderWidth);
	float scale = 1.0f;
	if (buttonRatio > spriteRatio) { // button wider than sprite
		scale = (m_bounds.height - 2.0f * m_borderWidth) / static_cast<float>(spriteSize.height);
	}
	else {
		scale = (m_bounds.width - 2.0f * m_borderWidth) / static_cast<float>(spriteSize.width);
	}
	m_sprite.setScale(scale, scale);
	m_sprite.setPosition(m_bounds.left + m_bounds.width / 2.0f - spriteSize.width * scale / 2.0f, m_bounds.top + m_bounds.height / 2.0f - spriteSize.height * scale / 2.0f);

}