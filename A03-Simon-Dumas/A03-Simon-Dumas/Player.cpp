#include "Player.h"

Player::Player(sf::Texture* playerTexture, 
	sf::Texture* healthTexture, 
	sf::Vector2f windowSize) :
	windowSize(windowSize)
{
	playerSprite.setTexture(*playerTexture);
	playerSprite.scale(sf::Vector2f(15.0f, 15.0f));
	playerSprite.setPosition(sf::Vector2f(windowSize.x / 2.0f - playerTexture->getSize().x/2.5f * playerSprite.getScale().x, windowSize.y / 2));

	healthSprite.setTexture(*healthTexture);
	healthSprite.scale(sf::Vector2f(10.0f, 10.0f));
	
	health = 5;
	healButtonDown = false;
	attackButtonDown = false;
}

Player::~Player()
{

}

void Player::Update(sf::RenderWindow& window, float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!attackButtonDown)
		{
			attackButtonDown = true;
			Attack();
		}
	}
	else
	{
		attackButtonDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (!healButtonDown)
		{
			healButtonDown = true;
			Heal();
		}
	}
	else
	{
		healButtonDown = false;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < health; i++)
	{
		healthSprite.setPosition(sf::Vector2f(windowSize.x / 20.0f + (windowSize.x / 5.0f) * i, windowSize.y / 10.0f));
		window.draw(healthSprite);
	}
	window.draw(playerSprite);
}

void Player::Attack()
{
	if (health > 0)
	{
		health--;
	}
}

void Player::Heal()
{
	if (health < 5)
	{
		health++;
	}
}
