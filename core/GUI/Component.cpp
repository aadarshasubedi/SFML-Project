#include "Component.h"

GUI::Component::Component()
	: selected_(false)
	, active_(false)
{ }

GUI::Component::~Component()
{ }

bool GUI::Component::Selected() const
{
	return selected_;
}

void GUI::Component::Select()
{
	selected_ = true;
}

void GUI::Component::DeSelect()
{
	selected_ = false;
}

bool GUI::Component::Active() const
{
	return active_;
}

void GUI::Component::Activate()
{
	active_ = true;
}

void GUI::Component::DeActivate()
{
	active_ = false;
}
