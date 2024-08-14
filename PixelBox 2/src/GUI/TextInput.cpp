#include "TextInput.h"
#include "../Application.h"

TextInput::TextInput() :InteractableGui() {
	m_inputString = "";
	m_defaultString = " text";
	m_maxInputLength = 256;
	setInputFlags(true, true, true);
	m_isFocused = false;

	m_cursor.setFillColor(sf::Color::White);
	m_cursor.setPosition(0.0f, 0.0f);
	m_cursorBlinkTime = 0.0f;
	m_cursorVisible = true;


	m_inputColor = sf::Color(255, 255, 255, 255);
	m_defaultColor = sf::Color(180, 180, 180, 255);

	m_displayedText.setString(m_defaultString);
	m_displayedText.setPosition(0.0f, 0.0f);
	m_displayedText.setFillColor(m_defaultColor);
	setFontSize(20);

	m_ninePatch.setPatches(PatchAtlas::roundedIdle);
	setBounds(sf::FloatRect(0, 0, 100, 60));
	setBorderWidth(2);
}

TextInput::~TextInput() {
}

std::string TextInput::getInputText() {
	return m_inputString;
}

void TextInput::setFontSize(unsigned int fontSize) {
	m_displayedText.setCharacterSize(fontSize);
	m_cursor.setSize(sf::Vector2f(std::max(1.0f, fontSize/20.0f), fontSize));
	updateCursor();
}

void TextInput::setDefaultText(std::string text) {
	m_defaultString = text;
	updateText();
}

void TextInput::updateText() {
	if (isInputEmpty()) {
		m_displayedText.setString(m_defaultString);
		m_displayedText.setFillColor(m_defaultColor);
	}
	else {
		m_displayedText.setString(m_inputString);
		m_displayedText.setFillColor(m_inputColor);
	}
	updateCursor();
}

void TextInput::updateCursor() {
	float x = m_displayedText.getGlobalBounds().left + m_displayedText.getGlobalBounds().width + m_displayedText.getCharacterSize() * 0.2f;
	m_cursor.setPosition(isInputEmpty() ? m_displayedText.getCharacterSize() * -0.2f : x, m_displayedText.getPosition().y);
}

bool TextInput::isInputEmpty() {
	return m_inputString.empty();
}

void TextInput::setMaxInputLength(unsigned int maxLength) {
	m_maxInputLength = maxLength;
	if (m_inputString.size() > m_maxInputLength) {
		m_inputString = m_inputString.substr(0, m_maxInputLength);
	}
	updateText();
}

void TextInput::setInputFlags(bool numbers, bool alphabet, bool special) {
	m_canInputNumbers = numbers;
	m_canInputAlphabet = alphabet;
	m_canInputSpecial = special;
}

bool TextInput::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sfEvent.key.code == sf::Keyboard::Enter) {
			m_isFocused = false;
		}
		else if (sfEvent.key.code == sf::Keyboard::Escape) {
			m_isFocused = false;
		}
		break;

	case sf::Event::TextEntered:
		if (m_isFocused) {
			// 0-9=[48,57] A-Z=[65,90] a-z=[97,122] special=[33,47]+[58,64]+[91,95]

			sf::Uint32 input = sfEvent.text.unicode;
			if (input == 8) { //backspace
				if (!m_inputString.empty()) {
					m_inputString.pop_back();
				}
			}
			if (input == 32) {//space
				m_inputString += static_cast<unsigned char>(input);
			}

			if (m_inputString.size() >= m_maxInputLength) {
				break;
			}

			if (m_canInputNumbers && input >= 48 && input <= 57) {
				m_inputString += static_cast<unsigned char>(input);
			}
			if (m_canInputAlphabet && ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))) {
				m_inputString += static_cast<unsigned char>(input);
			}
			if (m_canInputSpecial && ((input >= 33 && input <= 47) || (input >= 58 && input <= 64) || (input >= 91 && input <= 95))) {
				m_inputString += static_cast<unsigned char>(input);
			}
			updateText();
		}
		break;

	case sf::Event::MouseButtonPressed:
		m_isFocused = isMouseOver();
		break;

	default:
		break;
	}

	return false;
}

void TextInput::update(float dt) {
	if (m_isFocused) {
		m_cursorBlinkTime += dt;
		if (m_cursorBlinkTime > 0.5f) {
			m_cursorBlinkTime = 0.0f;
			m_cursorVisible = !m_cursorVisible;
		}
	}
	else {
		m_cursorBlinkTime = 0.0f;
		m_cursorVisible = false;
	}
}

void TextInput::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);

	sf::View previousView = window.getView();

	updateTextView(previousView);
	window.setView(m_textView);

	window.draw(m_displayedText);

	if(m_cursorVisible)
		window.draw(m_cursor);

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

void TextInput::updateTextView(const sf::View& previousView) {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());

	//position of the panelwindow
	sf::Vector2f pos(m_bounds.left + m_borderWidth, m_bounds.top + m_borderWidth);
	sf::Vector2f size(m_bounds.width - 2.0f * m_borderWidth, m_bounds.height - 2.0f * m_borderWidth);
	float boundsRatio = size.x / size.y;

	//set view
	sf::FloatRect textArea = m_displayedText.getLocalBounds();
	float padding = m_displayedText.getCharacterSize() * 0.5f;
	textArea.left -= padding;
	//textArea.top -= padding;
	//textArea.height += 2 * padding;
	textArea.width += 2 * padding;

	sf::FloatRect view;

	//constrain the height and width so the text doesnt render outside the bounds
	view.left = textArea.left;
	view.width = std::min(textArea.width, size.x);
	view.height = std::min(textArea.height, size.y);
	view.top = textArea.top + (textArea.height - view.height) / 2.0f; //center the text vertically

	//shift the view to be at end of text if input is not empty. otherwise stay at front
	if (!isInputEmpty()) {
		view.left += textArea.width - view.width;
	}

	//parent view position.
	sf::Vector2f parentViewPos(0.0f, 0.0f); //no parent
	sf::Vector2f parentViewSize = windowSize;
	sf::Vector2f parentVieportPos(0.0f, 0.0f);
	sf::Vector2f parentViewportSize = windowSize;
	if (m_parentGui != nullptr) {
		parentViewPos = previousView.getCenter() - previousView.getSize() * 0.5f;
		parentViewSize = previousView.getSize();
		parentVieportPos.x = previousView.getViewport().left * windowSize.x;
		parentVieportPos.y = previousView.getViewport().top * windowSize.y;
		parentViewportSize.x = previousView.getViewport().width * windowSize.x;
		parentViewportSize.y = previousView.getViewport().height * windowSize.y;
	}

	sf::Vector2f offset = pos - parentViewPos;

	sf::FloatRect viewport(0, 0, 0, 0);
	viewport.left = parentVieportPos.x + offset.x;
	viewport.top = parentVieportPos.y + offset.y + size.y / 2.0f - view.height / 2.0f;

	//check if offset is outside of parentView and correct it
	if (offset.x < 0) {
		view.left -= offset.x;
		view.width += offset.x;
		viewport.left = parentVieportPos.x;
	}
	if (offset.x > parentViewSize.x - view.width) {
		view.width = parentViewportSize.x - offset.x;
	}
	if (offset.x > parentViewportSize.x) {//useless???
		offset.x = parentViewportSize.x;
	}

	if (offset.y < 0) {
		view.top -= offset.y;
		view.height += offset.y;
		viewport.top = parentVieportPos.y;
	}
	if (offset.y > parentViewSize.y - view.height) {
		view.height = parentViewportSize.y - offset.y;
	}
	if (offset.y > parentViewportSize.y) {//useless???
		offset.y = parentViewportSize.y;
	}

	viewport.width = std::max(view.width, 0.0f);
	viewport.height = std::max(view.height, 0.0f);

	//normalize viewport
	viewport.left /= windowSize.x;
	viewport.top /= windowSize.y;
	viewport.width /= windowSize.x;
	viewport.height /= windowSize.y;

	//update m_panelView from view and m_panelView.viewport from viewport
	m_textView.setSize(view.width, view.height);
	m_textView.setCenter(view.left + view.width / 2.0f, view.top + view.height / 2.0f);
	m_textView.setViewport(viewport);
}