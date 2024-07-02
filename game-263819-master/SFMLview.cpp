//
// Created by Dawid on 2022-06-06.
//

#include "SFMLview.h"
#include <iostream>
SFMLview::SFMLview(Player &p, GameManager &g, SFMLcontroller &c) : player(p), game(g), ctrl(c) {
    frame_walk = 0;
    frame_stay = 0;
    frame_attack = 0;
    frame_dead = 0;
    frame_enemy = 0;
    frame_damaged = 0;

    //BULLET TEXTURES PATHS
    std::string path_bullets[8] = {"../graphics/bulletUP.png", "../graphics/bulletUPRIGHT.png", "../graphics/bulletRIGHT.png",
                                   "../graphics/bulletDOWNRIGHT.png", "../graphics/bulletDOWN.png", "../graphics/bulletDOWNLEFT.png",
                                   "../graphics/bulletLEFT.png", "../graphics/bulletUPLEFT.png"};

    //FONT
    if(!font.loadFromFile("../font/GothicA1-Black.ttf"))
        abort();

    //MENU
    //LOAD BACKGROUND TEXTURE
    if (!bg_texture[0].loadFromFile("../graphics/bgmenu.png"))
        abort();
    bg_sprite[0].setTexture(bg_texture[0]);
    bg_sprite[0].setPosition({0,0});

    //LOAD BUTTON TEXTURE
    if (!button_texture[0].loadFromFile("../graphics/button.png"))
        abort();
    button_sprite[0].setTexture(button_texture[0]);
    button_sprite[0].setPosition({345,280});


    //GAME
    //LABELS
    level.setFont(font);
    level.setCharacterSize(22);
    level.setFillColor(sf::Color::Black);
    level.setPosition({20,20});

    score[0].setFont(font);
    score[0].setCharacterSize(22);
    score[0].setFillColor(sf::Color::Black);
    score[0].setPosition({550,20});

    //LOAD HP TEXTURE
    if (!hp_texture.loadFromFile("../graphics/hp.png"))
        abort();
    hp_sprite.setTexture(hp_texture);

    //LOAD BACKGROUND TEXTURE
    if (!bg_texture[1].loadFromFile("../graphics/bggame.png"))
        abort();
    bg_sprite[1].setTexture(bg_texture[1]);
    bg_sprite[1].setPosition({0,0});
    if (!bg_texture[2].loadFromFile("../graphics/bggamehit.png"))
        abort();
    bg_sprite[2].setTexture(bg_texture[2]);
    bg_sprite[2].setPosition({0,0});

    //LOAD PLAYER TEXTURES
    //STAY
    if (!player_stay_texture[0].loadFromFile("../graphics/Idle.png"))
        abort();
    for (int index = 0; index < 4; index++){
        player_stay_sprite[0][index].setTexture(player_stay_texture[0]);
        player_stay_sprite[0][index].setTextureRect(sf::IntRect(48 * index, 0, 32, 40));
    }

    if (!player_stay_texture[1].loadFromFile("../graphics/IdleL.png"))
        abort();
    for (int index = 0; index < 4; index++){
        player_stay_sprite[1][index].setTexture(player_stay_texture[1]);
        player_stay_sprite[1][index].setTextureRect(sf::IntRect((48 * index) + 16, 0, 32, 40));
    }

    //WALK
    if (!player_walk_texture[0].loadFromFile("../graphics/Walk.png"))
        abort();
    for (int index = 0; index < 6; index++){
        player_walk_sprite[0][index].setTexture(player_walk_texture[0]);
        player_walk_sprite[0][index].setTextureRect(sf::IntRect(48 * index, 0, 32, 40));
    }

    if (!player_walk_texture[1].loadFromFile("../graphics/WalkL.png"))
        abort();
    for (int index = 0; index < 6; index++){
        player_walk_sprite[1][index].setTexture(player_walk_texture[1]);
        player_walk_sprite[1][index].setTextureRect(sf::IntRect((48 * index) + 16, 0, 32, 40));
    }

    //SHOOT
    if (!player_attact_texture[0].loadFromFile("../graphics/Attack.png"))
        abort();
    for (int index = 0; index < 9; index++){
        player_attact_sprite[0][index].setTexture(player_attact_texture[0]);
        player_attact_sprite[0][index].setTextureRect(sf::IntRect(48 * index, 0, 32, 40));
    }
    if (!player_attact_texture[1].loadFromFile("../graphics/AttackL.png"))
        abort();
    for (int index = 0; index < 9; index++){
        player_attact_sprite[1][index].setTexture(player_attact_texture[1]);
        player_attact_sprite[1][index].setTextureRect(sf::IntRect((48 * index) + 16, 0, 32, 40));
    }

    //DEATH
    if (!player_death_texture.loadFromFile("../graphics/Death.png"))
        abort();
    for (int index = 0; index < 6; index++){
        player_death_sprite[index].setTexture(player_death_texture);
        player_death_sprite[index].setTextureRect(sf::IntRect(48 * index, 0, 48, 40));
    }

    //LOAD BULLET TEXTURES
    for (int index = 0; index < 8; index++){
        if (!bullets_texture[index].loadFromFile(path_bullets[index]))
            abort();
    }

    for (int index = 0; index < 8; index++){
        bullets_sprite[index].setTexture(bullets_texture[index]);
    }

    //LOAD ENEMY TEXTURES
    if (!enemy_walk_texture[0].loadFromFile("../graphics/Enemy.png"))
        abort();
    for (int index = 0; index < 6; index++){
        enemy_walk_sprite[0][index].setTexture(enemy_walk_texture[0]);
        enemy_walk_sprite[0][index].setTextureRect(sf::IntRect(48 * index, 0, 32, 40));
    }

    if (!enemy_walk_texture[1].loadFromFile("../graphics/EnemyL.png"))
        abort();
    for (int index = 0; index < 6; index++){
        enemy_walk_sprite[1][index].setTexture(enemy_walk_texture[1]);
        enemy_walk_sprite[1][index].setTextureRect(sf::IntRect((48 * index) + 16, 0, 32, 40));
    }

    //INPUT NAME
    if (!bg_texture[3].loadFromFile("../graphics/bginput.png"))
        abort();
    bg_sprite[3].setTexture(bg_texture[3]);
    bg_sprite[3].setPosition({0,0});

    if (!bg_texture[4].loadFromFile("../graphics/bginput2.png"))
        abort();
    bg_sprite[4].setTexture(bg_texture[4]);
    bg_sprite[4].setPosition({0,0});

    score[1].setFont(font);
    score[1].setFillColor(sf::Color::White);
    score[1].setCharacterSize(50);
    score[1].setPosition({600,55});

    input_name.setFont(font);
    input_name.setFillColor(sf::Color::White);
    input_name.setCharacterSize(35);

    if (!button_texture[1].loadFromFile("../graphics/button2.png"))
        abort();
    button_sprite[1].setTexture(button_texture[1]);
    button_sprite[1].setPosition({355,450});

    //SCORE BOARD
    if (!bg_texture[5].loadFromFile("../graphics/bgscoreboard.png"))
        abort();
    bg_sprite[5].setTexture(bg_texture[5]);
    bg_sprite[5].setPosition({0,0});

    scores.setFont(font);
    scores.setFillColor(sf::Color::White);
    scores.setCharacterSize(25);
    scores.setPosition({520, 100});

    if (!button_texture[2].loadFromFile("../graphics/button3.png"))
        abort();
    button_sprite[2].setTexture(button_texture[2]);
    button_sprite[2].setPosition({355,450});
}

void SFMLview::draw_menu(sf::RenderWindow &window) {
    window.draw(bg_sprite[0]);
    window.draw(button_sprite[0]);
}

void SFMLview::draw_game(sf::RenderWindow &window) {
    //BACKGROUND
    if (game.is_player_damaged()){
        window.draw(bg_sprite[1 + (frame_damaged/6)]);
        frame_damaged++;
        if (frame_damaged > 11)
            frame_damaged = 0;
    }

    else
        window.draw(bg_sprite[1]);

    //DRAW PLAYER
    if (player.get_player_state() == STAY){
        if (player.get_last_side() == 1) {
            player_stay_sprite[0][frame_stay / 4].setPosition(sf::Vector2f(player.get_position()));
            window.draw(player_stay_sprite[0][frame_stay / 4]);
        }
        if (player.get_last_side() == -1){
            player_stay_sprite[1][frame_stay / 4].setPosition(sf::Vector2f(player.get_position()));
            window.draw(player_stay_sprite[1][frame_stay / 4]);
        }
        frame_stay++;
        if (frame_stay > 14)
            frame_stay = 0;
    }
    if (player.get_player_state() == RUN) {
        if (player.get_last_direction().x == 1 || player.get_last_side() == 1) {
            player_walk_sprite[0][frame_walk / 3].setPosition(sf::Vector2f(player.get_position()));
            window.draw(player_walk_sprite[0][frame_walk / 3]);
        }
        if (player.get_last_direction().x == -1 || player.get_last_side() == -1) {
            player_walk_sprite[1][frame_walk / 3].setPosition(sf::Vector2f(player.get_position()));
            window.draw(player_walk_sprite[1][frame_walk / 3]);
        }
        frame_walk++;
        if (frame_walk > 16)
            frame_walk = 0;
    }

    if (player.get_player_state() == SHOOT){
        if (player.get_last_direction().x == 1 || player.get_last_side() == 1) {
            if(player.get_last_direction().y == 0) {
                player_attact_sprite[0][frame_attack / 2].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[0][frame_attack / 2]);
            }
            if(player.get_last_direction().y == 1) {
                player_attact_sprite[0][3 + (frame_attack / 2)].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[0][3 + (frame_attack / 2)]);
            }
            if(player.get_last_direction().y == -1) {
                player_attact_sprite[0][6 + (frame_attack / 2)].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[0][6 + (frame_attack / 2)]);
            }
        }
        if (player.get_last_direction().x == -1 || player.get_last_side() == -1) {
            if(player.get_last_direction().y == 0) {
                player_attact_sprite[1][8 - (frame_attack / 2)].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[1][8 - (frame_attack / 2)]);
            }
            if(player.get_last_direction().y == 1) {
                player_attact_sprite[1][5 - (frame_attack / 2)].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[1][5 - (frame_attack / 2)]);
            }
            if(player.get_last_direction().y == -1) {
                player_attact_sprite[1][2 - (frame_attack / 2)].setPosition(sf::Vector2f(player.get_position()));
                window.draw(player_attact_sprite[1][2 - (frame_attack / 2)]);
            }
        }
        frame_attack++;
        if (frame_attack > 6){
            frame_attack = 0;
            player.set_player_state(STAY);
        }
    }

    if (player.get_player_state() == DEAD){
        player_death_sprite[frame_dead / 10].setPosition(sf::Vector2f(player.get_position()));
        window.draw(player_death_sprite[frame_dead / 10]);
        if (frame_dead < 60)
            frame_dead++;
        else {
            game.set_game_state(FINISHED);
            scores.setString("");
        }
    }

    //DRAW BULLETS
    for (size_t nrbullet=0; nrbullet<player.get_count_bullets(); nrbullet++) {
        if (player.get_bullet_direction(nrbullet).x == 0)
        {
            if (player.get_bullet_direction(nrbullet).y == -1) {
                bullets_sprite[0].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                window.draw(bullets_sprite[0]);
            }
            if (player.get_bullet_direction(nrbullet).y == 1){
                bullets_sprite[4].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                window.draw(bullets_sprite[4]);
            }
        }
        else{
            if (player.get_bullet_direction(nrbullet).x == 1){
                if (player.get_bullet_direction(nrbullet).y == 0){
                    bullets_sprite[2].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[2]);
                }
                if (player.get_bullet_direction(nrbullet).y == -1){
                    bullets_sprite[1].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[1]);
                }
                if (player.get_bullet_direction(nrbullet).y == 1){
                    bullets_sprite[3].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[3]);
                }
            }
            if (player.get_bullet_direction(nrbullet).x == -1){
                if (player.get_bullet_direction(nrbullet).y == 0){
                    bullets_sprite[6].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[6]);
                }
                if (player.get_bullet_direction(nrbullet).y == -1){
                    bullets_sprite[7].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[7]);
                }
                if (player.get_bullet_direction(nrbullet).y == 1){
                    bullets_sprite[5].setPosition(sf::Vector2f(player.get_bullet_position(nrbullet)));
                    window.draw(bullets_sprite[5]);
                }
            }
        }

    }


    for(size_t unit=0; unit < game.get_enemies().size(); unit++){
        if (player.get_position().x >= game.get_enemies()[unit].get_position().x) {
            enemy_walk_sprite[0][frame_enemy / 4].setPosition(sf::Vector2f(game.get_enemies()[unit].get_position()));
            window.draw(enemy_walk_sprite[0][frame_enemy / 4]);
        }
        if (player.get_position().x < game.get_enemies()[unit].get_position().x) {
            enemy_walk_sprite[1][frame_enemy / 4].setPosition(sf::Vector2f(game.get_enemies()[unit].get_position()));
            window.draw(enemy_walk_sprite[1][frame_enemy / 4]);
        }
    }
    frame_enemy++;
    if (frame_enemy > 14)
        frame_enemy = 0;

    //LEVEL
    level.setString("Level: " + std::to_string(player.get_level()));
    window.draw(level);
    score[0].setString("Score: " + std::to_string(game.get_score()));
    window.draw(score[0]);

    //DRAW HP
    for (int heart = 0; heart < player.get_health(); heart++) {
        hp_sprite.setPosition(sf::Vector2f(1080 + (heart * 40), 10));
        window.draw(hp_sprite);
    }
}

void SFMLview::draw_input_name(sf::RenderWindow &window) {
    score[1].setString(std::to_string(game.get_score()));
    if(game.check_score()) {
        window.draw(bg_sprite[3]);
        input_name.setPosition(600 - (ctrl.get_name().getSize() * 10), 325);
        input_name.setString(ctrl.get_name());
        window.draw(input_name);
        window.draw(score[1]);
        window.draw(button_sprite[1]);
    }
    else{
        window.draw(bg_sprite[4]);
        window.draw(button_sprite[1]);
        window.draw(score[1]);
    }
}

void SFMLview::draw_score_board(sf::RenderWindow &window) {
    window.draw(bg_sprite[5]);
    if(scores.getString() == "")
        read_score();
    window.draw(scores);
    window.draw(button_sprite[2]);
}

void SFMLview::read_score() {
    score_board.open("../score/score.txt", std::ios::in);
    if (score_board.good())
    {
        while(std::getline(score_board, record)) {
            scores.setString(scores.getString() + record + "\n");
        }
    }
    score_board.close();
}
