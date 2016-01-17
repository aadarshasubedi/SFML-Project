#include "Data.h"
#include "Character.h"

std::vector<CharacterData> InitCharacterData()
{
	std::vector<CharacterData> data(Character::TypeCount);

	data[Character::Player1].life			= 0;
	data[Character::Player1].speed			= 0.0f;
	data[Character::Player1].texture		= Textures::Player1;
	//data[Character::Player1].frame		= ;
	data[Character::Player1].fireRate		= sf::milliseconds(500);
	//data[Character::Player1].directions	= ;
	data[Character::Player1].hasAnimation	= true;

	data[Character::Player2].life			= 0;
	data[Character::Player2].speed			= 0.0f;
	data[Character::Player2].texture		= Textures::Player2;
	//data[Character::Player2].frame		= ;
	data[Character::Player2].fireRate		= sf::milliseconds(500);
	//data[Character::Player2].directions	= ;
	data[Character::Player2].hasAnimation	= true;

	data[Character::Bird].life				= 1;
	data[Character::Bird].speed				= 100.0f;
	data[Character::Bird].texture			= Textures::Bird;
	//data[Character::Bird].frame			= ;
	data[Character::Bird].fireRate			= sf::Time::Zero;
	//data[Character::Bird].directions		= ;
	data[Character::Bird].hasAnimation		= true;

	return data;
}

std::vector<ProjectileData> InitProjectileData()
{
	return std::vector<ProjectileData>();
}

std::vector<PickupData> InitPickupData()
{
	return std::vector<PickupData>();
}

std::vector<ParticleData> InitParticleData()
{
	return std::vector<ParticleData>();
}
