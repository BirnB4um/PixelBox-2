#pragma once

#include "GuiElement.h"

class Panel : public GuiElement
{

public:
	Panel();
	~Panel();

	void handleEvent(sf::Event& sfEvent) override;
	void update(float dt) override;
	void render(sf::RenderTarget& window) override;


private:
	std::vector<GuiElement> m_guiElements;
	int m_positionX, m_positionY, m_width, m_height;
	bool m_active;


};

