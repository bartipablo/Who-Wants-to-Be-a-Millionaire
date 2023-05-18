//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "GameView.h"

GameView::GameView() {

}

void GameView::runGameView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
