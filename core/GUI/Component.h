#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>

namespace sf
{
	class Event;
}

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
		public:
		typedef std::shared_ptr<Component> Ptr;

						Component();
		virtual			~Component();

		virtual bool	Selectable() const = 0;
		virtual bool	Selected() const;
		virtual void	Select();
		virtual void	DeSelect();

		virtual bool	Active() const;
		virtual void	Activate();
		virtual void	DeActivate();

		virtual void	HandleEvent(const sf::Event & event) = 0;

		private:
		bool			selected_;
		bool			active_;
	};
}