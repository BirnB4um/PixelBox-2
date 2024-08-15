#pragma once
#include <vector>

class ByteSet
{
public:
	ByteSet();
	ByteSet(size_t maxSize);
	~ByteSet();

	inline void setMaxSize(size_t maxSize);

	inline void add(size_t item);

	inline bool isSet(size_t item) const;

	inline void clear();

	inline size_t size() const { return items.size(); }

	std::vector<size_t>& getItems() { return items; }

	inline bool* getMap() const { return map; }

	inline void swap(ByteSet& other);


private:
	size_t maxSize;
	bool* map;
	std::vector<size_t> items;

};

