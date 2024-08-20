#include "TextStateSwitch.h"
#include "../Application.h"


TextStateSwitch::TextStateSwitch() : StateSwitch() {
	m_text.setString("");
	m_text.setCharacterSize(24);
}

TextStateSwitch::~TextStateSwitch() {

}

void TextStateSwitch::reloadResources() {
	StateSwitch::reloadResources();
	m_text.setFont(*ResourceManager::getPixelFont());
	updateBounds();
}

void TextStateSwitch::render(sf::RenderTarget& window) {
	StateSwitch::render(window);
	window.draw(m_text);
}

void TextStateSwitch::incrementState() {
	if (m_states.size() == 0) {
		m_text.setString("");
		return;
	}

	m_currentState = (m_currentState + 1) % m_states.size();
	m_text.setString(m_states[m_currentState].name);
	updateBounds();

}

void TextStateSwitch::setFont(sf::Font& font) {
	m_text.setFont(font);
	updateBounds();
}

void TextStateSwitch::setFontSize(int size) {
	m_text.setCharacterSize(size);
	updateBounds();
}

void TextStateSwitch::addState(State state) {
	m_states.push_back(state);
	if (m_states.size() == 1) {
		m_text.setString(state.name);
		updateBounds();
	}
}

void TextStateSwitch::clearStates() {
	m_currentState = 0;
	m_states.clear();
	m_text.setString("");
	updateBounds();
}

void TextStateSwitch::updateBounds() {
	StateSwitch::updateBounds();
	m_text.setPosition(getPosition() + getSize() / 2.0f - sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height) / 2.0f);
}

TextStateSwitch::State TextStateSwitch::getCurrentState() {
	if (m_states.size() == 0) {
		return { 0, "" };
	}

	return m_states[m_currentState];
}

void TextStateSwitch::setState(size_t id) {
	for (size_t i = 0; i < m_states.size(); i++) {
		if (m_states[i].id == id) {
			m_currentState = i;
			m_text.setString(m_states[m_currentState].name);
			m_function();
			updateBounds();
			return;
		}
	}
}