#pragma once

#include <SFML/Graphics.hpp>

class NinePatch
{
public:
	const enum PatchIndex
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,
		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};

	NinePatch();
	~NinePatch();

	void render(sf::RenderTarget& window);
	void setTexture(sf::Texture* texture);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float width, float height);
	void setSize(sf::Vector2f size);
	void setBounds(sf::FloatRect bounds);
	void setBounds(float x, float y, float width, float height);
	void setBorderWidth(float width);

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::FloatRect getBounds();
	float getBorderWidth();

	void setPatch(PatchIndex index, sf::IntRect area);
	void setPatches(sf::IntRect area, float borderWidth);

private:
	sf::FloatRect m_bounds;
	float m_borderWidth;
	sf::Vertex* m_verticesArray;
	sf::VertexBuffer m_vertexBuffer;
	sf::RenderStates m_renderState;

	void updateVerticesPositions();
};
