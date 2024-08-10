#pragma once
#include "Slider.h"

class VerticalSlider : public Slider
{

public:
	VerticalSlider();
	~VerticalSlider();

protected:

	void updateBounds() override;
	void updateNobPosition() override;
	void updateValue() override;
};

