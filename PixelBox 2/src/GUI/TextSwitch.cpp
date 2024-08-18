#include "TextSwitch.h"

TextSwitch::TextSwitch() : Switch() {
	m_text.setString("Switch");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color(255, 255, 255, 255));
}

TextSwitch::~TextSwitch() {
}


void TextSwitch::render(sf::RenderTarget& window) {
	Switch::render(window);
	window.draw(m_text);
}

void TextSwitch::setFont(sf::Font& font) {
	m_text.setFont(font);
	updateBounds();
}

void TextSwitch::setFontSize(int size) {
	m_text.setCharacterSize(size);
	updateBounds();
}

void TextSwitch::setText(std::string text) {
	m_text.setString(text);
	updateBounds();
}

void TextSwitch::updateBounds() {
	Switch::updateBounds();
	m_text.setPosition(getPosition() + getSize() / 2.0f - sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height) / 2.0f);
}

void TextSwitch::reloadResources() {
	Switch::reloadResources();
	m_text.setFont(*ResourceManager::getPixelFont());
	updateBounds();
}