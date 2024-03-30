#include "NinePatch.h"

NinePatch::NinePatch() {
	m_vertexBuffer = sf::VertexBuffer(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static);
	m_vertexBuffer.create(54); // 6 * 9 vertices

	m_verticesArray = new sf::Vertex[54];

	m_posX = 0;
	m_posY = 0;
	m_width = 50;
	m_height = 50;
	m_borderWidth = 1;

	updateVerticesPositions();
	setPatches(0, 0, 3, 3, 1);
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

void NinePatch::setPosX(float x) {
	m_posX = x;
	updateVerticesPositions();
}
void NinePatch::setPosY(float y) {
	m_posY = y;
	updateVerticesPositions();
}

void NinePatch::setWidth(float width) {
	m_width = width;
	updateVerticesPositions();
}

void NinePatch::setHeight(float height) {
	m_height = height;
	updateVerticesPositions();
}

void NinePatch::setSize(float width, float height) {
	m_width = width;
	m_height = height;
	updateVerticesPositions();
}

void NinePatch::setPosition(float x, float y) {
	m_posX = x;
	m_posY = y;
	updateVerticesPositions();
}

void NinePatch::setBounds(float x, float y, float width, float height) {
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	updateVerticesPositions();
}

void NinePatch::setBorderWidth(float width) {
	m_borderWidth = width;
	updateVerticesPositions();
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

void NinePatch::setPatches(int left, int top, int width, int height, int borderWidth) {
	float x = left;
	float y = top;
	float w = width;
	float h = height;
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

void NinePatch::updateVerticesPositions() {
	float x = m_posX;
	float y = m_posY;
	float w = m_width;
	float h = m_height;
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