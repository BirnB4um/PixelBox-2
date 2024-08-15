#pragma once

#include <string>
#include "../Ruleset/Ruleset.h"

struct WorldMetaData
{
public:
	WorldMetaData();

	std::string worldName;
	unsigned int width, height;
	Ruleset* ruleset;


};

