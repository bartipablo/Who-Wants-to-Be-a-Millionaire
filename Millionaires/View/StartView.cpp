//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#include "StartView.h"


void StartView::runStartView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    startMusic.play();
    bool menuMusicIsPlaying = false;

    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(930, 1300);

    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    logoSprite.setOrigin(logoSprite.getLocalBounds().width / 2, logoSprite.getLocalBounds().height / 2);
    logoSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    loading.setOrigin(loading.getLocalBounds().width / 2, loading.getLocalBounds().height / 2);
    loading.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 700);

    float rotationSpeed = 0.015f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //LEFT MOUSE BUTTON CLICK
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    //START BUTTON HANDLER
                    if (startButton.getGlobalBounds().contains(mousePosition)) {
                        window.draw(loading);
                        window.display();
                        window.close();
                        handleClickStart(startButton);
                    }
                }
            }
        }

        window.clear();

        backgroundSprite.rotate(rotationSpeed * 0.5f); // Mnożnik prędkości wynosi 0.5f

        window.draw(backgroundSprite);
        window.draw(logoSprite);
        window.draw(startButton);

        if (startMusic.getStatus() == sf::Music::Stopped && !menuMusicIsPlaying) {
            menuMusicIsPlaying = true;
            menuMusic.play();
            menuMusic.setLoop(true);
        }

        window.display();
    }
}

StartView::StartView() {
    View::prepareSprite(&logoTexture, &logoSprite, "./resources/images/logo.png");
    View::prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/background.png");

    View::prepareSound(&startMusicBuffer, &startMusic, "./resources/sounds/StartGame.wav");
    View::prepareSound(&menuMusicBuffer, &menuMusic, "./resources/sounds/music01.wav");

    View::prepareFont(&font, "./resources/fonts/OpenSans-Bold.ttf");
    View::prepareText(&startButton, "Start", &font, 120);
    View::prepareText(&loading, "Loading...", &font, 60);
}


void runNewGame() {
    GameView gameView;
    gameView.runGameView();
}

void StartView::handleClickStart(sf::Text &button) {
    startMusic.stop();
    menuMusic.stop();
    GameView gameView;
    gameView.runGameView();
}






