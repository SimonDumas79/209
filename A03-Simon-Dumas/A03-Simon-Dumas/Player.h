#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	private:
		sf::Sprite playerSprite;
		sf::Sprite healthSprite;
		sf::Vector2f windowSize;

		int health;
		bool healButtonDown;
		bool attackButtonDown;

	public:
		Player(sf::Texture* playerTexture, sf::Texture* healthTexture, sf::Vector2f windowSize);
		~Player();

		void Update(sf::RenderWindow& window, float deltaTime);
		void Draw(sf::RenderWindow& window);

		void Attack();
		void Heal();
};

