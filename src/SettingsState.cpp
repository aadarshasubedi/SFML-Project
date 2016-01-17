#include "SettingsState.h"
#include "ResourceManager.h"
#include "Utils.h"

#include <SFML/Graphics/RenderWindow.hpp>

SettingsState::SettingsState(StateMachine & states, Context context)
	: State(states, context)
	, GUIcontainer_()
{
	background_.setTexture(context.textures_->get(Textures::Title));

	AddButtonLabel(Player::MoveLeft, 130.0f, "Move Left", context);
	AddButtonLabel(Player::MoveRight, 190.0f, "Move Right", context);
	AddButtonLabel(Player::MoveUp, 250.0f, "Move Up", context);
	AddButtonLabel(Player::MoveDown, 310.0f, "Move Down", context);

	UpdateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	backButton->setPosition(550.0f, 80.0f);
	backButton->setText("BACK");
	backButton->setCallback([this]()
	{
		RequestPop();
	});

	GUIcontainer_.Pack(backButton);
}

void SettingsState::Draw()
{
	sf::RenderWindow & window = *getContext().window_;

	window.draw(background_);
	window.draw(GUIcontainer_);
}

bool SettingsState::Update(sf::Time delta)
{
	return true;
}

bool SettingsState::HandleEvent(const sf::Event & event)
{
	bool isKeyBinding = false;

	for (unsigned int action = 0; action < Player::ActionCount; ++action)
	{
		if (bindingButtons_[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player_->AssignKey(static_cast<Player::Action>(action), event.key.code);
				bindingButtons_[action]->DeActivate();
			}
			break;
		}
	}

	if (isKeyBinding)
	{
		UpdateLabels();
	}
	else
	{
		GUIcontainer_.HandleEvent(event);
	}

	return false;
}

void SettingsState::UpdateLabels()
{
	Player & player = *getContext().player_;

	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{

		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(action));
		bindingLabels_[action]->setText(toString(key));

	}
}

void SettingsState::AddButtonLabel(Player::Action action, float y, const std::string & text, Context context)
{
	bindingButtons_[action] = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
	bindingButtons_[action]->setPosition(250.0f, y + 5.0f);
	bindingButtons_[action]->setText(text);
	bindingButtons_[action]->setToggle(true);

	bindingLabels_[action] = std::make_shared<GUI::Label>("", *context.fonts_);
	bindingLabels_[action]->setPosition(bindingButtons_[action]->getPosition() + sf::Vector2f(210.0f, 20.0f));

	GUIcontainer_.Pack(bindingButtons_[action]);
	GUIcontainer_.Pack(bindingLabels_[action]);
}
