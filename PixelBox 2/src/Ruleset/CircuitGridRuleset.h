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

	enum Item : uint8_t {
		AIR,
		WIRE,
		OUTPUT,
		BATTERY,
		DELAY,
		BRIDGE,

		LAMP,
		BUTTON,
		SWITCH,

		NOT,
		OR,
		NOR,
		XOR,
		XNOR,
		AND,
		NAND,

		CLOCK,
		DEBUG

	};

	void createInventory() override;


};

