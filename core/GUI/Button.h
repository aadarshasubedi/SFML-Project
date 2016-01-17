#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <functional>

namespace GUI
{
	class Button : public Component
	{
		public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()>	Callback;

		Button(const FontManager & fonts, const TextureManager & textures);

		void					setCallback(Callback callback);
		void					setText(const std::string & text);
		void					setTextColor(sf::Color color);
		void					setToggle(bool flag);

		virtual bool			isSelectable() const;
		virtual void			Select();
		virtual void			DeSelect();
		virtual void			Activate();
		virtual void			DeActivate();

		virtual void			HandleEvent(const sf::Event & event);

		private:
		virtual void			draw(sf::RenderTarget & target, sf::RenderStates states) const;

		private:
		Callback				callback_;
		const sf::Texture &		defaultTexture_;
		const sf::Texture &		selectedTexture_;
		const sf::Texture &		pressedTexture_;
		sf::Sprite				sprite_;
		sf::Text				text_;
		bool					toggle_;
		
	};
}