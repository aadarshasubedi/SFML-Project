#include "scenenode.h"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() :
	parent_(nullptr)
{
}

void SceneNode::AttachChild(std::unique_ptr<SceneNode> child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(children_.begin(), children_.end(), [&node] (std::unique_ptr<SceneNode>& p) -> bool { return p.get() == &node; });
	assert(found != children_.end());
	std::unique_ptr<SceneNode> result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget &, sf::RenderStates) const
{
}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates) const
{
}
