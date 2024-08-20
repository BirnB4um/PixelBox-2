#pragma once

#include "StateSwitch.h"

class SpriteStateSwitch : public StateSwitch
{

public:

	struct State {
		size_t id = 0;
		sf::IntRect area = sf::IntRect(0, 0, 1, 1);
	};

	SpriteStateSwitch();
	~SpriteStateSwitch();

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void addState(State state);
	void clearStates();
	void setState(size_t id) override;
	State getCurrentState();

	void setSpritePadding(float padding);
	inline float getSpritePadding() { return m_spritePadding; }



protected:

	bool m_drawSprite;
	sf::Sprite m_sprite;
	float m_spritePadding;

	std::vector<State> m_states;

	void updateBounds() override;
	void incrementState() override;

};

