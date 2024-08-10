#include "Panel.h"


Panel::Panel(): GuiContainer() {

	m_textureViewRect = sf::FloatRect(0, 0, 1, 1);
	updateViewFromRect(m_textureViewRect);
	m_renderTexture.create(1, 1);
	m_renderTexture.setView(m_textureView);
	m_renderSprite.setTexture(m_renderTexture.getTexture(), true);

	m_ninePatch.setPatches(PatchAtlas::roundedIdle);

	m_bounds = sf::FloatRect(0, 0, 200, 200);
	m_borderWidth = 2.0f;

}

Panel::~Panel() {

}

bool Panel::handleEvent(sf::Event& sfEvent) {
	//TODO: return true if something captures the event

	//switch (sfEvent.type)
	//{
	//default:
	//	break;
	//}

	m_ninePatch.handleEvent(sfEvent);

	GuiContainer::handleEvent(sfEvent);

	return false;
}

void Panel::update(float dt) {
	m_ninePatch.update(dt);
	GuiContainer::update(dt);
}

void Panel::render(sf::RenderTarget& window) {
	//draw elements onto texture
	m_renderTexture.setView(m_textureView);
	m_renderTexture.clear(sf::Color::Transparent);
	GuiContainer::render(m_renderTexture);
	m_renderTexture.display();

	m_ninePatch.render(window);
	window.draw(m_renderSprite);
}

void Panel::reloadResources() {
	m_ninePatch.reloadResources();
	GuiContainer::reloadResources();
}


void Panel::updateViewFromRect(sf::FloatRect& rect) {
	m_textureView.setSize(rect.width, rect.height);
	m_textureView.setCenter(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

	updateMouseOffset();

	m_interactableArea = m_textureViewRect;
}

void Panel::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	updateMouseOffset();

	m_renderSprite.setPosition(m_bounds.left + m_borderWidth, m_bounds.top + m_borderWidth);

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);

	//resize texture if size changed
	sf::Vector2i new_size(m_bounds.left + m_bounds.width - m_borderWidth - m_bounds.left - m_borderWidth,
		m_bounds.top + m_bounds.height - m_borderWidth - m_bounds.top - m_borderWidth);
	new_size.x = std::min(std::max(new_size.x, 1), 2048);
	new_size.y = std::min(std::max(new_size.y, 1), 2048);

	if (m_renderTexture.getSize() != static_cast<sf::Vector2u>(new_size)) {
		m_renderTexture.create(new_size.x, new_size.y);
		m_renderSprite.setTexture(m_renderTexture.getTexture(), true);

		m_textureViewRect.width = new_size.x;
		m_textureViewRect.height = new_size.y;
		updateViewFromRect(m_textureViewRect);
	}
}

void Panel::updateMouseOffset() {
	m_mouseOffset.x = m_renderSprite.getPosition().x - m_textureViewRect.left;
	m_mouseOffset.y = m_renderSprite.getPosition().y - m_textureViewRect.top;
}
