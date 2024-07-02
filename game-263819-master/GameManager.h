//
// Created by dawid on 26.05.22.
//

#ifndef GAME_263819_GAMEMENAGER_H
#define GAME_263819_GAMEMENAGER_H

#include "Player.h"
#include "Enemy.h"
#include <fstream>

enum GameState {MENU, RUNNING, FINISHED, SCOREBOARD};

struct ScoreBoard{
    int score;
    std::string name;
};

class GameManager {
    Player &player;
    int width, height;
    GameState state;
    bool player_damaged;
    int score;
    std::vector <Enemy> enemies;
    sf::Clock spawn_time, immune_time;
    std::fstream dataScore;
    ScoreBoard sc_board[10];
public:
    GameManager(Player &p, int w, int h);
    void update();
    void update_enemy();
    bool collision_enemy();
    void collision_bullet();
    void create_enemy(int hp);
    void check_level_up();
    void read_records();
    int check_score() const;
    void save_record(std::string name);
    void init_empty_score();
    void set_game_state(GameState gstate);
    std::vector <Enemy> get_enemies() const;
    GameState get_game_state() const;
    bool is_player_damaged() const;
    int get_score() const;
    void default_settings();
};


#endif //GAME_263819_GAMEMENAGER_H
