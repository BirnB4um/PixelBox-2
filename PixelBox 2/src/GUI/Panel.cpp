#include "Panel.h"
#include "../Application.h"

Panel::Panel(): GuiContainer() {

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

	m_ninePatch.render(window);

	sf::View previousView = window.getView();
	updateView(previousView);

	//TODO
	//if m_panelView has a width
	if (true) {
		window.setView(m_panelView);

		GuiContainer::render(window);

		window.setView(previousView);
	}

}

void Panel::reloadResources() {
	m_ninePatch.reloadResources();
	GuiContainer::reloadResources();
}


void Panel::updateView(const sf::View& previousView) {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());

	//position of the panelwindow
	sf::Vector2f pos(m_bounds.left + m_borderWidth, m_bounds.top + m_borderWidth);
	sf::Vector2f size(m_bounds.width - 2.0f * m_borderWidth, m_bounds.height - 2.0f * m_borderWidth);

	sf::FloatRect view = m_panelViewRect;


	//parent view position.
	sf::Vector2f parentViewPos(0.0f, 0.0f); //no parent
	sf::Vector2f parentViewSize = windowSize;
	sf::Vector2f parentVieportPos(0.0f, 0.0f);
	sf::Vector2f parentViewportSize = windowSize;
	if (m_parentGui != nullptr) {
		parentViewPos = previousView.getCenter() - previousView.getSize() * 0.5f;
		parentViewSize = previousView.getSize();
		parentVieportPos.x = previousView.getViewport().left * windowSize.x;
		parentVieportPos.y = previousView.getViewport().top * windowSize.y;
		parentViewportSize.x = previousView.getViewport().width * windowSize.x;
		parentViewportSize.y = previousView.getViewport().height * windowSize.y;
	}

	sf::Vector2f offset = pos - parentViewPos;

	sf::FloatRect viewport(0, 0, 0, 0);
	viewport.left = parentVieportPos.x + offset.x;
	viewport.top = parentVieportPos.y + offset.y;

	//check if offset is outside of parentView and correct it
	if (offset.x < 0) {
		view.left -= offset.x;
		view.width += offset.x;
		viewport.left = parentVieportPos.x;
	}
	if (offset.x > parentViewSize.x - view.width) {
		view.width = parentViewportSize.x - offset.x;
	}
	if (offset.x > parentViewportSize.x) {//useless???
		offset.x = parentViewportSize.x;
	}
	
	
	if (offset.y < 0) {
		view.top -= offset.y;
		view.height += offset.y;
		viewport.top = parentVieportPos.y;
	}
	if (offset.y > parentViewSize.y - view.height) {
		view.height = parentViewportSize.y - offset.y;
	}
	if (offset.y > parentViewportSize.y) {//useless???
		offset.y = parentViewportSize.y;
	}

	viewport.width = std::max(view.width, 0.0f);
	viewport.height = std::max(view.height, 0.0f);

	//normalize viewport
	viewport.left /= windowSize.x;
	viewport.top /= windowSize.y;
	viewport.width /= windowSize.x;
	viewport.height /= windowSize.y;

	//update m_panelView from view and m_panelView.viewport from viewport
	m_panelView.setSize(view.width, view.height);
	m_panelView.setCenter(view.left + view.width/2.0f, view.top + view.height/2.0f);
	m_panelView.setViewport(viewport);
}


void Panel::updateBounds() {
	m_bounds.width = std::max(m_bounds.width, 2.0f * m_borderWidth);
	m_bounds.height = std::max(m_bounds.height, 2.0f * m_borderWidth);

	m_panelViewRect.width = m_bounds.width - 2.0f * m_borderWidth;
	m_panelViewRect.height = m_bounds.height - 2.0f * m_borderWidth;
	updateViewRect();

	m_ninePatch.setBorderWidth(m_borderWidth);
	m_ninePatch.setBounds(m_bounds);
}

void Panel::updateMouseOffset() {
	m_mouseOffset.x = m_bounds.left + m_borderWidth - m_panelViewRect.left;
	m_mouseOffset.y = m_bounds.top + m_borderWidth - m_panelViewRect.top;
}

void Panel::updateViewRect() {
	m_interactableArea = m_panelViewRect;
	updateMouseOffset();
}