#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

#include <SFML/Graphics/Text.hpp>

namespace GUI
{
	class Label : public Component
	{
		public:
		typedef std::shared_ptr<Label> Ptr;

		Label(const std::string & text, const FontManager & fonts);
		virtual bool	isSelectable() const;
		virtual void	HandleEvent(const sf::Event & event);

		void			setText(const std::string & text);
		void			setTextColor(sf::Color color);

		private:
		void			draw(sf::RenderTarget & target, sf::RenderStates states) const ;

		private:
		sf::Text		text_;
	};
}