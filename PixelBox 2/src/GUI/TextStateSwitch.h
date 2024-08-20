#pragma once

#include "StateSwitch.h"

class TextStateSwitch : public StateSwitch
{
public:

	struct State {
		size_t id = 0;
		std::string name = "";
	};

	TextStateSwitch();
	~TextStateSwitch();

	void render(sf::RenderTarget& window) override;
	void reloadResources() override;

	void addState(State state);
	void clearStates();
	void setState(size_t id) override;
	State getCurrentState();

	void setFont(sf::Font& font);
	void setFontSize(int size);


protected:

	sf::Text m_text;

	std::vector<State> m_states;

	void updateBounds() override;
	void incrementState() override;


};

