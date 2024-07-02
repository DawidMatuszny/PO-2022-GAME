//
// Created by Dawid on 2022-06-06.
//

#ifndef GAME_SFMLCONTROLLER_H
#define GAME_SFMLCONTROLLER_H

#include "Player.h"
#include "GameManager.h"

class SFMLcontroller {
    Player &player;
    GameManager &game;
    sf::Vector2i input_direction;
    sf::String name;
    bool pressed_right, pressed_up, pressed_left, pressed_down;
public:
    SFMLcontroller(Player &p, GameManager &g);
    void event_loop(sf::Event event);
    void check_player_state();
    void movement();
    sf::String get_name() const;
};


#endif //GAME_SFMLCONTROLLER_H
