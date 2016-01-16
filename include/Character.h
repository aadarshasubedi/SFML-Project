#pragma once

#include "Entity.h"
#include "ResourceTypes.h"

#include <SFML/Graphics/Sprite.hpp>

class Character : public Entity
{
	public:
	explicit		Character(const TextureManager & textures);
	virtual void	drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
	sf::Sprite		sprite_;
};