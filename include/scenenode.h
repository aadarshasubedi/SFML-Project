#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
	SceneNode();

	/// <summary>
	/// Attach a child to the SceneNode
	/// </summary>
	/// <param name="child"></param>
	/// <returns>void</returns>
	void AttachChild(std::unique_ptr<SceneNode> child);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="node"></param>
	/// <returns></returns>
	std::unique_ptr<SceneNode> DetachChild(const SceneNode& node);

	private:
	
	/// <summary>
	/// 
	/// </summary>
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const; // inherited from sf::Drawable

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	private:
	std::vector<std::unique_ptr<SceneNode>> children_;
	SceneNode* parent_;
};