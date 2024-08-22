#pragma once
#include <iostream>
#include "Ruleset.h"

class CircuitGridRuleset : public Ruleset
{

public:
	CircuitGridRuleset();
	~CircuitGridRuleset() override;

	void updateAllPixels(World* world) override;
	const bool updatePixel(size_t& index) const override;
	void addSurrondingPixels(size_t& index) const override;

private:

	void createInventory() override;


};

