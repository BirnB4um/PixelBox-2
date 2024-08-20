#include "SpriteStateSwitch.h"
#include "../Application.h"


SpriteStateSwitch::SpriteStateSwitch() : StateSwitch() {
	m_sprite.setPosition(0.0f, 0.0f);
	m_drawSprite = false;
	m_spritePadding = 0.0f;
}

SpriteStateSwitch::~SpriteStateSwitch() {

}

void SpriteStateSwitch::reloadResources() {
	StateSwitch::reloadResources();
	m_sprite.setTexture(*ResourceManager::getGuiTexture(), false);
	updateBounds();
}

void SpriteStateSwitch::render(sf::RenderTarget& window) {
	StateSwitch::render(window);

	if(m_drawSprite)
		window.draw(m_sprite);
}

void SpriteStateSwitch::incrementState() {
	if (m_states.size() == 0) {
		m_drawSprite = false;
		return;
	}

	m_currentState = (m_currentState + 1) % m_states.size();
	m_sprite.setTextureRect(m_states[m_currentState].area);
	updateBounds();

}

void SpriteStateSwitch::addState(State state) {
	m_states.push_back(state);
	m_drawSprite = true;
	if (m_states.size() == 1) {
		m_sprite.setTextureRect(state.area);
		updateBounds();
	}
}

void SpriteStateSwitch::clearStates() {
	m_currentState = 0;
	m_drawSprite = false;
	m_states.clear();
	updateBounds();
}

void SpriteStateSwitch::updateBounds() {
	StateSwitch::updateBounds();

	sf::IntRect spriteSize = m_sprite.getTextureRect();
	float spriteRatio = static_cast<float>(spriteSize.width) / static_cast<float>(spriteSize.height);
	float buttonRatio = (m_bounds.width - 2.0f * m_borderWidth) / (m_bounds.height - 2.0f * m_borderWidth);
	float scale = 1.0f;
	if (buttonRatio > spriteRatio) { // button wider than sprite
		scale = (m_bounds.height - 2.0f * (m_borderWidth + m_spritePadding)) / static_cast<float>(spriteSize.height);
	}
	else {
		scale = (m_bounds.width - 2.0f * (m_borderWidth + m_spritePadding)) / static_cast<float>(spriteSize.width);
	}
	m_sprite.setScale(scale, scale);
	m_sprite.setPosition(m_bounds.left + m_bounds.width / 2.0f - spriteSize.width * scale / 2.0f, m_bounds.top + m_bounds.height / 2.0f - spriteSize.height * scale / 2.0f);
}

SpriteStateSwitch::State SpriteStateSwitch::getCurrentState() {
	if (m_states.size() == 0) {
		return { 0, {0,0,1,1} };
	}
	return m_states[m_currentState];
}

void SpriteStateSwitch::setState(size_t id) {
	for (size_t i = 0; i < m_states.size(); i++) {
		if (m_states[i].id == id) {
			m_currentState = i;
			m_sprite.setTextureRect(m_states[m_currentState].area);
			m_function();
			updateBounds();
			return;
		}
	}
}

void SpriteStateSwitch::setSpritePadding(float padding) {
	m_spritePadding = padding;
	updateBounds();
}