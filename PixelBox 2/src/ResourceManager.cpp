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
		std::cout << "Failed to load res/textures/gui_texture.png" << std::endl;
		return false;
	}
	if (!resourceManager.m_logoTexture.loadFromFile("res/textures/logo.png")) {
		std::cout << "Failed to load res/textures/logo.png" << std::endl;
		return false;
	}

	// Load font
	if (!resourceManager.m_pixelfont.loadFromFile("res/fonts/pixelfont.ttf")) {
		std::cout << "Failed to load res/fonts/pixelfont.ttf" << std::endl;
		return false;
	}

	// Load sounds


	//load rulesets
	for (Ruleset* ruleset : resourceManager.m_rulesets) {
		delete ruleset;
	}
	resourceManager.m_rulesets.clear();
	resourceManager.m_rulesets.push_back(new CircuitGridRuleset());
	resourceManager.m_rulesets.push_back(new PixelBoxRuleset());
	//TODO: load custom rulesets


	//load shaders
	if (!resourceManager.m_pixelShader.loadFromFile("res/shader/pixelShader.frag", sf::Shader::Fragment)) {
		std::cout << "Failed to load res/shader/pixelShader.frag" << std::endl;
		return false;
	}
	
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

sf::Shader* ResourceManager::getPixelShader() {
	return &ResourceManager::instance().m_pixelShader;
}

Ruleset* ResourceManager::getRuleset(uint64_t id) {
	for (Ruleset* ruleset : ResourceManager::instance().m_rulesets) {
		if (ruleset->getID() == id)
			return ruleset;
	}

	return nullptr;
}

const std::vector<Ruleset*>& ResourceManager::getRulesetList() {
	return ResourceManager::instance().m_rulesets;
}