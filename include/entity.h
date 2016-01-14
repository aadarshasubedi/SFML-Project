#pragma once

#include "SceneNode.h"

class Entity : public SceneNode
{
	public:
	explicit		Entity(int life);

	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	void			Accelerate(sf::Vector2f velocity);
	void			Accelerate(float vx, float vy);
	sf::Vector2f	getVelocity() const;

	void			setLife(int life);
	int				getLife() const;
	void			Kill();
	bool			Dead() const;


	private:
	virtual void	UpdateCurrent(sf::Time delta);

	private:
	sf::Vector2f	velocity_;
	int				life_;
};