//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "GameView.h"

GameView::GameView() {
    prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/game-background.png");
    //prepareSound();
}

void GameView::runGameView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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

        window.draw(backgroundSprite);

        window.display();
    }
}
