#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow & window)
	: window_(window)
	, worldView_(window.getDefaultView())
	, textures_()
	, sceneGraph_()
	, sceneLayers_()
	, worldBounds_(0.0f, 0.0f, 6000.0f, worldView_.getSize().y)
	, spawnPosition_(0.0f, worldView_.getSize().y / 2.0f)
	, scrollSpeed_(0.0f)
	, player_(nullptr)
{
	LoadTextures();
	BuildScene();

	worldView_.setCenter(spawnPosition_);
}

void World::Update(sf::Time delta)
{
	worldView_.move(scrollSpeed_ * delta.asSeconds(), 0.0f);

	sf::Vector2f position = player_->getPosition();
	sf::Vector2f velocity = player_->getVelocity();

	if (position.y <= worldBounds_.top || position.y >= worldBounds_.top + worldBounds_.height)
	{
		velocity.y *= -1;
		player_->setVelocity(velocity);
	}

	sceneGraph_.Update(delta);
}

void World::Draw()
{
	window_.setView(worldView_);
	window_.draw(sceneGraph_);
}

void World::LoadTextures()
{
	textures_.Load(Textures::Eagle,  "assets/gfx/blueblock.png");
	textures_.Load(Textures::Raptor, "assets/gfx/redblock.png");
	textures_.Load(Textures::Desert, "assets/gfx/background.png");
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

	// Prepare the tiled background
	sf::Texture & texture = textures_.get(Textures::Desert);
	sf::IntRect textureRect(worldBounds_);
	texture.setRepeated(true);

	// Add background sprite to the scene
	SpriteNode::Ptr backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds_.left - worldView_.getSize().x / 2.0f, worldBounds_.top);
	sceneLayers_[Background]->AttachChild(std::move(backgroundSprite));

	// Add player sprite to the scene
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, textures_));
	player_ = leader.get();
	player_->setPosition(spawnPosition_);
	player_->setVelocity(scrollSpeed_, 100.0f);
	sceneLayers_[Air]->AttachChild(std::move(leader));

	// Add escort sprite to the scene
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, textures_));
	leftEscort->setPosition(-50.0f, -50.0f);
	player_->AttachChild(std::move(leftEscort));

	// Add escort sprite to the scene
	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, textures_));
	rightEscort->setPosition(-50.0f, 50.0f);
	player_->AttachChild(std::move(rightEscort));
}
