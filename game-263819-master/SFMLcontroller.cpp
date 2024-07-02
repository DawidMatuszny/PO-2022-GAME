//
// Created by Dawid on 2022-06-06.
//

#include "SFMLcontroller.h"

SFMLcontroller::SFMLcontroller(Player &p, GameManager &g) : player(p), game(g) {
    input_direction = {0,0};
    pressed_up = false;
    pressed_right = false;
    pressed_down = false;
    pressed_left = false;
}

void SFMLcontroller::event_loop(sf::Event event) {
    if (game.get_game_state() == MENU) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.x > 345 && event.mouseButton.x < 1045) {
                if (event.mouseButton.y > 280 && event.mouseButton.y < 480)
                    game.set_game_state(RUNNING);
            }
        }
    }
    if (game.get_game_state() == RUNNING && player.get_player_state() != DEAD) {
        if (event.type == sf::Event::KeyReleased) {
            //Player movement
            if (event.key.code == sf::Keyboard::Up)
                pressed_up = false;
            if (event.key.code == sf::Keyboard::Right)
                pressed_right = false;
            if (event.key.code == sf::Keyboard::Down)
                pressed_down = false;
            if (event.key.code == sf::Keyboard::Left)
                pressed_left = false;
        }

        if (event.type == sf::Event::KeyPressed) {
            //Player movement
            if (event.key.code == sf::Keyboard::Up)
                pressed_up = true;
            if (event.key.code == sf::Keyboard::Right)
                pressed_right = true;
            if (event.key.code == sf::Keyboard::Down)
                pressed_down = true;
            if (event.key.code == sf::Keyboard::Left)
                pressed_left = true;

            if (event.key.code == sf::Keyboard::Space)
                player.shoot();
        }
    }
    if (game.get_game_state() == SCOREBOARD) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.x > 355 && event.mouseButton.x < 855 && event.mouseButton.y > 450 &&
                event.mouseButton.y < 650) {
                game.default_settings();
                pressed_up = false;
                pressed_right = false;
                pressed_down = false;
                pressed_left = false;
            }
        }
    }

    if (game.get_game_state() == FINISHED) {
        if (game.check_score()) {
            if (event.type == sf::Event::TextEntered) {
                if ((event.text.unicode >= 65 && event.text.unicode <= 90) ||
                    (event.text.unicode >= 97 && event.text.unicode <= 122))
                    name += event.text.unicode;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.x > 355 && event.mouseButton.x < 855 && event.mouseButton.y > 450 &&
                    event.mouseButton.y < 650) {
                    game.save_record(name);
                    game.set_game_state(SCOREBOARD);
                    name.clear();
                }
            }
        } else {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.x > 355 && event.mouseButton.x < 855 && event.mouseButton.y > 450 &&
                    event.mouseButton.y < 650)
                    game.set_game_state(SCOREBOARD);
            }
        }
    }
}

void SFMLcontroller::check_player_state() {
    if (player.get_player_state() != SHOOT && player.get_player_state() != DEAD) {
        if (pressed_left || pressed_right || pressed_up || pressed_down)
            player.set_player_state(RUN);
        if (!pressed_left && !pressed_right && !pressed_up && !pressed_down)
            player.set_player_state(STAY);
    }
}

void SFMLcontroller::movement() {
    input_direction = {0,0};
    if (pressed_up && !pressed_down) {
        input_direction = {0, -1};
        if (pressed_right && !pressed_left)
            input_direction = {1, -1};
        if (pressed_left && !pressed_right)
            input_direction = {-1, -1};
    } else {

        if (pressed_down && !pressed_up) {
            input_direction = {0, 1};
            if (pressed_right && !pressed_left)
                input_direction = {1, 1};
            if (pressed_left && !pressed_right)
                input_direction = {-1, 1};
        } else {
            if (pressed_right && !pressed_left)
                input_direction = {1, 0};
            if (pressed_left && !pressed_right)
                input_direction = {-1, 0};
        }
    }
    player.move(input_direction);
}

sf::String SFMLcontroller::get_name() const{
    return name;
}