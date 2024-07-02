//
// Created by dawid on 26.05.22.
//

#include "GameManager.h"
#include <cstdlib>
#include <ctime>

GameManager::GameManager(Player &p, int w, int h) : player(p) {
    srand(time(nullptr));
    init_empty_score();
    width = w;
    height = h;
    default_settings();
}

void GameManager::update() {
    player.bullets_update();
    collision_bullet();

    // 3 SECOND IMMUNE AFTER COLLISION
    if (immune_time.getElapsedTime().asMilliseconds() > 3000) {
        // BACK TO NORMAL MOVEMENT SPEED, IF WAS BOOSTED
        if (player_damaged) {
            player.set_movement_speed(player.get_movement_speed() / 2);
            player_damaged = false;
        }
        // IF COLLISION : -HP, +MOVEMENT SPEED, RESTART IMMUNE TIME
        if (collision_enemy()){
            player.hit();
            player.set_movement_speed(player.get_movement_speed() * 2);
            player_damaged = true;
            immune_time.restart();
            if (player.get_health() <= 0)
                player.set_player_state(DEAD);
        }
    }

    update_enemy();
    if(spawn_time.getElapsedTime().asMilliseconds() > (3000 - score)){
        create_enemy(24);
        spawn_time.restart();
    }
    check_level_up();
}

void GameManager::update_enemy() {
    for(size_t unit = 0; unit < enemies.size(); unit++) {
        if(enemies[unit].is_alive())
            enemies[unit].move(player.get_position());
        else {
            enemies.erase(enemies.begin() + unit);
            score++;
        }
    }
}

void GameManager::collision_bullet() {
    for (size_t bullet = 0; bullet < player.get_count_bullets(); bullet++ ) {
        for (size_t unit = 0; unit < enemies.size(); unit++) {
            if (player.get_bullet_position(bullet).x + 4 > enemies[unit].get_position().x &&
                player.get_bullet_position(bullet).x < enemies[unit].get_position().x + 24)
            {
                if (player.get_bullet_position(bullet).y + 2 > enemies[unit].get_position().y &&
                    player.get_bullet_position(bullet).y < enemies[unit].get_position().y + 35)
                {
                    enemies[unit].hit(player.get_damage());
                    player.destroy_bullet(bullet);
                    unit = enemies.size();
                }
            }
        }
    }
}

bool GameManager::collision_enemy() {
    for (size_t unit = 0; unit < enemies.size(); unit++) {
        if (player.get_position().x < enemies[unit].get_position().x + 15 &&
            player.get_position().x + 15 > enemies[unit].get_position().x) {
            if (player.get_position().y + 25 > enemies[unit].get_position().y &&
                player.get_position().y < enemies[unit].get_position().y + 25)
                return true;
        }
    }
    return false;
}

void GameManager::create_enemy(int hp) {
    //SPAWN ENEMY ON LEFT OR RIGHT SIDE
    if (rand()%2 == 0){
        //LEFT
        if(rand()%2 == 0)
            enemies.push_back(Enemy({-28, rand()%height}, hp));
        //RIGHT
        else
            enemies.push_back(Enemy({width, rand()%height}, hp));
    }
    //SPAWN ENEMY BOTTOM OR TOP
    else{
        //TOP
        if(rand()%2 == 0)
            enemies.push_back(Enemy({rand()%width, -40}, hp));
        //BOTTOM
        else
            enemies.push_back(Enemy({rand()%width, height}, hp));
    }
}

void GameManager::check_level_up() {
    if (score == (10 * player.get_level()) * player.get_level())
        player.level_up();
}

void GameManager::read_records() {
    dataScore.open("../score/score.txt", std::ios::in);
    if (dataScore.good()) {
        int nrRecord = 0;
        while(!dataScore.eof()) {
            dataScore >> sc_board[nrRecord].score;
            dataScore >> sc_board[nrRecord].name;
            nrRecord++;
        }
    }
    dataScore.close();
}


int GameManager::check_score() const {
    for(int nrRecord = 0; nrRecord < 10; nrRecord++){
        if (sc_board[nrRecord].score < score)
            return nrRecord+1;
    }
    return 0;
}

void GameManager::save_record(std::string name) {
    if (name == "")
        name = "unnamed";
    dataScore.open("../score/score.txt", std::ios::out | std::ios::trunc);
    if (dataScore.good()) {
        int score_place = check_score();
        for (int nrRecord = 0; nrRecord < 10; nrRecord++) {
            if (nrRecord == score_place - 1)
                dataScore << score << "\t" << name << std::endl;
            if (sc_board[nrRecord].score != 0 && nrRecord < 9)
                dataScore << sc_board[nrRecord].score << "\t" << sc_board[nrRecord].name << std::endl;
        }
    }
    dataScore.close();
}

void GameManager::init_empty_score() {
    for(int nrRecord = 0; nrRecord < 10; nrRecord++){
        sc_board[nrRecord] = {0, ""};
    }
}

void GameManager::set_game_state(GameState gstate) {
    state = gstate;
}

std::vector <Enemy> GameManager::get_enemies() const{
    return enemies;
}

GameState GameManager::get_game_state() const{
    return state;
}

bool GameManager::is_player_damaged() const{
    return player_damaged;
}

int GameManager::get_score() const {
    return score;
}

void GameManager::default_settings() {
    enemies.clear();
    read_records();
    state = MENU;
    score = 0;
    player_damaged = false;
    player.default_settings();
}