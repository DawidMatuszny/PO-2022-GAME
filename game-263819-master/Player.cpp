//
// Created by dawid on 26.05.22.
//

#include "Player.h"
#include <iostream>

Player::Player(int field_w, int field_h) {
    field_width = field_w;
    field_height = field_h;
    default_settings();
}

void Player::move(sf::Vector2i vec) {
    vec = move_out_of_window(vec);
    position += movement_speed * vec;
    last_direction = vec;
    if (vec.x != 0)
        last_side = vec.x;
}

sf::Vector2i Player::move_out_of_window(sf::Vector2i vec) {
    if ((position.x <= 0 && vec.x == -1) || (position.x >= field_width - 24 && vec.x == 1))
        vec.x = 0;
    if ((position.y <= 0 && vec.y == -1) || (position.y >= field_height - 40 && vec.y == 1))
        vec.y = 0;
    return vec;
}

void Player::shoot() {
    if (reload_bullet.getElapsedTime().asMilliseconds() > 1000/attack_speed) {
        bullets.push_back({{last_direction.x < 0 ? position.x - 4 : position.x + (14 * last_direction.x) + 10,
                            last_direction.y < 0 ? position.y - 4 : position.y + (20 * last_direction.y) + 20},
                           last_direction});
        player_state = SHOOT;
        reload_bullet.restart();
    }
}

void Player::level_up() {
    level++;
    damage++;
    attack_speed += 0.5;
}

void Player::bullets_update() {
    //BULLET MOVEMENT
    for (size_t nrbullet = 0; nrbullet < bullets.size(); nrbullet++){
        if (bullets[nrbullet].direction.x != 0 && bullets[nrbullet].direction.y != 0)
            bullets[nrbullet].position += 5 * bullets[nrbullet].direction;
        else
            bullets[nrbullet].position += 10 * bullets[nrbullet].direction;

    //DESTROY BULLET WHICH IS OUT OF SCREEN
        if (bullets[nrbullet].position.x > field_width || bullets[nrbullet].position.y > field_height ||
            bullets[nrbullet].position.x < 0 || bullets[nrbullet].position.y < 0 )
            bullets.erase(bullets.begin()+nrbullet);
    }
}

void Player::hit(){
    health--;
};

int Player::get_level() const{
    return level;
}

void Player::set_movement_speed(int speed) {
    movement_speed = speed;
}

void Player::destroy_bullet(size_t index) {
    bullets.erase(bullets.begin() + index);
}

void Player::set_player_state(PlayerState state) {
    player_state = state;
}

int Player::get_movement_speed() const{
    return movement_speed;
}

PlayerState Player::get_player_state() const{
    return player_state;
}

sf::Vector2i Player::get_position() const{
    return position;
}

sf::Vector2i Player::get_last_direction() const{
    return last_direction;
}

int Player::get_damage() const{
    return damage;
}

int Player::get_health() const{
    return health;
}

size_t Player::get_count_bullets() const{
    return bullets.size();
}

sf::Vector2i Player::get_bullet_position(size_t bullet_number) const{
    return bullets[bullet_number].position;
}

sf::Vector2i Player::get_bullet_direction(size_t bullet_number) const{
    return bullets[bullet_number].direction;
}

int Player::get_last_side() {
    return last_side;
}

void Player::default_settings() {
    bullets.clear();
    level = 1;
    movement_speed = 2;
    health = 3;
    player_state = STAY;
    attack_speed = 1.0;
    damage = 10;
    position = {600,340};
    last_direction = {1,0};
    last_side = 1;
}