#include "HorizontalSlider.h"
#include "../Application.h"

HorizontalSlider::HorizontalSlider(): Slider() {
	setBounds(sf::FloatRect(0, 0, 180, 40));
}

HorizontalSlider::~HorizontalSlider() {
}

void HorizontalSlider::updateBounds() {
	Slider::updateBounds();

	m_nob.setSize(sf::Vector2f(m_nobSize, m_bounds.height - 2.0f * m_borderWidth));
	updateNobPosition();
}

void HorizontalSlider::updateNobPosition() {
	float x = m_bounds.left + m_borderWidth + m_value * (m_bounds.width - 2.0f * m_borderWidth - m_nobSize);
	m_nob.setPosition(x, m_bounds.top + m_borderWidth);
}

void HorizontalSlider::updateValue() {
	if (!m_pressed)
		return;

	float newValue = (getMousePos().x - m_mouseGrabOffset.x - m_bounds.left - m_borderWidth) / (m_bounds.width - 2.0f * m_borderWidth - m_nobSize);
	newValue = std::max(0.0f, std::min(1.0f, newValue));
	
	if (newValue != m_value) {
		m_value = newValue;
		m_function();
		updateNobPosition();
	}
}