#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Inimigo com Desvio de Golpe");

    sf::CircleShape player(50.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(100, 300);

    sf::CircleShape enemy(30.f);
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(600, 300);

    float playerSpeed = 5.0f;
    float enemySpeed = 3.0f;
    float distanceThreshold = 150.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimento do jogador com as teclas W, A, S e D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0, playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(playerSpeed, 0);

        // Lógica de desvio do golpe do jogador
        sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f enemyPosition = enemy.getPosition();
        float distance = std::sqrt(std::pow(playerPosition.x - enemyPosition.x, 2) + std::pow(playerPosition.y - enemyPosition.y, 2));

        if (distance < distanceThreshold)
        {
            // Desvio do golpe
            sf::Vector2f direction = playerPosition - enemyPosition;
            direction /= distance;
            enemy.move(-direction.x * enemySpeed, -direction.y * enemySpeed);
        }

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}
