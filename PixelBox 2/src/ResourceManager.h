#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ruleset/Ruleset.h"
#include "Ruleset/CircuitGridRuleset.h"
#include "Ruleset/PixelBoxRuleset.h"


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
	static sf::Shader* getPixelShader();

	//returns ruleset with given id
	//if no ruleset found returns nullptr
	static Ruleset* getRuleset(uint64_t id);
	static const std::vector<Ruleset*>& getRulesetList();

private:
	ResourceManager();

	sf::Texture m_guiTexture;
	sf::Texture m_logoTexture;

	sf::Font m_pixelfont;
	sf::Shader m_pixelShader;

	std::vector<Ruleset*> m_rulesets;
};
