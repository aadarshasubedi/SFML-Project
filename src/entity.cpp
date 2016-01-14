#include "Entity.h"

Entity::Entity(int life)
	: velocity_()
	, life_(life)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

void Entity::Accelerate(sf::Vector2f velocity)
{
	velocity_ += velocity;
}

void Entity::Accelerate(float vx, float vy)
{
	velocity_.x += vx;
	velocity_.y += vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity_;
}

void Entity::setLife(int life)
{
	life_ = life;
}

int Entity::getLife() const
{
	return life_;
}

void Entity::Kill()
{
	life_ = 0;
}

bool Entity::Dead() const
{
	return life_ == 0;
}

void Entity::UpdateCurrent(sf::Time delta)
{
	sf::Transformable::move(velocity_ * delta.asSeconds());
}
