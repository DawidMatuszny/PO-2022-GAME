//
// Created by Dawid on 2022-06-09.
//

#include "Enemy.h"

Enemy::Enemy(sf::Vector2i start_position, int hp) {
    health = hp;
    position = start_position;
}

void Enemy::move(sf::Vector2i player_position){

    //IF "X" DISTANCE IS GREATER THAN "Y" DISTANCE, MOVE ONLY VERTICAL HORIZONTALLY
    if (abs(position.x - player_position.x) > abs(position.y - player_position.y)){
        if (position.x > player_position.x)
            position.x--;
        if (position.x < player_position.x)
            position.x++;
    }
    else {
        //IF "X" DISTANCE IS LESS "Y" THAN DISTANCE, MOVE ONLY VERTICAL
        if (abs(position.x - player_position.x) < abs(position.y - player_position.y)) {
            if (position.y > player_position.y)
                position.y--;
            if (position.y < player_position.y)
                position.y++;
        }
        //IF "X" DISTANCE IS EQUAL "Y" THAN DISTANCE, MOVE DIAGONALLY
        else {
            if (abs(position.x - player_position.x) == abs(position.y - player_position.y)) {
                if (position.x > player_position.x)
                    position.x--;
                if (position.x < player_position.x)
                    position.x++;
                if (position.y > player_position.y)
                    position.y--;
                if (position.y < player_position.y)
                    position.y++;
            }
        }
    }
}

void Enemy::hit(int damage){
    health -= damage;
}

bool Enemy::is_alive() const{
    if (health > 0)
        return true;
    else
        return false;
}

sf::Vector2i Enemy::get_position() const{
    return position;
}