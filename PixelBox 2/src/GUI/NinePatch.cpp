#include "NinePatch.h"

NinePatch::NinePatch() {
	m_vertices = sf::VertexBuffer(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static);
	m_vertices.create(54); // 6 * 9 vertices
}

NinePatch::~NinePatch() {

}

void NinePatch::setTexture(sf::Texture *texture) {
	m_renderState = sf::RenderStates(texture);
}

void NinePatch::render(sf::RenderTarget& window) {
	window.draw(m_vertices, m_renderState);
}