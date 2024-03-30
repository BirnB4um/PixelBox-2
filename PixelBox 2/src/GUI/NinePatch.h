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

	void setPosX(float x);
	void setPosY(float y);
	void setPosition(float x, float y);
	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);
	void setBounds(float x, float y, float width, float height);
	void setBorderWidth(float width);

	void setPatch(PatchIndex index, sf::IntRect area);
	void setPatches(int left, int top, int width, int height, int borderWidth);

private:
	float m_posX, m_posY, m_width, m_height;
	float m_borderWidth;
	sf::Vertex* m_verticesArray;
	sf::VertexBuffer m_vertexBuffer;
	sf::RenderStates m_renderState;

	void updateVerticesPositions();
};
