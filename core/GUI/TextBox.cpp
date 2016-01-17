#include "TextBox.h"

GUI::TextBox::TextBox(const FontManager & fonts, const TextureManager & textures)
	: children_()
	, selectedChild_(-1)
	, sprite_(textures.get(Textures::None))
	, text_("", fonts.get(Fonts::Default), 16)
{ }
