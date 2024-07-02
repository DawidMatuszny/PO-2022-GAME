//
// Created by Dawid on 2022-06-09.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include <SFML/Graphics.hpp>


class Enemy {
    int health;
    sf::Vector2i position;
public:
    Enemy(sf::Vector2i start_position, int hp);
    void move(sf::Vector2i player_position);
    void hit(int damage);
    bool is_alive() const;
    sf::Vector2i get_position() const;
};

#endif //GAME_ENEMY_H
