#include "VerticalSlider.h"
#include "../Application.h"

VerticalSlider::VerticalSlider() : Slider() {
	setBounds(sf::FloatRect(0, 0, 40, 180));
}

VerticalSlider::~VerticalSlider() {
}

void VerticalSlider::updateSize() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_nob.setSize(sf::Vector2f(m_bounds.width - 2.0f * m_borderWidth, m_nobSize));
	updateNobPosition();

	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
}

void VerticalSlider::updateNobPosition() {
	float y = m_bounds.top + m_borderWidth + m_value * (m_bounds.height - 2.0f * m_borderWidth - m_nobSize);
	m_nob.setPosition(m_bounds.left + m_borderWidth, y);
}

void VerticalSlider::updateValue() {
	if (!m_pressed)
		return;

	float newValue = (static_cast<float>(Application::mousePos.y) - m_bounds.top - m_borderWidth - m_nobSize / 2.0f) / (m_bounds.height - 2.0f * m_borderWidth - m_nobSize);
	newValue = std::max(0.0f, std::min(1.0f, newValue));

	if (newValue != m_value) {
		m_value = newValue;
		m_function();
		updateNobPosition();
	}
}