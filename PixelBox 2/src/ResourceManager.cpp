#include "ResourceManager.h"
#include "iostream"


ResourceManager& ResourceManager::instance() {
	static ResourceManager resourceManager;
	return resourceManager;
}

ResourceManager::ResourceManager()
{

}

bool ResourceManager::loadResources()
{
	ResourceManager& resourceManager = instance();

	// Load textures
	if (!resourceManager.m_guiTexture.loadFromFile("res/textures/gui_texture.png")) {
		std::cout << "Failed to load gui_texture.png" << std::endl;
		return false;
	}
	if (!resourceManager.m_logoTexture.loadFromFile("res/textures/logo.png")) {
		std::cout << "Failed to load logo.png" << std::endl;
		return false;
	}

	// Load font
	if (!resourceManager.m_pixelfont.loadFromFile("res/fonts/pixelfont.ttf")) {
		std::cout << "Failed to load pixelfont.ttf" << std::endl;
		return false;
	}

	// Load sounds
	
	return true;
}

sf::Texture* ResourceManager::getGuiTexture() {
	return &ResourceManager::instance().m_guiTexture;
}

sf::Texture* ResourceManager::getLogoTexture() {
	return &ResourceManager::instance().m_logoTexture;
}

sf::Font* ResourceManager::getPixelFont() {
	return &ResourceManager::instance().m_pixelfont;
}
