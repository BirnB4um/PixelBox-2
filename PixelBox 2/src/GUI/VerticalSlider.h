#pragma once
#include "Slider.h"

class VerticalSlider : public Slider
{

public:
	VerticalSlider();
	~VerticalSlider();

protected:

	void updateSize() override;
	void updateNobPosition() override;
	void updateValue() override;
};

