#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
	typedef std::unique_ptr<SceneNode> Ptr;

	public:
						SceneNode();

	void				AttachChild(Ptr child);
	Ptr					DetachChild(const SceneNode& node);

	void				Update(sf::Time delta);

	sf::Vector2f		getWorldPosition() const;
	sf::Transform		getWorldTransform() const;

	private:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const final; // inherited from sf::Drawable
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void		UpdateCurrent(sf::Time delta);
	void				UpdateChildren(sf::Time delta);

	private:
	std::vector<Ptr>	children_;
	SceneNode*			parent_;
};