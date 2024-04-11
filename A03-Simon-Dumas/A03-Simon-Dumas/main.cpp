#include <iostream>
#include "Player.h"

sf::Clock gameClock;
sf::Time totalTime;
sf::Time prevTotalTime;

Player* player;

void Init(sf::RenderWindow& window) {
    // load textures
    sf::Texture* playerTexture = new sf::Texture();
    playerTexture->loadFromFile("Assets/slime_with_helmet.png");

    sf::Texture* healthTexture = new sf::Texture();
    healthTexture->loadFromFile("Assets/heart.png");

    //create player
    player = new Player(playerTexture, healthTexture, sf::Vector2f(window.getSize().x, window.getSize().y));

    //initial values for clock and time
    gameClock.restart();
    totalTime = gameClock.getElapsedTime();
}

void Update(sf::RenderWindow& window) {
    totalTime = gameClock.getElapsedTime();
    float deltaTime = totalTime.asSeconds() - prevTotalTime.asSeconds();

    if (player != NULL)
        player->Update(window, deltaTime);
}

void Render(sf::RenderWindow& window) {
    if (player != NULL)
        player->Draw(window);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "IGME209-A03");

    Init(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255)); // clear the window with color(255,255,255)

        Update(window);
        Render(window);

        window.display(); // display the window
    }

    return 0;
}