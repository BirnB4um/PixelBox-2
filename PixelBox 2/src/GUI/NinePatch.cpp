#include "NinePatch.h"

NinePatch::NinePatch() : GuiElement() {
	m_vertexBuffer = sf::VertexBuffer(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static);
	m_vertexBuffer.create(54); // 6 * 9 vertices

	m_verticesArray = new sf::Vertex[54];

	m_bounds = sf::FloatRect(0.0f, 0.0f, 10.0f, 10.0f);
	m_borderWidth = 1.0f;

	updateBounds();
	setPatches(sf::IntRect(0, 0, 3, 3), 1.0f);
}

NinePatch::~NinePatch() {
	delete[] m_verticesArray;
}

void NinePatch::setTexture(sf::Texture* texture) {
	m_renderState = sf::RenderStates(texture);
}

void NinePatch::render(sf::RenderTarget& window) {
	window.draw(m_vertexBuffer, m_renderState);
}

void NinePatch::setPatch(PatchIndex patchIndex, sf::IntRect area) {
	int index = 6 * patchIndex;
	m_verticesArray[index++].texCoords = sf::Vector2f(area.left, area.top); // top left
	m_verticesArray[index++].texCoords = sf::Vector2f(area.left + area.width, area.top); // top right
	m_verticesArray[index++].texCoords = sf::Vector2f(area.left + area.width, area.top + area.height); // bottom right

	m_verticesArray[index++].texCoords = sf::Vector2f(area.left, area.top); // top left
	m_verticesArray[index++].texCoords = sf::Vector2f(area.left + area.width, area.top + area.height); // bottom right
	m_verticesArray[index++].texCoords = sf::Vector2f(area.left, area.top + area.height); // bottom left

	m_vertexBuffer.update(m_verticesArray);
}

void NinePatch::setPatches(sf::IntRect area, float borderWidth) {
	float x = area.left;
	float y = area.top;
	float w = area.width;
	float h = area.height;
	float bw = borderWidth;

	// points for corners
	float xs[4] = { x + 0.01f, x + bw, x + w - bw, x + w - 0.01f };
	float ys[4] = { y + 0.01f, y + bw, y + h - bw, y + h - 0.01f };

	int index = 0;
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			sf::Vector2f topLeft(xs[col], ys[row]);
			sf::Vector2f topRight(xs[col + 1], ys[row]);
			sf::Vector2f bottomLeft(xs[col], ys[row + 1]);
			sf::Vector2f bottomRight(xs[col + 1], ys[row + 1]);

			// First triangle
			m_verticesArray[index++].texCoords = topLeft;
			m_verticesArray[index++].texCoords = topRight;
			m_verticesArray[index++].texCoords = bottomRight;

			// Second triangle
			m_verticesArray[index++].texCoords = topLeft;
			m_verticesArray[index++].texCoords = bottomRight;
			m_verticesArray[index++].texCoords = bottomLeft;
		}
	}

	m_vertexBuffer.update(m_verticesArray);
}

void NinePatch::setPatches(PatchAtlas& atlas) {
	setPatches(atlas.area, atlas.borderWidth);
}

void NinePatch::updateBounds() {
	float x = m_bounds.left;
	float y = m_bounds.top;
	float w = m_bounds.width;
	float h = m_bounds.height;
	float bw = m_borderWidth;

	// points for corners
	float xs[4] = { x, x + bw, x + w - bw, x + w };
	float ys[4] = { y, y + bw, y + h - bw, y + h };

	int index = 0;
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			sf::Vector2f topLeft(xs[col], ys[row]);
			sf::Vector2f topRight(xs[col + 1], ys[row]);
			sf::Vector2f bottomLeft(xs[col], ys[row + 1]);
			sf::Vector2f bottomRight(xs[col + 1], ys[row + 1]);

			// First triangle
			m_verticesArray[index++].position = topLeft;
			m_verticesArray[index++].position = topRight;
			m_verticesArray[index++].position = bottomRight;

			// Second triangle
			m_verticesArray[index++].position = topLeft;
			m_verticesArray[index++].position = bottomRight;
			m_verticesArray[index++].position = bottomLeft;
		}
	}

	m_vertexBuffer.update(m_verticesArray);
}

void NinePatch::reloadResources() {
	setTexture(ResourceManager::getGuiTexture());
}