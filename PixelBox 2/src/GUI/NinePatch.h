#pragma once

#include <SFML/Graphics.hpp>

class NinePatch
{
public:

	NinePatch();
	~NinePatch();

	void render(sf::RenderTarget& window);
	void setTexture(sf::Texture* texture);

	void setPosX(float x);
	void setPosY(float y);
	void setWidth(float width);
	void setHeight(float height);


private:

	sf::VertexBuffer m_vertices;
	sf::RenderStates m_renderState;


};

