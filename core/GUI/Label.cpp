#include "Label.h"

GUI::Label::Label(const std::string & text, const FontManager & fonts)
	: text_(text, fonts.get(Fonts::Default), 16)
{ }

bool GUI::Label::isSelectable() const
{
	return false;
}

void GUI::Label::HandleEvent(const sf::Event & event)
{ }

void GUI::Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text_, states);
}

void GUI::Label::setText(const std::string & text)
{
	text_.setString(text);
}
