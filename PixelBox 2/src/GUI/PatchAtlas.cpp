#include "PatchAtlas.h"

PatchAtlas PatchAtlas::angularIdle = PatchAtlas(1, 1, 3, 3, 1);
PatchAtlas PatchAtlas::angularHover = PatchAtlas(5, 1, 3, 3, 1);
PatchAtlas PatchAtlas::angularPressed = PatchAtlas(9, 1, 3, 3, 1);

PatchAtlas PatchAtlas::roundedIdle = PatchAtlas(13, 1, 5, 5, 2);
PatchAtlas PatchAtlas::roundedHover = PatchAtlas(19, 1, 5, 5, 2);
PatchAtlas PatchAtlas::roundedPressed = PatchAtlas(25, 1, 5, 5, 2);

PatchAtlas PatchAtlas::curvedIdle = PatchAtlas(31, 1, 9, 9, 4);
PatchAtlas PatchAtlas::curvedHover = PatchAtlas(41, 1, 9, 9, 4);
PatchAtlas PatchAtlas::curvedPressed = PatchAtlas(51, 1, 9, 9, 4);


PatchAtlas::PatchAtlas(){
	area = sf::IntRect(0, 0, 0, 0);
	borderWidth = 0;
}

PatchAtlas::PatchAtlas(sf::IntRect area, int borderWidth){
	this->area = area;
	this->borderWidth = borderWidth;
}

PatchAtlas::PatchAtlas(int x, int y, int width, int height, int borderWidth) {
	area = sf::IntRect(x, y, width, height);
	this->borderWidth = borderWidth;
}

PatchAtlas::~PatchAtlas() {
}
