#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define PI 3.1415926f

using namespace std;
using namespace sf;

class Tank {
private:
	Sprite m_baseSprite;
	Sprite m_turretSprite;

	float m_move_speed = 100.0f;
	float m_rotate_speed = 120.0f;

	sf::Vector2f position;
	
public:
	Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);
};