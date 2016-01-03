#include "Aircraft.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
		case Aircraft::Player:
			return Textures::Player;
		case Aircraft::Enemy:
			return Textures::Enemy;
	}
	return Textures::Player;
}

Aircraft::Aircraft(Type type, const TextureManager & textures) :
	type_(type), sprite_(textures.get(toTextureID(type)))
{
	auto bounds = sprite_.getLocalBounds();
	sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

uint32_t Aircraft::getCategory() const
{
	switch (type_)
	{
		case Player:
			return Category::Player;
		default:
			return Category::Enemy;
	}
}
