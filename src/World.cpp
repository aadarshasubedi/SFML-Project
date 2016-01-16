#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow & window)
	: window_(window)
	, worldView_(window.getDefaultView())
	, textures_()
	, sceneGraph_()
	, sceneLayers_()
	, worldBounds_(0.0f, 0.0f, worldView_.getSize().x, worldView_.getSize().y)
	, spawnPosition_(worldView_.getSize().x / 2.0f, worldView_.getSize().y / 2.0f)
	, scrollSpeed_(0.0f)
	, playerCharacter_(nullptr)
{
	LoadTextures();
	BuildScene();
}

void World::Update(sf::Time delta)
{
	worldView_.move(scrollSpeed_ * delta.asSeconds(), 0.0f);
	playerCharacter_->setVelocity(0.0f, 0.0f);

	while (!commandQueue_.Empty())
	{
		sceneGraph_.onCommand(commandQueue_.Pop(), delta);
	}

	// Adapt player velocity in case it goes diagonally
	sf::Vector2f velocity = playerCharacter_->getVelocity();
	if (velocity.x != 0.0f && velocity.y != 0.0f)
		playerCharacter_->setVelocity(velocity / std::sqrtf(2.0f));
	playerCharacter_->Accelerate(scrollSpeed_, 0.0f);

	sceneGraph_.Update(delta);


}

void World::Draw()
{
	window_.setView(worldView_);
	window_.draw(sceneGraph_);
}

CommandQueue & World::getCommandQueue()
{
	return commandQueue_;
}

void World::LoadTextures()
{
	textures_.Load(Textures::Player1, "assets/gfx/player.png");
	textures_.Load(Textures::Background, "assets/gfx/background.png");
}

void World::BuildScene()
{
	// Initialize the layers
	for (int i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers_[i] = layer.get();
		sceneGraph_.AttachChild(std::move(layer));
	}

	// Prepare the background
	sf::Texture & texture = textures_.get(Textures::Background);
	sf::IntRect textureRect(worldBounds_);

	// Add background sprite to the scene
	SpriteNode::Ptr backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
	sceneLayers_[Background]->AttachChild(std::move(backgroundSprite));

	// Add player sprite to the scene
	std::unique_ptr<Character> player(new Character(textures_));
	playerCharacter_ = player.get();
	playerCharacter_->setPosition(spawnPosition_);
	playerCharacter_->setVelocity(scrollSpeed_, 100.0f);
	sceneLayers_[Air]->AttachChild(std::move(player));
}
