#pragma once
#include <vector>
#include <cassert>

class ByteSet
{
public:

	ByteSet() {
		setMaxSize(1024);
	}

	ByteSet(size_t maxSize) {
		setMaxSize(maxSize);
	}


	~ByteSet() {
		delete[] map;
	}

	inline void setMaxSize(size_t maxSize) {
		this->maxSize = maxSize;
		delete[] map;
		map = new bool[maxSize];
		clear();
		items.reserve(maxSize);
	}

	inline size_t getMaxSize() const { 
		return maxSize;
	}

	inline void add(size_t item) {
		assert(item < maxSize);
		if (!map[item]) {
			map[item] = true;
			items.push_back(item);
		}
	}

	inline bool isSet(size_t item) const {
		assert(item < maxSize);
		return map[item];
	}

	inline void clear() {
		for (size_t item : items) {
			map[item] = false;
		}
		items.clear();
	}

	inline size_t size() const { 
		return items.size();
	}

	std::vector<size_t>& getItems() {
		return items;
	}

	inline bool* getMap() const {
		return map;
	}

	inline void swap(ByteSet& other) {
		std::swap(maxSize, other.maxSize);
		std::swap(map, other.map);
		std::swap(items, other.items);
	}


private:
	size_t maxSize;
	bool* map;
	std::vector<size_t> items;

};

