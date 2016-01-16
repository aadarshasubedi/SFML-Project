#include "Character.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Character::Character(const TextureManager & textures)
	: Entity(10)
	, sprite_(textures.get(Textures::Player1))
{
	auto bounds = sprite_.getLocalBounds();
	sprite_.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Character::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
