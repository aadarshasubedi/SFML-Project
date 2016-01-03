#include "Entity.h"

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

void Entity::UpdateCurrent(sf::Time delta)
{
	sf::Transformable::move(velocity_ * delta.asSeconds());
}
