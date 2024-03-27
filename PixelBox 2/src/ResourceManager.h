#pragma once

#include <cstdarg>
#include <iostream>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	bool loadResources();
	sf::Texture* getGuiTexture();
	sf::Font& getPixelFont();

private:
	sf::Texture m_guiTexture;
	sf::Font m_pixelfont;
};

