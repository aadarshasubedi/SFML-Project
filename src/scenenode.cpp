#include "scenenode.h"

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
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto & child : children_)
	{
		child->draw(target, states);
	}
}
