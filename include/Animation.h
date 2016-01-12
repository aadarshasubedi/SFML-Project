#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Animation : public sf::Drawable, public sf::Transformable
{
	public:
						Animation();
	explicit			Animation(const sf::Texture & texture);

	void				setTexture(const sf::Texture & texture);
	void				setFrameSize(sf::Vector2i frameSize);
	void				setNumFrames(std::size_t numFrames);
	void				setDuration(sf::Time duration);
	void				Looping(bool flag);

	const sf::Texture *	getTexture() const;
	sf::Vector2i		getFrameSize() const;
	std::size_t			getNumFrames() const;
	sf::Time			getDuration() const;
	bool				Looping() const;
	sf::FloatRect		getLocalBounds() const;
	sf::FloatRect		getGlobalBounds() const;

	void				Restart();
	bool				Finished() const;


	void				Update(sf::Time delta);

	private:
	void				draw(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
	sf::Sprite			sprite_;
	sf::Vector2i		frameSize_;
	std::size_t			numFrames_;
	std::size_t			currentFrame_;
	sf::Time			duration_;
	sf::Time			elapsed_;
	bool				loop_;
};