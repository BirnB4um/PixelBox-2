#pragma once
#include "Panel.h"
#include "HorizontalSlider.h"
#include "VerticalSlider.h"

#include "TextButton.h"


/*

TODO: 
- use view instead of rendering to a rendertexture
- dont show scrollbar if the window covers all content

*/


class ScrollPanel : public Panel
{
public:
	ScrollPanel();
	~ScrollPanel();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;
	void setParent(GuiContainer* parent) override;

	// clear all elements and set their parent to null
	void clearElements() override;
	// Ownership of element retains with the caller
	void addElement(GuiElement* element) override;
	void setScrollable(bool vertical, bool horizontal);
	void setSliderWidth(float width);
	void resetSliders();


private:
	HorizontalSlider m_horizontalSlider;
	VerticalSlider m_verticalSlider;
	bool m_horizontalScrollable, m_verticalScrollable;
	float m_sliderWidth;
	float m_minSliderNobSize;
	float m_elementsBorder;
	sf::FloatRect m_totalRenderSize;

	void updateBounds() override;
	void updateTotalRenderSize();
	void updateSliders();


};

