#include "ByteSet.h"
#include <cassert>

ByteSet::ByteSet() {
	setMaxSize(1024);
}

ByteSet::ByteSet(size_t maxSize) {
	setMaxSize(maxSize);
}

ByteSet::~ByteSet() {
	delete[] map;
}

void ByteSet::setMaxSize(size_t maxSize) {
	this->maxSize = maxSize;
	delete[] map;
	map = new bool[maxSize];
	clear();
	items.reserve(maxSize);
}

void ByteSet::add(size_t item) {
	assert(item < maxSize);
	if (!map[item]) {
		map[item] = true;
		items.push_back(item);
	}
}

bool ByteSet::isSet(size_t item) const {
	assert(item < maxSize);
	return map[item];
}

void ByteSet::clear() {
	for (size_t item : items) {
		map[item] = false;
	}
	items.clear();
}

void ByteSet::swap(ByteSet& other) {
	std::swap(maxSize, other.maxSize);
	std::swap(map, other.map);
	std::swap(items, other.items);
}