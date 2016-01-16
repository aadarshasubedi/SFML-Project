#pragma once

#include "ResourceTypes.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

class Character;

struct Direction
{
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{ }

	float						angle;
	float						distance;
};

struct CharacterData
{
	int							life;
	float						speed;
	Textures::ID				texture;
	sf::IntRect					frame;
	sf::Time					fireRate;
	std::vector<Direction>		directions;
	bool						hasAnimation;
};

struct ProjectileData
{
	int							damage;
	float						speed;
	Textures::ID				texture;
	sf::IntRect					frame;
};

struct PickupData
{
	std::function<void(Character&)> action;
	Textures::ID				texture;
	sf::IntRect					frame;
};

struct ParticleData
{
	sf::Color					color;
	sf::Time					lifetime;
};


std::vector<CharacterData>			InitCharacterData();
std::vector<ProjectileData>		InitProjectileData();
std::vector<PickupData>			InitPickupData();
std::vector<ParticleData>		InitParticleData();