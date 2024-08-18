#pragma once
#include "ValueSlider.h"

class VerticalValueSlider : public ValueSlider
{
public:
	VerticalValueSlider();
	~VerticalValueSlider();

protected:

	void updateNobPosition() override;
	void updateValue() override;
	void updateZeroLine() override;
};

