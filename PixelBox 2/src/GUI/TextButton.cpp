#include "TextButton.h"
#include "../Application.h"

TextButton::TextButton() : Button() {
	m_text.setString("Button");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color(255, 255, 255, 255));
}

TextButton::~TextButton() {
}


void TextButton::render(sf::RenderTarget& window) {
	Button::render(window);
	window.draw(m_text);
}

void TextButton::setFont(sf::Font& font) {
	m_text.setFont(font);
	updateBounds();
}

void TextButton::setFontSize(int size) {
	m_text.setCharacterSize(size);
	updateBounds();
}

void TextButton::setText(std::string text) {
	m_text.setString(text);
	updateBounds();
}

void TextButton::updateBounds() {
	Button::updateBounds();
	m_text.setPosition(getPosition() + getSize() / 2.0f - sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height) / 2.0f);
}

void TextButton::reloadResources() {
	Button::reloadResources();
	m_text.setFont(*ResourceManager::getPixelFont());
	updateBounds();
}