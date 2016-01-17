#pragma once

#include "Container.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

namespace GUI
{
	class TextBox : public Container
	{
		public:
		typedef std::shared_ptr<TextBox> Ptr;

		TextBox(const FontManager & fonts, const TextureManager & textures);

		private:
		std::vector<Component::Ptr>	children_;
		int							selectedChild_;
		sf::Sprite					sprite_;
		sf::Text					text_;
	};
}