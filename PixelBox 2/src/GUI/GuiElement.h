#pragma once

#include <SFML/Graphics.hpp>

class GuiContainer;

class GuiElement
{
public:
	static void setGuiScale(float scale);
	static float getGuiScale();

	GuiElement();
	~GuiElement();

	//returns true, if the event is captured
	virtual bool handleEvent(sf::Event& sfEvent);
	virtual void update(float dt);
	virtual void render(sf::RenderTarget& window);
	virtual void reloadResources();

	// setter
	virtual void setPosition(float x, float y);
	virtual void setPosition(sf::Vector2f position);
	virtual void setSize(float width, float height);
	virtual void setSize(sf::Vector2f size);
	virtual void setBounds(float x, float y, float width, float height);
	virtual void setBounds(sf::FloatRect bounds);
	virtual void setBorderWidth(float width);
	virtual void setParent(GuiContainer* parent);

	// getter
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getSize();
	virtual sf::FloatRect getBounds();
	virtual float getBorderWidth();
	GuiContainer* getParent();

protected:
	static float m_guiScale;

	GuiContainer* m_parentGui;

	sf::FloatRect m_bounds;
	float m_borderWidth;

	virtual void updateBounds();

};
