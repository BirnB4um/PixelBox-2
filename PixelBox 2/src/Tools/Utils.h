#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Utils {

	//Constrain a value between a min and max
	template <typename T>
	inline T constrain(const T& x,const T& min, const T& max) {
		return x < min ? min : x > max ? max : x;
	}

	//returns true if the point is inside the rectangle or on the edge
	inline bool rectContainsPoint(float pointX, float pointY, float rectX, float rectY, float rectWidth, float rectHeight) {
		return pointX >= rectX && pointX <= rectX + rectWidth && pointY >= rectY && pointY <= rectY + rectHeight;
	}

	inline float getLength(const sf::Vector2f& vector) {
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	//Log something to file
	inline void log(std::string logText) {
		//TODO
	}
};