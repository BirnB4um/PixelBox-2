#pragma once
#include "Ruleset.h"

class PixelBoxRuleset : public Ruleset
{
public:

	PixelBoxRuleset();
	~PixelBoxRuleset();

	void updateAllPixels(World* world) override;
	const bool updatePixel(size_t& index) const override;
	void addSurrondingPixels(size_t& index) const override;
};

