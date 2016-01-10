#include "Container.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

GUI::Container::Container()
	: children_()
	, selectedChild_(-1)
{ }

void GUI::Container::Pack(Component::Ptr component)
{
	children_.push_back(component);
	if (!Selection() && component->Selectable())
	{
		Select(children_.size() - 1);
	}
}

bool GUI::Container::Selectable() const
{
	return false;
}

void GUI::Container::HandleEvent(const sf::Event & event)
{
	if (Selection() && children_[selectedChild_]->Active())
	{
		children_[selectedChild_]->HandleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			SelectPrev();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			SelectNext();
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			if (Selection())
			{
				children_[selectedChild_]->Activate();
			}
		}
	}
}

void GUI::Container::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (const auto & child : children_)
	{
		target.draw(*child, states);
	}
}

bool GUI::Container::Selection() const
{
	return selectedChild_ >= 0;
}

void GUI::Container::Select(std::size_t index)
{
	if (children_[index]->Selectable())
	{
		if (Selection())
		{
			children_[selectedChild_]->DeSelect();
		}
		children_[index]->Select();
		selectedChild_ = index;
	}
}

void GUI::Container::SelectNext()
{
	if (!Selection())
	{
		return;
	}

	int next = selectedChild_;
	do
	{
		next = (next + 1) % children_.size();
	} while (!children_[next] - Selectable());

	Select(next);
}

void GUI::Container::SelectPrev()
{
	if (!Selection())
	{
		return;
	}

	int prev = selectedChild_;
	do
	{
		prev = (prev + children_.size() - 1) % children_.size();
	} while (!children_[prev] - Selectable());

	Select(prev);
}
