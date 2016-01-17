#pragma once

#include "Entity.h"
#include "ResourceTypes.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Sprite.hpp>

class Character : public Entity
{
	public:
	enum Type
	{
		Player1, Player2, Bird, TypeCount
	};

	public:
	explicit				Character(Type type, const TextureManager & textures);
	
	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			Freeable() const;
	float					getMaxSpeed() const;

	void					increaseFireRate();
	void					Fire();
	
	private:
	virtual void			drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void			UpdateCurrent(sf::Time delta, CommandQueue & commands);
	void					CreateBullets(SceneNode & node, const TextureManager & textures) const;

	private:
	Type			type_;
	sf::Sprite		sprite_;
	Command			fireCommand_;
	sf::Time		fireCountDown_;
	bool			firing_;
	bool			freeable_;

	int				fireRateLevel_;

	//TextNode *		healthDisplay_;
};