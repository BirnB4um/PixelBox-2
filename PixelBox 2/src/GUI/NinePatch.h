#pragma once

#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "PatchAtlas.h"
#include "../ResourceManager.h"

class NinePatch : public GuiElement
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

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;
	void setTexture(sf::Texture* texture);

	void setPatch(PatchIndex index, sf::IntRect area);
	void setPatches(sf::IntRect area, float borderWidth);
	void setPatches(PatchAtlas& atlas);

private:
	sf::Vertex* m_verticesArray;
	sf::VertexBuffer m_vertexBuffer;
	sf::RenderStates m_renderState;

	void updateBounds() override;
};
