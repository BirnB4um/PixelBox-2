#pragma once
#include <SFML/Graphics.hpp>

class PatchAtlas
{
public:
	PatchAtlas();
	PatchAtlas(sf::IntRect area, int borderWidth);
	PatchAtlas(int x, int y, int width, int height, int borderWidth);
	~PatchAtlas();

	static PatchAtlas angularIdle;
	static PatchAtlas angularHover;
	static PatchAtlas angularPressed;

	static PatchAtlas roundedIdle;
	static PatchAtlas roundedHover;
	static PatchAtlas roundedPressed;

	static PatchAtlas curvedIdle;
	static PatchAtlas curvedHover;
	static PatchAtlas curvedPressed;

	sf::IntRect area;
	int borderWidth;
private:

};

