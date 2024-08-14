#pragma once

#include "GuiContainer.h"
#include "NinePatch.h"

class Panel : public GuiContainer
{
public:
	Panel();
	~Panel();

	bool handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;
	void reloadResources() override;


protected:

	NinePatch m_ninePatch;
	sf::View m_panelView;
	sf::FloatRect m_panelViewRect;

	void updateBounds() override;
	void updateMouseOffset() override;

	//update the view based on the view of the parent
	void updateView(const sf::View& previousView);

	//update everything that is dependent on the viewRect
	virtual void updateViewRect();
	

};

