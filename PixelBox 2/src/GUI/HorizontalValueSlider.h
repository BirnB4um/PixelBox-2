#pragma once

#include "ValueSlider.h"

class HorizontalValueSlider : public ValueSlider
{
public:
	HorizontalValueSlider();
	~HorizontalValueSlider();


protected:

	void updateNobPosition() override;
	void updateValue() override;
	void updateZeroLine() override;


};

