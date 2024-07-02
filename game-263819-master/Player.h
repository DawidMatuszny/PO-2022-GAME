//
// Created by dawid on 26.05.22.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>

enum PlayerState {STAY, RUN, SHOOT, DEAD};

struct Bullet{
    sf::Vector2i position;
    sf::Vector2i direction;
};

class Player {
int field_width, field_height, last_side;
int health, level, damage, movement_speed;
double attack_speed;
sf::Clock reload_bullet;
PlayerState player_state;
sf::Vector2i position, last_direction;
std::vector <Bullet> bullets;
public:
    Player(int field_w, int field_h);
    void move(sf::Vector2i vec);
    sf::Vector2i move_out_of_window(sf::Vector2i vec);
    void shoot();
    void bullets_update();
    void destroy_bullet(size_t index);
    void set_player_state(PlayerState state);
    void hit();
    void set_movement_speed(int speed);
    void level_up();
    int get_movement_speed() const;
    int get_level() const;
    PlayerState get_player_state() const;
    sf::Vector2i get_position() const;
    sf::Vector2i get_last_direction() const;
    int get_damage() const;
    int get_health() const;
    sf::Vector2i get_bullet_position(size_t bullet_number) const;
    sf::Vector2i get_bullet_direction(size_t bullet_number) const;
    size_t get_count_bullets() const;
    int get_last_side();
    void default_settings();
};


#endif //GAME_PLAYER_H
