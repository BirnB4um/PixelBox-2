#include "TextInput.h"
#include "../Application.h"

TextInput::TextInput() :InteractableGui() {
	m_inputString = "";
	m_defaultString = "text";

	m_inputColor = sf::Color(255, 255, 255, 255);
	m_defaultColor = sf::Color(180, 180, 180, 255);

	m_displayedText.setCharacterSize(20);
	m_displayedText.setString(m_defaultString);
	m_displayedText.setPosition(0.0f, 0.0f);
	m_displayedText.setFillColor(m_defaultColor);

	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	setBounds(sf::FloatRect(0, 0, 100, 60));
	setBorderWidth(2);
}

TextInput::~TextInput() {
}

std::string TextInput::getInputText() {
	return m_inputString;
}

void TextInput::setDefaultText(std::string text) {
	m_defaultString = text;
}

bool TextInput::handleEvent(sf::Event& sfEvent) {
	return false;
}

void TextInput::update(float dt) {
}

void TextInput::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);

	sf::View previousView = window.getView();

	updateTextView(window.getSize());


	window.setView(m_textView);
	window.draw(m_displayedText);
	window.setView(previousView);
}

void TextInput::reloadResources() {
	m_ninePatch.reloadResources();
	m_displayedText.setFont(*ResourceManager::instance().getPixelFont());

}

void TextInput::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);

}

void TextInput::updateTextView(const sf::Vector2u& windowSize) {
	sf::FloatRect size = m_displayedText.getLocalBounds();
	float padding = 5.0f;
	size.left += size.width + padding;
	size.top -= padding;
	size.height += 2 * padding;

	float boundsRatio = m_bounds.width / m_bounds.height;
	size.width = boundsRatio * size.height;
	size.left -= size.width;

	m_textView.setSize(size.width, size.height);
	m_textView.setCenter(size.left + size.width / 2.0f, size.top + size.height / 2.0f);

	sf::FloatRect viewport;
	viewport.left = (m_bounds.left + m_borderWidth) / windowSize.x;
	viewport.top = (m_bounds.top + m_borderWidth) / windowSize.y;
	viewport.width = (m_bounds.width - 2 * m_borderWidth) / windowSize.x;
	viewport.height = (m_bounds.height - 2 * m_borderWidth) / windowSize.y;
	m_textView.setViewport(viewport);
}