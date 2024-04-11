#include "Tank.h"

Tank::Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position)
{
    m_baseSprite.setTexture(*baseTexture_ptr); // assign the base texture to base sprite
    m_turretSprite.setTexture(*turretTexture_ptr); // assign the turretTexture to turret sprite

    // init origin
    m_baseSprite.setOrigin(baseTexture_ptr->getSize().x / 2.0f, baseTexture_ptr->getSize().y / 2.0f);
    m_turretSprite.setOrigin(turretTexture_ptr->getSize().x / 2.0f, turretTexture_ptr->getSize().y / 2.0f);

    // init position
    this->position = position;
    m_baseSprite.setPosition(position);
    m_turretSprite.setPosition(position);

    // init rotation
    m_baseSprite.setRotation(0);
    m_turretSprite.setRotation(0);

    // init scale
    m_baseSprite.setScale(2, 2);
    m_turretSprite.setScale(2, 2);
}

Tank::~Tank()
{
}

void Tank::Render(RenderWindow& window)
{
    window.draw(m_baseSprite);// draw the base sprite
    window.draw(m_turretSprite);// draw the base sprite
}

void Tank::Update(RenderWindow& window, float deltaSeconds)
{  
    float rotation = m_baseSprite.getRotation();

    // update rotation
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        rotation += -m_rotate_speed * deltaSeconds;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        rotation += m_rotate_speed * deltaSeconds;
    }
    m_baseSprite.setRotation(rotation);
    m_turretSprite.setRotation(rotation);

    /*******************/
    // Write your code below
    
    // convert rotation angle to radian and adjust for the coordinate system
    float theta = (rotation - 90) / 180.0f * PI; 

    // 1. Calculate direction vector based on the converted rotation 'theta'
    // Vector2f direction = Vector2f(?, ?);
    
    sf::Vector2f fwd = Vector2f(cos(theta), sin(theta));
    

    // 2. forward/backward movement
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        position += fwd * m_move_speed * deltaSeconds;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        position -= fwd * m_move_speed * deltaSeconds;
    }
    m_baseSprite.setPosition(position);
    m_turretSprite.setPosition(position);
    /*******************/
}