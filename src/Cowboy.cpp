#include "Cowboy.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Cowboy::Type type)
{
	switch (type)
	{
		case Cowboy::Player:
			return Textures::Player;
		case Cowboy::Enemy:
			return Textures::Enemy;
	}
	return Textures::Player;
}

Cowboy::Cowboy(Type type, const TextureManager & textures) :
	type_(type), sprite_(textures.get(toTextureID(type)))
{
	auto bounds = sprite_.getLocalBounds();
	sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Cowboy::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

uint32_t Cowboy::getCategory() const
{
	switch (type_)
	{
		case Player:
			return Category::Player;
		default:
			return Category::Enemy;
	}
}
