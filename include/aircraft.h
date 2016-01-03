#pragma once

#include "Entity.h"
#include "ResourceTypes.h"

#include <SFML/Graphics/Sprite.hpp>

class Aircraft : public Entity
{
	public:
	enum Type { Player, Enemy };

	public:
	explicit		Aircraft(Type type, const TextureManager & textures);
	virtual void	drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual uint32_t getCategory() const;

	private:
	Type			type_;
	sf::Sprite		sprite_;
};