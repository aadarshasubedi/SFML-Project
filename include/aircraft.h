#pragma once

#include "entity.h"

class Aircraft : public Entity
{
	public:
	enum Type { Eagle, Raptor };

	public:
	explicit Aircraft(Type);

	private:
	Type type_;
};