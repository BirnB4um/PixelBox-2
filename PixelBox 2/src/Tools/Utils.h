#pragma once
#include <string>

namespace Utils {

	//Constrain a value between a min and max
	float constrain(float x, float min, float max);

	//returns true if the point is inside the rectangle or on the edge
	bool rectContainsPoint(float pointX, float pointY, float rectX, float rectY, float rectWidth, float rectHeight);

	//Log something to file
	void log(std::string logText);
};