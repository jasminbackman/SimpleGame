#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "resource.h"
#include<list>
#include "Enemy.h"
#include "Player.h"
#include <random>
#include <chrono>

using namespace sf;

void gameLoop(sf::Clock clock, sf::Time targetFrameTime, 
    std::chrono::high_resolution_clock::time_point start_time, RenderWindow& window, Player& player, std::list<Enemy> enemies) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        sf::Time elapsedTime = clock.restart();

        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> elapsed_time = current_time - start_time;
        start_time = current_time;
        float delta_time = elapsed_time.count();

        Vector2f playerSize = player.getBody().getSize();
        Vector2f playerPosition = player.getBody().getPosition();
        Vector2i mousePosition = Mouse::getPosition(window);
        Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= 1.0f;

        player.faceCursor(mousePosition);
        player.move(movement, delta_time);

        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            Vector2f playerPosition = player.getBody().getPosition();
            Vector2f enemyPosition = it->getBody().getPosition();
            Vector2f direction = playerPosition - enemyPosition;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0.0f) {
                direction /= length;
            }

            it->move(direction, delta_time);
        }

        window.clear();
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            window.draw(it->getBody());
        }
        window.draw(player.getBody());

        if (elapsedTime < targetFrameTime) {
            sf::sleep(targetFrameTime - elapsedTime);
        }

        window.display();
    }
}

int main() {
    sf::Clock clock;
    sf::Time targetFrameTime = sf::milliseconds(1000 / target_fps);

    RenderWindow window(VideoMode(window_width, window_height), "TheGame");

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    
    std::random_device dev;

    Player player(RectangleShape(Vector2f(50.0f, 50.0f)));
    std::list<Enemy> enemies = {};

    for (int i = 0; i < 10; i++) {
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randTop(0, 1);
        std::uniform_int_distribution<std::mt19937::result_type> randLeft(0, 1);
        
        bool isLeft = randLeft(rng) > 0;
        bool isTop = randTop(rng) > 0;
        float randomMinWidth = static_cast<float>(window_width * (isLeft ? -1 : 1));
        float randomMaxWidth = static_cast<float>((window_width + max_enemy_distance_from_play_area) * (isLeft ? -1 : 1));
        float randomMinHeight = static_cast<float>(window_height * (isTop ? 1 : -1));
        float randomMaxHeight = static_cast<float>((window_height + max_enemy_distance_from_play_area) * (isTop ? 1 : -1));
        std::uniform_real_distribution<float> randomX(std::min(randomMinWidth, randomMaxWidth), std::max(randomMinWidth, randomMaxWidth));
        std::uniform_real_distribution<float> randomY(std::min(randomMinHeight, randomMaxHeight), std::max(randomMinHeight, randomMaxHeight));
        Enemy enemy(RectangleShape(Vector2f(22.0f, 22.0f)));
        enemy.getBody().setPosition(randomX(rng), randomY(rng));
        enemy.getBody().setFillColor(Color::Magenta);
        enemies.push_back(enemy);
    }

    player.getBody().setPosition(static_cast<float>(window_width * 0.5), static_cast<float>(window_height * 0.5));  // Initial position

    gameLoop(clock, targetFrameTime, start_time, window, player, enemies);

    return 0;
}
