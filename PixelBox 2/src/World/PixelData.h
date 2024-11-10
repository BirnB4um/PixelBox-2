#pragma once
#include <cstdint>

class PixelData {

public:
	PixelData() : id(0), data1(0), data2(0), data3(0) {}
	PixelData(uint8_t id, uint8_t data1, uint8_t data2, uint8_t data3) : id(id), data1(data1), data2(data2), data3(data3) {}
	PixelData(uint32_t data) {
		fromUInt32(data);
	}

	uint8_t id;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;

	inline void set(uint8_t id_, uint8_t data1_, uint8_t data2_, uint8_t data3_) {
		id = id_;
		data1 = data1_;
		data2 = data2_;
		data3 = data3_;
	}

	inline uint32_t toUInt32() const {
		uint32_t x = 0;
		uint8_t* xPtr = reinterpret_cast<uint8_t*>(&x);
		xPtr[0] = id;
		xPtr[1] = data1;
		xPtr[2] = data2;
		xPtr[3] = data3;
		return x;
	}

	inline void fromUInt32(uint32_t x) {
		uint8_t* xPtr = reinterpret_cast<uint8_t*>(&x);
		id = xPtr[0];
		data1 = xPtr[1];
		data2 = xPtr[2];
		data3 = xPtr[3];
	}

	inline bool operator==(const PixelData& other) const {
		return id == other.id && data1 == other.data1 && data2 == other.data2 && data3 == other.data3;
	}

	inline bool operator!=(const PixelData& other) const {
		return id != other.id || data1 != other.data1 || data2 != other.data2 || data3 != other.data3;
	}


};