#include "ScrollPanel.h"

ScrollPanel::ScrollPanel() : Panel() {
	m_sliderWidth = 30.0f;
	m_minSliderNobSize = 20.0f;
	m_elementsBorder = 10.0f;

	m_horizontalSlider.setRange(0, 1);
	m_horizontalSlider.setBorderWidth(1);
	m_horizontalSlider.setNobSize(m_minSliderNobSize);
	m_horizontalSlider.setFunction([this]() {
		m_textureViewRect.left = m_totalRenderSize.left + m_horizontalSlider.getValue();
		updateViewFromRect(m_textureViewRect);
		});
	m_horizontalSlider.setValue(0);

	m_verticalSlider.setRange(0, 1);
	m_verticalSlider.setBorderWidth(1);
	m_verticalSlider.setNobSize(m_minSliderNobSize);
	m_verticalSlider.setFunction([this]() {
		m_textureViewRect.top = m_totalRenderSize.top + m_verticalSlider.getValue();
		updateViewFromRect(m_textureViewRect);
		});
	m_verticalSlider.setValue(0);

	setScrollable(true, false);
	updateTotalRenderSize();
}

ScrollPanel::~ScrollPanel() {
}

bool ScrollPanel::handleEvent(sf::Event& sfEvent) {
	//TODO: return true if anything captures the event

	//switch (sfEvent.type)
	//{
	//default:
	//	break;
	//}

	Panel::handleEvent(sfEvent);

	m_horizontalSlider.handleEvent(sfEvent);
	m_verticalSlider.handleEvent(sfEvent);

	return false;
}

void ScrollPanel::update(float dt) {
	m_horizontalSlider.update(dt);
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

	updateMouseOffset();

	m_renderSprite.setPosition(m_bounds.left + m_borderWidth, m_bounds.top + m_borderWidth);

	if (m_verticalScrollable) {
		m_verticalSlider.setSize((m_sliderWidth), (m_bounds.height - 2.0f * m_borderWidth - (m_horizontalScrollable ? m_sliderWidth : 0.0f)));
		m_verticalSlider.setPosition((m_bounds.left + m_bounds.width - m_borderWidth - m_sliderWidth), (m_bounds.top + m_borderWidth));
	}

	if (m_horizontalScrollable) {
		m_horizontalSlider.setSize((m_bounds.width - 2.0f * m_borderWidth - (m_verticalScrollable ? m_sliderWidth : 0.0f)), (m_sliderWidth));
		m_horizontalSlider.setPosition((m_bounds.left + m_borderWidth), (m_bounds.top + m_bounds.height - m_borderWidth - m_sliderWidth));
	}

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);

	//resize texture if size changed
	sf::Vector2i new_size((m_verticalScrollable ? m_verticalSlider.getPosition().x : m_bounds.left + m_bounds.width - m_borderWidth) - m_bounds.left - m_borderWidth,
		(m_horizontalScrollable ? m_horizontalSlider.getPosition().y : m_bounds.top + m_bounds.height - m_borderWidth) - m_bounds.top - m_borderWidth);
	new_size.x = std::min(std::max(new_size.x, 1), 2048);
	new_size.y = std::min(std::max(new_size.y, 1), 2048);
	if (m_renderTexture.getSize() != static_cast<sf::Vector2u>(new_size)) {
		m_renderTexture.create(new_size.x, new_size.y);
		m_renderSprite.setTexture(m_renderTexture.getTexture(), true);

		m_textureViewRect.width = new_size.x;
		m_textureViewRect.height = new_size.y;
		updateViewFromRect(m_textureViewRect);
		updateSliders();
	}
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
	float minX = 0, maxX = m_bounds.width, minY = 0, maxY = m_bounds.height;
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

	sf::Vector2f visiblePortion(m_textureViewRect.width / m_totalRenderSize.width, m_textureViewRect.height / m_totalRenderSize.height);
	sf::Vector2f remainingSize(m_totalRenderSize.width - m_textureViewRect.width, m_totalRenderSize.height - m_textureViewRect.height);
	sf::Vector2f offset(m_textureViewRect.left - m_totalRenderSize.left, m_textureViewRect.top - m_totalRenderSize.top);

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