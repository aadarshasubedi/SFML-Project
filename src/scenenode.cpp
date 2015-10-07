#include "scenenode.h"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() :
	parent_(nullptr)
{
}

void SceneNode::AttachChild(pSceneNode child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

SceneNode::pSceneNode SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(children_.begin(), children_.end(), [&] (pSceneNode& p) -> bool { return p.get() == &node; });
	assert(found != children_.end());
	pSceneNode result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}
