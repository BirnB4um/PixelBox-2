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

	
	//copy constructor
	NinePatch(const NinePatch& other) : GuiElement(other) {
		m_vertexBuffer = other.m_vertexBuffer;
		m_renderState = other.m_renderState;

		m_verticesArray = new sf::Vertex[54];
		for (int i = 0; i < 54; ++i) {
			m_verticesArray[i] = other.m_verticesArray[i];
		}
	}

	//copy assignment operator
	NinePatch& operator=(const NinePatch& other) {
		if (this != &other) {
			GuiElement::operator=(other);

			m_vertexBuffer = other.m_vertexBuffer;
			m_renderState = other.m_renderState;

			delete[] m_verticesArray;
			m_verticesArray = new sf::Vertex[54];
			for (int i = 0; i < 54; ++i) {
				m_verticesArray[i] = other.m_verticesArray[i];
			}
		}
		return *this;
	}

	//move constructor
	NinePatch(NinePatch&& other) noexcept : GuiElement(std::move(other)) {
		m_vertexBuffer = other.m_vertexBuffer;
		m_renderState = other.m_renderState;

		m_verticesArray = other.m_verticesArray;
		other.m_verticesArray = nullptr;
	}

	//move assignment operator
	NinePatch& operator=(NinePatch&& other) noexcept {
		if (this != &other) {
			GuiElement::operator=(std::move(other));

			m_vertexBuffer = other.m_vertexBuffer;
			m_renderState = other.m_renderState;

			delete[] m_verticesArray;
			m_verticesArray = other.m_verticesArray;
			other.m_verticesArray = nullptr;
		}
		return *this;
	}



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
