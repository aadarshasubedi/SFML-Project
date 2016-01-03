#include "SceneNode.h"

#include "Command.h"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() :
	parent_(nullptr)
{
}

void SceneNode::AttachChild(SceneNode::Ptr child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(children_.begin(), children_.end(), [&node](SceneNode::Ptr& p) -> bool { return p.get() == &node; });
	assert(found != children_.end());

	SceneNode::Ptr child = std::move(*found);

	child->parent_ = nullptr;
	children_.erase(found);
	return child;
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Implemented by sub-classes
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto & child : children_)
	{
		child->draw(target, states);
	}
}

void SceneNode::Update(sf::Time delta)
{
	UpdateCurrent(delta);
	UpdateChildren(delta);
}

void SceneNode::UpdateCurrent(sf::Time delta)
{
	// Implemented by sub-classes
}

void SceneNode::UpdateChildren(sf::Time delta)
{
	for (auto & child : children_)
	{
		child->Update(delta);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();;
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode * node = this; node != nullptr; node = node->parent_)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

void SceneNode::onCommand(const Command & command, sf::Time delta)
{
	if (command.category & getCategory())
	{
		command.action(*this, delta);
	}

	for (auto & child : children_)
	{
		child->onCommand(command, delta);
	}
}

uint32_t SceneNode::getCategory() const
{
	return Category::Scene;
}
