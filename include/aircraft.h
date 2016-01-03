#pragma once

#include "entity.h"
#include "ResourceTypes.h"

class Aircraft : public Entity
{
	public:
	enum Type { Eagle, Raptor };

	public:
	explicit Aircraft(Type type, const TextureManager & textures);
	virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
	Type type_;
	sf::Sprite sprite_;
};