#include "ValueSlider.h"
#include "../Application.h"


ValueSlider::ValueSlider() : InteractableGui() {
	m_nob.setFillColor(sf::Color(60, 120, 200));
	m_zeroLine.setFillColor(sf::Color(255, 255, 255, 255));

	m_value = 0.0f;
	m_minValue = 0.0f;
	m_maxValue = 1.0f;

	m_ninePatch.setPatches(PatchAtlas::angularIdle);
	setBounds(sf::FloatRect(0, 0, 80, 40));
	setBorderWidth(1);

	m_hovered = false;
	m_pressed = false;
	m_drawZeroLine = false;

	m_function = []() {};
}

ValueSlider::~ValueSlider() {

}

bool ValueSlider::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::MouseMoved:
		updateInteraction();
		updateValue();

		if (m_pressed)
			return true;
		break;

	case sf::Event::MouseButtonPressed:
		if (m_hovered) {
			m_pressed = true;
			updateValue();
			return true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		m_pressed = false;
		updateInteraction();
		return false;
		break;

	default:
		break;
	}

	return false;
}

void ValueSlider::updateInteraction() {
	sf::Vector2f mouse = getMousePos();
	if (isMouseOver()) {
		if (!m_hovered) {
			m_ninePatch.setPatches(PatchAtlas::angularHover);
		}
		m_hovered = true;
	}
	else {
		if (m_hovered && !m_pressed) {
			m_ninePatch.setPatches(PatchAtlas::angularIdle);
			m_hovered = false;
		}
	}
}

void ValueSlider::update(float dt) {

}

void ValueSlider::render(sf::RenderTarget& window) {
	m_ninePatch.render(window);
	window.draw(m_nob);
	if (m_drawZeroLine) {
		window.draw(m_zeroLine);
	}
}

void ValueSlider::reloadResources() {
	m_ninePatch.reloadResources();
}

void ValueSlider::setFunction(std::function<void()> func) {
	m_function = func;
}

void ValueSlider::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
	updateInteraction();
	updateNobPosition();
	updateZeroLine();
}

float ValueSlider::getValue() {
	return m_value;
}

void ValueSlider::setValue(float value) {
	m_value = value;
	m_value = std::max(m_value, m_minValue);
	m_value = std::min(m_value, m_maxValue);

	updateNobPosition();
	m_function();
}

void ValueSlider::setRange(float min, float max) {
	if (min == max)
		max += 0.0001f;

	m_minValue = min;
	m_maxValue = max;
	m_value = Utils::constrain(m_value, m_minValue, m_maxValue);

	updateZeroLine();
}

void ValueSlider::updateNobPosition() {

}

void ValueSlider::updateValue() {

}

void ValueSlider::updateZeroLine() {
	updateNobPosition();
}

void ValueSlider::resetInteractionState() {
	m_pressed = false;
	m_hovered = false;
	m_ninePatch.setPatches(PatchAtlas::angularIdle);
	updateInteraction();
}

