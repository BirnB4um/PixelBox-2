#pragma once
#include <vector>
#include <cassert>

class ByteSet
{
public:
	ByteSet() : maxSize(1024), size(0), map(nullptr), items(nullptr) {
		setMaxSize(1024);
	}

	ByteSet(size_t maxSize) : maxSize(maxSize), size(0), map(nullptr), items(nullptr) {
		setMaxSize(maxSize);
	}

	~ByteSet() {
		delete[] map;
		delete[] items;
	}

	// Copy Constructor
	ByteSet(const ByteSet& other) : maxSize(other.maxSize), size(other.size) {
		map = new bool[maxSize];
		items = new size_t[maxSize];
		std::copy(other.map, other.map + maxSize, map);
		std::copy(other.items, other.items + size, items);
	}

	// Copy Assignment Operator
	ByteSet& operator=(const ByteSet& other) {
		if (this != &other) {
			ByteSet temp(other);
			swap(temp);
		}
		return *this;
	}

	// Move Constructor
	ByteSet(ByteSet&& other) noexcept
		: maxSize(other.maxSize), size(other.size), map(other.map), items(other.items) {
		other.maxSize = 0;
		other.size = 0;
		other.map = nullptr;
		other.items = nullptr;
	}

	// Move Assignment Operator
	ByteSet& operator=(ByteSet&& other) noexcept {
		if (this != &other) {
			delete[] map;
			delete[] items;

			maxSize = other.maxSize;
			size = other.size;
			map = other.map;
			items = other.items;

			other.maxSize = 0;
			other.size = 0;
			other.map = nullptr;
			other.items = nullptr;
		}
		return *this;
	}

	// Set maximum size of ByteSet
	inline void setMaxSize(size_t maxSize) {
		if (this->maxSize != maxSize) {
			bool* newMap = new bool[maxSize](); // Allocate and zero initialize
			size_t* newItems = new size_t[maxSize];

			delete[] map;
			delete[] items;

			map = newMap;
			items = newItems;
			this->maxSize = maxSize;
			size = 0;
		}
	}

	inline size_t getMaxSize() const {
		return maxSize;
	}

	// Add item to set
	// Returns true if item was added, false if it was already in the set
	inline bool add(size_t item) {
		assert(item < maxSize);

		// If already set
		if (map[item])
			return false;

		// Set flag
		map[item] = true;

		// Push back item
		items[size++] = item;

		return true;
	}

	inline bool isSet(size_t item) const {
		assert(item < maxSize);
		return map[item];
	}

	// Clear the ByteSet
	inline void clear() {
		for (size_t i = 0; i < size; ++i) {
			map[items[i]] = false;
		}
		size = 0;
	}

	inline size_t getSize() const {
		return size;
	}

	size_t* getItems() {
		return items;
	}

	inline bool* getMap() const {
		return map;
	}

	inline void swap(ByteSet& other) {
		std::swap(maxSize, other.maxSize);
		std::swap(map, other.map);
		std::swap(items, other.items);
		std::swap(size, other.size);
	}


	class iterator {
	public:
		iterator(size_t* ptr) : m_ptr(ptr) {}

		size_t& operator*() const { return *m_ptr; }
		size_t* operator->() { return m_ptr; }

		// Prefix increment
		iterator& operator++() {
			m_ptr++;
			return *this;
		}

		// Postfix increment
		iterator operator++(int) {
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

	private:
		size_t* m_ptr;
	};

	iterator begin() { return iterator(items); }
	iterator end() { return iterator(items + size); }

private:
	size_t maxSize;
	bool* map;
	size_t* items;
	size_t size;
};