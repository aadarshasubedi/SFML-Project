#pragma once

namespace Textures
{
	enum ID
	{
		Title, Player, Bird, Background,
		ButtonDefault, ButtonSelected, ButtonPressed
	};
}

namespace Shaders
{
	enum ID
	{

	};
}

namespace Fonts
{
	enum ID
	{
		Default
	};
}

namespace SoundEffect
{
	enum ID
	{

	};
}

namespace Music
{
	enum ID
	{

	};
}

namespace sf
{
	class Font; class Shader; class SoundBuffer; class Texture;
}

template <typename Resource, typename Identifier> class ResourceManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::Shader, Shaders::ID> ShaderManager;
typedef ResourceManager<sf::SoundBuffer, SoundEffect::ID> SoundManager;
typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;