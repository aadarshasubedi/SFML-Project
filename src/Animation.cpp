#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation()
	: sprite_()
	, frameSize_()
	, numFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsed_(sf::Time::Zero)
	, loop_(false)
{ }

Animation::Animation(const sf::Texture & texture)
	: sprite_(texture)
	, frameSize_()
	, numFrames_(0)
	, currentFrame_(0)
	, duration_(sf::Time::Zero)
	, elapsed_(sf::Time::Zero)
	, loop_(false)
{ }

void Animation::setTexture(const sf::Texture & texture)
{
	sprite_.setTexture(texture);
}

const sf::Texture * Animation::getTexture() const
{
	return sprite_.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

sf::Vector2i Animation::getFrameSize() const
{
	return frameSize_;
}

void Animation::setNumFrames(std::size_t numFrames)
{
	numFrames_ = numFrames;
}

std::size_t Animation::getNumFrames() const
{
	return numFrames_;
}

void Animation::setDuration(sf::Time duration)
{
	duration_ = duration;
}

sf::Time Animation::getDuration() const
{
	return duration_;
}

void Animation::Looping(bool flag)
{
	loop_ = flag;
}

bool Animation::Looping() const
{
	return loop_;
}

void Animation::Restart()
{
	currentFrame_ = 0;
}

bool Animation::Finished() const
{
	return currentFrame_ >= numFrames_;
}

sf::FloatRect Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::Update(sf::Time delta)
{
	sf::Time timePerFrame = duration_ / static_cast<float>(numFrames_);
	elapsed_ += delta;

	sf::Vector2i textureBounds(sprite_.getTexture()->getSize());
	sf::IntRect  frame = sprite_.getTextureRect();

	if (currentFrame_ == 0)
	{
		frame = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
	}

	while (elapsed_ >= timePerFrame && (currentFrame_ <= numFrames_ || loop_))
	{
		frame.left += frame.width;

		if (frame.left + frame.width > textureBounds.x)
		{
			frame.left = 0;
			frame.top += frame.height;
		}

		elapsed_ -= timePerFrame;
		if (loop_)
		{
			currentFrame_ = (currentFrame_ + 1) % numFrames_;

			if (currentFrame_ == 0)
			{
				frame = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
			}
		}
		else
		{
			++currentFrame_;
		}
	}
	sprite_.setTextureRect(frame);
}

void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}
