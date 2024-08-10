#pragma once
#include "Slider.h"

class HorizontalSlider : public Slider
{

public:
	HorizontalSlider();
	~HorizontalSlider();

protected:

	void updateBounds() override;
	void updateNobPosition() override;
	void updateValue() override;
};

