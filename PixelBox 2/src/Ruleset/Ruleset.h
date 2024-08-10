#pragma once

#include <cstdint>

class Ruleset
{
public:
	Ruleset();
	~Ruleset();

	uint64_t getID();

private:
	uint64_t m_id;
};

