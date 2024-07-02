//
// Created by Dawid on 2022-06-06.
//

#ifndef GAME_SFMLVIEW_H
#define GAME_SFMLVIEW_H

#include "Player.h"
#include "GameManager.h"
#include "SFMLcontroller.h"

class SFMLview {
    Player &player;
    GameManager &game;
    SFMLcontroller &ctrl;
    int frame_walk, frame_stay, frame_enemy, frame_attack, frame_dead, frame_damaged;
    sf::Texture bg_texture[6], hp_texture, button_texture[3], player_walk_texture[2], player_stay_texture[2], player_attact_texture[2], player_death_texture, bullets_texture[8], enemy_walk_texture[2];
    sf::Sprite bg_sprite[6], hp_sprite, button_sprite[3], player_walk_sprite[2][6], player_stay_sprite[2][4], player_attact_sprite[2][9], player_death_sprite[6], bullets_sprite[8], enemy_walk_sprite[2][6];
    sf::Font font;
    sf::Text level, score[2], input_name, scores;
    std::fstream score_board;
    std::string record;
public:
    SFMLview(Player &p, GameManager &g, SFMLcontroller &c);
    void draw_menu(sf::RenderWindow &window);
    void draw_game(sf::RenderWindow &window);
    void draw_input_name(sf::RenderWindow &window);
    void draw_score_board(sf::RenderWindow &window);
    void read_score();
};


#endif //GAME_SFMLVIEW_H
