#pragma once

#include "Aircraft.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "SceneNode.h"
#include "SpriteNode.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
	public:
	explicit							World(sf::RenderWindow & window);

	void								Update(sf::Time delta);
	void								Draw();

	private:
	void								LoadTextures();
	void								BuildScene();

	enum Layer { Background, Air, LayerCount };

	private:
	sf::RenderWindow &					window_;
	sf::View							worldView_;
	TextureManager						textures_;

	SceneNode							sceneGraph_;
	std::array<SceneNode*, LayerCount>	sceneLayers_;

	sf::FloatRect						worldBounds_;
	sf::Vector2f						spawnPosition_;
	float								scrollSpeed_;
	Aircraft *							player_;
};