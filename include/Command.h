#pragma once

#include "Category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
	Command() : action(), category(Category::None) {}

	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};

// DerivedAction prevent us to downcast each time we call a node (?)
template <typename Object, typename Function>
std::function<void(SceneNode&, sf::Time)> DerivedAction(Function fct)
{
	return [=](SceneNode & node, sf::Time dt)
	{
		assert(dynamic_cast<Object*>(&node) != nullptr);
		fct(static_cast<Object&>(node), dt);
	};
}