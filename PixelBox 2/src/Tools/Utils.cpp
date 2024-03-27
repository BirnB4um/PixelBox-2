#include "Utils.h"


float Utils::constrain(float x, float min, float max) {
	return x < min ? min : x > max ? max : x;
}

bool Utils::rectContainsPoint(float pointX, float pointY, float rectX, float rectY, float rectWidth, float rectHeight) {
	return pointX >= rectX && pointX <= rectX + rectWidth && pointY >= rectY && pointY <= rectY + rectHeight;
}

void Utils::log(std::string logText) {

}