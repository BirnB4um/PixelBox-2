#include "TextRect.h"
#include "../Application.h"

TextRect::TextRect() {
	m_borderWidth = 0.0f;
	setBounds(0, 0, 150, 80);

	m_text.setString("");
	m_text.setCharacterSize(20);
	m_text.setPosition(0.0f, 0.0f);
	m_text.setFillColor(sf::Color(255, 255, 255));

	m_textAlignment = Alignment::Center;
}

void TextRect::update(float dt) {

}

void TextRect::render(sf::RenderTarget& window) {
	
	sf::View previousView = window.getView();

	updateTextView(previousView);
	window.setView(m_textView);

	window.draw(m_text);

	window.setView(previousView);

}

void TextRect::reloadResources() {
	m_text.setFont(*ResourceManager::getPixelFont());
}

void TextRect::updateTextView(const sf::View& previousView) {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());

	//position of the panelwindow
	sf::Vector2f pos(m_bounds.left, m_bounds.top);
	sf::Vector2f size(m_bounds.width, m_bounds.height);
	float boundsRatio = size.x / size.y;


	sf::FloatRect textArea = m_text.getLocalBounds();
	//float padding = m_text.getCharacterSize() * 0.5f;
	//textArea.left -= padding;
	////textArea.top -= padding;
	////textArea.height += 2 * padding;
	//textArea.width += 2 * padding;

	//view has to be same size as m_bounds
	sf::FloatRect view(0.0f, 0.0f, size.x, size.y);

	
	if (m_textAlignment == Alignment::TopLeft || 
		m_textAlignment == Alignment::CenterLeft ||
		m_textAlignment == Alignment::BottomLeft) {
		view.left = textArea.left;
	}
	else if (m_textAlignment == Alignment::TopCenter ||
		m_textAlignment == Alignment::Center ||
		m_textAlignment == Alignment::BottomCenter) {
		view.left = textArea.left + textArea.width / 2.0f - view.width / 2.0f;
	}
	else if (m_textAlignment == Alignment::TopRight ||
		m_textAlignment == Alignment::CenterRight ||
		m_textAlignment == Alignment::BottomRight) {
		view.left = textArea.left + textArea.width - view.width;
	}

	if (m_textAlignment == Alignment::TopLeft ||
		m_textAlignment == Alignment::TopCenter ||
		m_textAlignment == Alignment::TopRight) {
		view.top = textArea.top;
	}
	else if (m_textAlignment == Alignment::CenterLeft ||
		m_textAlignment == Alignment::Center ||
		m_textAlignment == Alignment::CenterRight) {
		view.top = textArea.top + textArea.height / 2.0f - view.height / 2.0f;
	}
	else if (m_textAlignment == Alignment::BottomLeft ||
		m_textAlignment == Alignment::BottomCenter ||
		m_textAlignment == Alignment::BottomRight) {
		view.top = textArea.top + textArea.height - view.height;
	}

	//parent view position.
	sf::Vector2f parentViewPos(0.0f, 0.0f); //no parent
	sf::Vector2f parentViewSize = windowSize;
	sf::Vector2f parentVieportPos(0.0f, 0.0f);
	sf::Vector2f parentViewportSize = windowSize;
	if (m_parentGui != nullptr) {
		parentViewPos = previousView.getCenter() - previousView.getSize() / 2.0f;
		parentViewSize = previousView.getSize();
		parentVieportPos.x = previousView.getViewport().left * windowSize.x;
		parentVieportPos.y = previousView.getViewport().top * windowSize.y;
		parentViewportSize.x = previousView.getViewport().width * windowSize.x;
		parentViewportSize.y = previousView.getViewport().height * windowSize.y;
	}


	sf::Vector2f offset = pos - parentViewPos;

	sf::FloatRect viewport(0, 0, 0, 0);
	viewport.left = parentVieportPos.x + offset.x;
	viewport.top = parentVieportPos.y + offset.y + size.y / 2.0f - view.height / 2.0f;


	//check if offset is outside of parentView and correct it
	if (offset.x < 0) {
		view.left -= offset.x;
		view.width += offset.x;
	}
	if (offset.x > parentViewSize.x - view.width) {
		view.width = parentViewportSize.x - offset.x;
	}

	if (offset.y < 0) {
		view.top -= offset.y;
		view.height += offset.y;
	}
	if (offset.y > parentViewSize.y - view.height) {
		view.height = parentViewportSize.y - offset.y;
	}

	viewport.width = std::max(view.width, 0.0f);
	viewport.height = std::max(view.height, 0.0f);
	viewport.left = Utils::constrain(viewport.left, parentVieportPos.x, parentVieportPos.x + parentViewportSize.x - viewport.width);
	viewport.top = Utils::constrain(viewport.top, parentVieportPos.y, parentVieportPos.y + parentViewportSize.y - viewport.height);

	//normalize viewport
	viewport.left /= windowSize.x;
	viewport.top /= windowSize.y;
	viewport.width /= windowSize.x;
	viewport.height /= windowSize.y;

	//update m_panelView from view and m_panelView.viewport from viewport
	m_textView.setSize(view.width, view.height);
	m_textView.setCenter(view.left + view.width / 2.0f, view.top + view.height / 2.0f);
	m_textView.setViewport(viewport);
}

