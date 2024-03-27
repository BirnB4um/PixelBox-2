#include "Button.h"

#include "../Application.h"

Button::Button() {
	m_text.setString("Button");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color(255, 255, 255, 255));

	m_rect.setFillColor(sf::Color(0, 0, 0, 255));
	m_rect.setOutlineColor(sf::Color(255, 255, 255, 255));
	m_rect.setOutlineThickness(2);

	m_hovered = false;
	m_pressed = false;

	setBounds(0, 0, 100, 60);
	t = 0;
}

Button::~Button() {
}

void Button::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		if (Utils::rectContainsPoint(sfEvent.mouseMove.x, sfEvent.mouseMove.y, m_posX, m_posY, m_width, m_height)) {
			if (!m_hovered) {
				m_rect.setFillColor(sf::Color(50, 50, 50, 255));
			}
			m_hovered = true;
		}
		else {
			if (m_hovered) {
				m_rect.setFillColor(sf::Color(0, 0, 0, 255));
			}
			m_hovered = false;
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (m_hovered) {
			m_pressed = true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (m_hovered && m_pressed) {
			m_function();
		}
		m_pressed = false;
		break;

	default:
		break;
	}
}

void Button::update(float dt) {
	t += dt*2;
	setBounds(200+sin(t)*50, 200+cos(t)*50, 100+cos(t)*50, 80+sin(t)*40);
}

void Button::render(sf::RenderTarget& window) {
	window.draw(m_rect);
	window.draw(m_text);
}

void Button::setFunction(std::function<void()> func) {
	m_function = func;
}

void Button::setFont(sf::Font& font) {
	m_text.setFont(font);
}

void Button::setPosX(float x) {
	m_posX = x;
	updateSize();
}

void Button::setPosY(float y) {
	m_posY = y;
	updateSize();
}

void Button::setPosition(float x, float y) {
	m_posX = x;
	m_posY = y;
	updateSize();
}

void Button::setWidth(float width) {
	m_width = width;
	updateSize();
}

void Button::setHeight(float height) {
	m_height = height;
	updateSize();
}

void Button::setSize(float width, float height) {
	m_width = width;
	m_height = height;
	updateSize();
}

void Button::setBounds(float x, float y, float width, float height) {
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	updateSize();
}

void Button::setText(std::string text) {
	m_text.setString(text);
}

void Button::updateSize() {
	m_rect.setPosition(m_posX, m_posY);
	m_rect.setSize(sf::Vector2f(m_width, m_height));

	m_text.setPosition(m_posX + m_width / 2 - m_text.getLocalBounds().width / 2, m_posY + m_height / 2 - m_text.getLocalBounds().height / 2);
}