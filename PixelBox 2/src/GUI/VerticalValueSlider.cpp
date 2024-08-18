#include "VerticalValueSlider.h"
#include "../Application.h"

VerticalValueSlider::VerticalValueSlider() : ValueSlider() {

}

VerticalValueSlider::~VerticalValueSlider() {

}

void VerticalValueSlider::updateNobPosition() {
	float zeroPos = ((-m_minValue) / (m_maxValue - m_minValue));
	zeroPos = Utils::constrain(zeroPos, 0.0f, 1.0f);

	float valuePos = (m_value - m_minValue) / (m_maxValue - m_minValue);
	if (zeroPos > valuePos)
		std::swap(zeroPos, valuePos);

	float y = m_bounds.top + m_borderWidth + zeroPos * (m_bounds.height - 2.0f * m_borderWidth);
	float height = (valuePos - zeroPos) * (m_bounds.height - 2.0f * m_borderWidth);
	m_nob.setSize(sf::Vector2f(m_bounds.width - 2.0f * m_borderWidth, height));
	m_nob.setPosition(m_bounds.left + m_borderWidth, y);
}

void VerticalValueSlider::updateValue() {
	if (!m_pressed)
		return;

	float newValue = (getMousePos().y - m_bounds.top - m_borderWidth) / (m_bounds.height - 2.0f * m_borderWidth);
	newValue = Utils::constrain(newValue, 0.0f, 1.0f);
	newValue = m_minValue + newValue * (m_maxValue - m_minValue);

	if (newValue != m_value) {
		m_value = newValue;
		m_function();
		updateNobPosition();
	}
}

void VerticalValueSlider::updateZeroLine() {
	float zeroPos = ((-m_minValue) / (m_maxValue - m_minValue));
	if (zeroPos <= 0.0f || zeroPos >= 1.0f) {
		m_drawZeroLine = false;
		return;
	}

	m_drawZeroLine = true;
	zeroPos = zeroPos * (m_bounds.height - 2.0f * m_borderWidth) + m_bounds.top + m_borderWidth;
	m_zeroLine.setPosition(m_bounds.left + m_borderWidth, zeroPos);
	m_zeroLine.setSize(sf::Vector2f(m_bounds.width - 2.0f * m_borderWidth, 1.0f));

	ValueSlider::updateZeroLine();
}
