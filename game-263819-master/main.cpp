#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "GameManager.h"
#include "SFMLview.h"
#include "SFMLcontroller.h"

int main() {
    int width = 1200, height = 700;
    sf::RenderWindow window(sf::VideoMode(width,height), "CROZMAN");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);
    Player player(width, height);
    GameManager game(player, width, height);
    SFMLcontroller ctrl(player, game);
    SFMLview view(player, game, ctrl);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            ctrl.event_loop(event);
        }
        window.clear();
        if (game.get_game_state() == MENU){
            view.draw_menu(window);
        }
        if (game.get_game_state() == RUNNING) {
            view.draw_game(window);
            game.update();
            ctrl.check_player_state();
            if (player.get_player_state() == RUN && player.get_health() > 0)
                ctrl.movement();
        }
        if (game.get_game_state() == FINISHED){
            view.draw_input_name(window);
        }
        if (game.get_game_state() == SCOREBOARD){
            view.draw_score_board(window);
        }
        window.display();

    }
    return 0;
}
