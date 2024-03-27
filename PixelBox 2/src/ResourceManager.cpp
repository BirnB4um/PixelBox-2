#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}


bool ResourceManager::loadResources()
{
	bool success = true;

	// Load textures
	if (!m_guiTexture.loadFromFile("res/textures/gui_texture.png")) {
		std::cout << "Failed to load gui_texture.png" << std::endl;
		success = false;
	}

	// Load font
	if (!m_pixelfont.loadFromFile("res/fonts/pixelfont.ttf")) {
		std::cout << "Failed to load pixelfont.ttf" << std::endl;
		success = false;
	}
	
	return success;
}

sf::Texture* ResourceManager::getGuiTexture() {
	return &m_guiTexture;
}

sf::Font& ResourceManager::getPixelFont() {
	return m_pixelfont;
}