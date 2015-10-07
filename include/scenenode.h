#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
	typedef std::unique_ptr<SceneNode> pSceneNode;

	public:
	SceneNode();

	void AttachChild(pSceneNode);
	pSceneNode DetachChild(const SceneNode&);

	private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const; // inherited from sf::Drawable
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	private:
	std::vector<pSceneNode> children_;
	SceneNode* parent_;
};