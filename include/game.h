#pragma once

#include <SFML/Graphics.hpp>

class Game
{
	public:
	Game(const Game&) = delete;				// delete the default copy constructor and the
	Game& operator=(const Game&) = delete; //  default assignment operator to make the class non-copyable
	Game();

	void Run(int fps);

	private:
	void ProcessEvents();
	void Update(sf::Time delta);
	void Render();

	private:
	sf::RenderWindow window_;
	sf::Texture texture_;
	sf::Sprite player_;
};