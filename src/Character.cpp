#include "Character.h"
#include "Data.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<CharacterData> table = InitCharacterData();
}

Character::Character(Type type, const TextureManager & textures)
	: Entity(table[type].life)
	, type_(type)
	, sprite_(textures.get(table[type].texture))
	, fireCommand_()
	, fireCountDown_(sf::Time::Zero)
	, firing_(false)
	, freeable_(false)
	, fireRateLevel_(1)
{
	CenterOrigin(sprite_);

	fireCommand_.category = Category::Scene;
	fireCommand_.action = [this, &textures](SceneNode & node, sf::Time)
	{
		CreateBullets(node, textures);
	};
}

unsigned int Character::getCategory() const
{
	if (type_ == Type::Player1)
		return Category::Player;
	if (type_ == Type::Player2)
		return Category::Player;
	if (type_ == Type::Bird)
		return Category::Enemy;
}

sf::FloatRect Character::getBoundingRect() const
{
	return sf::FloatRect();
}

bool Character::Freeable() const
{
	return freeable_;
}

float Character::getMaxSpeed() const
{
	return 0.0f;
}

void Character::increaseFireRate()
{
}

void Character::Fire()
{
}

void Character::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void Character::UpdateCurrent(sf::Time delta, CommandQueue & commands)
{
	if (Dead())
	{
		freeable_ = true;
		return;
	}
}

void Character::CreateBullets(SceneNode & node, const TextureManager & textures) const
{
}