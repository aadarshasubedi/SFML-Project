#pragma once

namespace sf
{
	class Font; class Shader; class SoundBuffer; class Texture;
}

namespace Textures
{
	enum ID
	{
		Eagle, Raptor
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

template <typename Resource, typename Identifier> class ResourceManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::Shader, Shaders::ID> ShaderManager;
typedef ResourceManager<sf::SoundBuffer, SoundEffect::ID> SoundManager;
typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;