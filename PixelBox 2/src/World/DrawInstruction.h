#pragma once

#include <SFML/Graphics.hpp>

struct DrawInstruction
{
	enum class Type
	{
		LINE,
		RECTANGLE,
		FILL,
		STRUCTURE,
	};

	//the Drawinstruction takes ownership of the structure pointer
	//the structure pointer size is determined by startPos and endPos
	//the width parameter is only used for LINE
	DrawInstruction(uint32_t pixelData, sf::Vector2i startPos, sf::Vector2i endPos, Type type, float width = 1.0f, uint8_t* structure = nullptr)
		: pixelData(pixelData), startPos(startPos), endPos(endPos), type(type), width(width), structure(structure)
	{
	}

	sf::Vector2i startPos;
	sf::Vector2i endPos;
	float width = 1.0f;
	Type type;
	uint32_t pixelData;

	uint8_t* structure = nullptr;
};

