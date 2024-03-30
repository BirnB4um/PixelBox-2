#include "Button.h"

#include "../Application.h"

Button::Button() {
	m_text.setString("Button");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color(255, 255, 255, 255));

	m_ninePatch.setTexture(m_texture);
	m_ninePatch.setPatches(0, 0, 5, 5, 2);
	m_ninePatch.setPosition(100, 100);
	m_ninePatch.setSize(100, 60);
	m_ninePatch.setBorderWidth(2);

	m_hovered = false;
	m_pressed = false;

	setBounds(0, 0, 100, 60);
}

Button::~Button() {
}

void Button::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		break;

	case sf::Event::MouseButtonPressed:
		if (m_hovered) {
			m_ninePatch.setPatches(10, 0, 5, 5, 2);
			m_pressed = true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (m_hovered && m_pressed) {
			m_ninePatch.setPatches(5, 0, 5, 5, 2);
			m_function();
		}
		m_pressed = false;
		break;

	default:
		break;
	}
}

void Button::updateInteraction() {
	if (Utils::rectContainsPoint(Application::mousePos.x, Application::mousePos.y, m_posX, m_posY, m_width, m_height)) {
		if (m_pressed) {
			m_ninePatch.setPatches(10, 0, 5, 5, 2);
		}
		else if (!m_hovered) {
			m_ninePatch.setPatches(5, 0, 5, 5, 2);
		}
		m_hovered = true;
	}
	else {
		if (m_hovered) {
			m_ninePatch.setPatches(0, 0, 5, 5, 2);
		}
		m_hovered = false;
	}
}

void Button::update(float dt) {
}

void Button::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
	window.draw(m_text);
}

void Button::reloadResources() {
	m_ninePatch.setTexture(m_texture);
}

void Button::setFunction(std::function<void()> func) {
	m_function = func;
}

void Button::setFont(sf::Font& font) {
	m_text.setFont(font);
}

void Button::setPosX(int x) {
	m_posX = x;
	updateSize();
}

void Button::setPosY(int y) {
	m_posY = y;
	updateSize();
}

void Button::setPosition(int x, int y) {
	m_posX = x;
	m_posY = y;
	updateSize();
}

void Button::setWidth(int width) {
	m_width = width;
	updateSize();
}

void Button::setHeight(int height) {
	m_height = height;
	updateSize();
}

void Button::setSize(int width, int height) {
	m_width = width;
	m_height = height;
	updateSize();
}

void Button::setBounds(int x, int y, int width, int height) {
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	updateSize();
}

void Button::setBorderWidth(int width) {
	m_borderWidth = width;
	m_ninePatch.setBorderWidth(width);
}

void Button::setText(std::string text) {
	m_text.setString(text);
}

int Button::getPosX() {
	return m_posX;
}

int Button::getPosY() {
	return m_posY;
}

sf::Vector2i Button::getPosition() {
	return sf::Vector2i(m_posX, m_posY);
}

int Button::getWidth() {
	return m_width;
}

int Button::getHeight() {
	return m_height;
}

sf::Vector2i Button::getSize() {
	return sf::Vector2i(m_width, m_height);
}

int Button::getBorderWidth() {
	return m_borderWidth;
}

void Button::updateSize() {
	m_ninePatch.setBounds(m_posX, m_posY, m_width, m_height);
	m_text.setPosition(m_posX + m_width / 2 - m_text.getLocalBounds().width / 2, m_posY + m_height / 2 - m_text.getLocalBounds().height / 2);
	updateInteraction();
}