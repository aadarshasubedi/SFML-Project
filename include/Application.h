#pragma once

#include "Player.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "StateMachine.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class Application
{
	public:
						Application();
	void				Run();

	private:
	void				ProcessInput();
	void				Update(sf::Time delta);
	void				Render();
	void				RegisterStates();

	private:
	sf::RenderWindow	window_;
	TextureManager		textures_;
	FontManager			fonts_;
	Player				player_;
	StateMachine		states_;
	
	private:
	void				UpdateStatistics(sf::Time delta);
	sf::Text			statisticsText_;
	sf::Time			statisticsUpdateTime_;
	std::size_t			statisticsNumFrames_;
};