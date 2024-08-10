#include "VerticalSlider.h"
#include "../Application.h"

VerticalSlider::VerticalSlider() : Slider() {
	setBounds(sf::FloatRect(0, 0, 40, 180));
}

VerticalSlider::~VerticalSlider() {
}

void VerticalSlider::updateBounds() {
	Slider::updateBounds();

	m_nob.setSize(sf::Vector2f(m_bounds.width - 2.0f * m_borderWidth, m_nobSize));
	updateNobPosition();
}

void VerticalSlider::updateNobPosition() {
	float y = m_bounds.top + m_borderWidth + m_value * (m_bounds.height - 2.0f * m_borderWidth - m_nobSize);
	m_nob.setPosition(m_bounds.left + m_borderWidth, y);
}

void VerticalSlider::updateValue() {
	if (!m_pressed)
		return;

	float newValue = (getMousePos().y - m_mouseGrabOffset.y - m_bounds.top - m_borderWidth) / (m_bounds.height - 2.0f * m_borderWidth - m_nobSize);
	newValue = std::max(0.0f, std::min(1.0f, newValue));

	if (newValue != m_value) {
		m_value = newValue;
		m_function();
		updateNobPosition();
	}
}