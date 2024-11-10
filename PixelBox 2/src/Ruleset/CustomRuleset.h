#pragma once
#include "Ruleset.h"

class CustomRuleset : public Ruleset
{
public:
	CustomRuleset();
	~CustomRuleset();

	void updateAllPixels(World* world) override;
	const bool updatePixel(size_t& index) const override;
	void addSurroundingPixels(size_t& index) const override;
};

