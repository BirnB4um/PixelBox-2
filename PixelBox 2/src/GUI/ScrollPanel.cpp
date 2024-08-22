#include "ScrollPanel.h"

ScrollPanel::ScrollPanel() : Panel() {
	m_sliderWidth = 25.0f;
	m_minSliderNobSize = 20.0f;
	m_elementsBorder = 10.0f;

	m_totalRenderSize = sf::FloatRect(0, 0, 0, 0);

	m_horizontalSlider.setRange(0, 1);
	m_horizontalSlider.setBorderWidth(1);
	m_horizontalSlider.setNobSize(m_minSliderNobSize);
	m_horizontalSlider.setFunction([this]() {
		m_panelViewRect.left = m_totalRenderSize.left + m_horizontalSlider.getValue();
		updateViewRect();
		});
	m_horizontalSlider.setValue(0);

	m_verticalSlider.setRange(0, 1);
	m_verticalSlider.setBorderWidth(1);
	m_verticalSlider.setNobSize(m_minSliderNobSize);
	m_verticalSlider.setFunction([this]() {
		m_panelViewRect.top = m_totalRenderSize.top + m_verticalSlider.getValue();
		updateViewRect();
		});
	m_verticalSlider.setValue(0);

	setScrollable(true, false);
	updateTotalRenderSize();
}

ScrollPanel::~ScrollPanel() {
}

bool ScrollPanel::handleEvent(sf::Event& sfEvent) {
	if (!m_isInteractable)
		return false;

	if (Panel::handleEvent(sfEvent))
		return true;

	if (m_horizontalScrollable && m_horizontalSlider.handleEvent(sfEvent))
		return true;

	if (m_verticalScrollable && m_verticalSlider.handleEvent(sfEvent))
		return true;

	switch (sfEvent.type)
	{
	case sf::Event::MouseButtonPressed:
		if (isMouseOver())
			return true;
	case sf::Event::MouseWheelScrolled:
		if (isMouseOver()) {
			float delta = -sfEvent.mouseWheelScroll.delta * 50.0f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				if (m_horizontalScrollable)
					m_horizontalSlider.setValue(m_horizontalSlider.getValue() + delta);
			}
			else {
				if (m_verticalScrollable)
					m_verticalSlider.setValue(m_verticalSlider.getValue() + delta);
			}

			return true;
		}
	default:
		break;
	}

	return false;
}

void ScrollPanel::update(float dt) {
	if (!m_isInteractable)
		return;

	if(m_horizontalScrollable)
		m_horizontalSlider.update(dt);

	if(m_verticalScrollable)
		m_verticalSlider.update(dt);

	Panel::update(dt);
}

void ScrollPanel::render(sf::RenderTarget& window) {
	Panel::render(window);

	if (m_verticalScrollable)
		m_verticalSlider.render(window);

	if (m_horizontalScrollable)
		m_horizontalSlider.render(window);
}

void ScrollPanel::reloadResources() {
	m_horizontalSlider.reloadResources();
	m_verticalSlider.reloadResources();
	Panel::reloadResources();
}

void ScrollPanel::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_panelViewRect.width = m_bounds.width - 2.0f * m_borderWidth;
	m_panelViewRect.height = m_bounds.height - 2.0f * m_borderWidth;

	if (m_verticalScrollable) {
		m_verticalSlider.setSize((m_sliderWidth), (m_bounds.height - 2.0f * m_borderWidth - (m_horizontalScrollable ? m_sliderWidth : 0.0f)));
		m_verticalSlider.setPosition((m_bounds.left + m_bounds.width - m_borderWidth - m_sliderWidth), (m_bounds.top + m_borderWidth));
		m_panelViewRect.width -= m_sliderWidth;
	}

	if (m_horizontalScrollable) {
		m_horizontalSlider.setSize((m_bounds.width - 2.0f * m_borderWidth - (m_verticalScrollable ? m_sliderWidth : 0.0f)), (m_sliderWidth));
		m_horizontalSlider.setPosition((m_bounds.left + m_borderWidth), (m_bounds.top + m_bounds.height - m_borderWidth - m_sliderWidth));
		m_panelViewRect.height -= m_sliderWidth;
	}

	updateViewRect();
	updateSliders();

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
}

void ScrollPanel::clearElements() {
	GuiContainer::clearElements();
	updateTotalRenderSize();
}

void ScrollPanel::addElement(GuiElement* element) {
	GuiContainer::addElement(element);
	updateTotalRenderSize();
}

void ScrollPanel::setScrollable(bool vertical, bool horizontal) {
	m_verticalScrollable = vertical;
	m_horizontalScrollable = horizontal;
	updateBounds();
}

void ScrollPanel::setSliderWidth(float width) {
	m_sliderWidth = width;
	updateBounds();
}

void ScrollPanel::updateTotalRenderSize() {
	float minX = 1000000, maxX = -1000000, minY = 1000000, maxY = -1000000;
	for (GuiElement* element : m_elements) {
		sf::FloatRect bounds = element->getBounds();
		if (bounds.left - m_elementsBorder < minX)
			minX = bounds.left - m_elementsBorder;
		if (bounds.left + bounds.width + m_elementsBorder > maxX)
			maxX = bounds.left + bounds.width + m_elementsBorder;
		if (bounds.top - m_elementsBorder < minY)
			minY = bounds.top - m_elementsBorder;
		if (bounds.top + bounds.height + m_elementsBorder > maxY)
			maxY = bounds.top + bounds.height + m_elementsBorder;
	}
	m_totalRenderSize = sf::FloatRect(minX, minY, maxX - minX, maxY - minY);

	updateSliders();
}

void ScrollPanel::updateSliders() {
	sf::Vector2f visiblePortion(m_panelViewRect.width / m_totalRenderSize.width, m_panelViewRect.height / m_totalRenderSize.height);
	sf::Vector2f remainingSize(m_totalRenderSize.width - m_panelViewRect.width, m_totalRenderSize.height - m_panelViewRect.height);
	sf::Vector2f offset(m_panelViewRect.left - m_totalRenderSize.left, m_panelViewRect.top - m_totalRenderSize.top);

	m_horizontalSlider.setNobSize(std::max(m_minSliderNobSize,
		std::min(visiblePortion.x, 1.0f) * (m_horizontalSlider.getBounds().width - m_horizontalSlider.getBorderWidth() * 2.0f)));
	m_horizontalSlider.setRange(0, std::max(0.0f, remainingSize.x));
	m_horizontalSlider.setValue(offset.x);

	m_verticalSlider.setNobSize(std::max(m_minSliderNobSize,
		std::min(visiblePortion.y, 1.0f) * (m_verticalSlider.getBounds().height - m_verticalSlider.getBorderWidth() * 2.0f)));
	m_verticalSlider.setRange(0, std::max(0.0f, remainingSize.y));
	m_verticalSlider.setValue(offset.y);
}

void ScrollPanel::setParent(GuiContainer* parent) {
	m_parentGui = parent;
	m_horizontalSlider.setParent(parent);
	m_verticalSlider.setParent(parent);
}

void ScrollPanel::resetSliders() {
	m_panelViewRect.top = m_totalRenderSize.top;
	m_panelViewRect.left = m_totalRenderSize.left;
	updateSliders();
	updateViewRect();
}

void ScrollPanel::resetInteractionState() {
	GuiContainer::resetInteractionState();
	m_horizontalSlider.resetInteractionState();
	m_verticalSlider.resetInteractionState();
}