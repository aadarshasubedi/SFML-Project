#pragma once

#include "Component.h"

#include <vector>

namespace GUI
{
	class Container : public Component
	{
		public:
		typedef std::shared_ptr<Container> Ptr;

									Container();
			
		void						Pack(Component::Ptr component);
		virtual bool				Selectable() const;
		virtual void				HandleEvent(const sf::Event & event);

		private:
		virtual void				draw(sf::RenderTarget & target, sf::RenderStates states) const;
		bool						Selection() const;
		void						Select(std::size_t index);
		void						SelectNext();
		void						SelectPrev();

		private:
		std::vector<Component::Ptr>	children_;
		int							selectedChild_;
	};
}