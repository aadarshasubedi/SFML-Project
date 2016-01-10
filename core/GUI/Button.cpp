#include "Button.h"
#include "Utils.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GUI::Button::Button(const FontManager & fonts, const TextureManager & textures)
	: callback_()
	, defaultTexture_(textures.get(Textures::ButtonDefault))
	, selectedTexture_(textures.get(Textures::ButtonSelected))
	, pressedTexture_(textures.get(Textures::ButtonPressed))
	, sprite_()
	, text_("", fonts.get(Fonts::Default), 16)
	, toggle_(false)
{
	sprite_.setTexture(defaultTexture_);

	sf::FloatRect bounds = sprite_.getLocalBounds();
	text_.setPosition(bounds.width / 2.0f, bounds.height / 2.0f);
}

void GUI::Button::setCallback(Callback callback)
{
	callback_ = std::move(callback);
}

void GUI::Button::setText(const std::string & text)
{
	text_.setString(text);
	CenterOrigin(text_);
}

void GUI::Button::setToggle(bool flag)
{
	toggle_ = flag;
}

bool GUI::Button::Selectable() const
{
	return true;
}

void GUI::Button::Select()
{
	Component::Select();
	sprite_.setTexture(selectedTexture_);
}

void GUI::Button::DeSelect()
{
	Component::DeSelect();
	sprite_.setTexture(defaultTexture_);
}

void GUI::Button::Activate()
{
	Component::Activate();

	if (toggle_)
	{
		sprite_.setTexture(pressedTexture_);
	}
	if (callback_)
	{
		callback_();
	}
	if (!toggle_)
	{
		DeActivate();
	}
}

void GUI::Button::DeActivate()
{
	Component::DeActivate();

	if (toggle_)
	{
		if (Selected())
		{
			sprite_.setTexture(selectedTexture_);
		}
		else
		{
			sprite_.setTexture(defaultTexture_);
		}
	}
}

void GUI::Button::HandleEvent(const sf::Event & event)
{
}

void GUI::Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	target.draw(text_, states);
}
