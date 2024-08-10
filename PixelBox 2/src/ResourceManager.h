#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class ResourceManager
{
public:
	static ResourceManager& instance();

	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;


	static bool loadResources();
	static sf::Texture* getGuiTexture();
	static sf::Texture* getLogoTexture();
	static sf::Font* getPixelFont();

private:
	ResourceManager();

	sf::Texture m_guiTexture;
	sf::Texture m_logoTexture;
	sf::Font m_pixelfont;
};
