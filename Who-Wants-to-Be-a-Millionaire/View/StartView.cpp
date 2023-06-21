//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#include "StartView.h"


void StartView::runStartView() {
    sf::RenderWindow window(sf::VideoMode(2200 * Configuration::resolutionFactor, 1600 * Configuration::resolutionFactor), "Who want to be a millionaire?");

    std::thread loadingThread([this]() {
        loadGameView();
    });

    startMusic.play();
    bool menuMusicIsPlaying = false;

    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(930 * Configuration::resolutionFactor, 1300 * Configuration::resolutionFactor);
    startButton.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);

    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    backgroundSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    logoSprite.setOrigin(logoSprite.getLocalBounds().width / 2, logoSprite.getLocalBounds().height / 2);
    logoSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    logoSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    loading.setOrigin(loading.getLocalBounds().width / 2, loading.getLocalBounds().height / 2);
    loading.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 680);
    switchOnGeneratingQuestionByAIButton.setPosition(window.getSize().x / 3.5, 50);
    switchOffGeneratingQuestionByAIButton.setPosition(window.getSize().x / 3.5, 50);
    loading.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    switchOnGeneratingQuestionByAIButton.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    switchOffGeneratingQuestionByAIButton.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    float rotationSpeed = 0.015f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Configuration::disableProgram();
                window.close();
            }

            //LEFT MOUSE BUTTON CLICK
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    //START BUTTON HANDLER
                    if (startButton.getGlobalBounds().contains(mousePosition) && isLoadedGameView) {
                        window.display();
                        window.close();
                        handleClickStart(startButton);
                    }

                    if (switchOnGeneratingQuestionByAIButton.getGlobalBounds().contains(mousePosition) && !Configuration::isSetGenerateQuestionByAI()) {
                        Configuration::setGeneratingQuestionByAI(true);
                        continue;
                    }

                    if (switchOffGeneratingQuestionByAIButton.getGlobalBounds().contains(mousePosition) && Configuration::isSetGenerateQuestionByAI()) {
                        Configuration::setGeneratingQuestionByAI(false);
                    }
                }
            }
        }

        window.clear();

        backgroundSprite.rotate(rotationSpeed * 0.5f);




        window.draw(backgroundSprite);
        window.draw(logoSprite);

        if (Configuration::isSetGenerateQuestionByAI()) window.draw(switchOffGeneratingQuestionByAIButton);
        else window.draw(switchOnGeneratingQuestionByAIButton);

        if (!isLoadedGameView) window.draw(loading);
        else window.draw(startButton);

        if (startMusic.getStatus() == sf::Music::Stopped && !menuMusicIsPlaying) {
            menuMusicIsPlaying = true;
            menuMusic.play();
            menuMusic.setLoop(true);
        }

        window.display();
    }

    try {
        loadingThread.join();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

StartView::StartView() {
    View::prepareSprite(&logoTexture, &logoSprite, "../resources/images/logo.png");
    View::prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/background.png");

    View::prepareSound(&startMusicBuffer, &startMusic, "../resources/sounds/StartGame.flac");
    View::prepareSound(&menuMusicBuffer, &menuMusic, "../resources/sounds/music01.flac");

    View::prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");
    View::prepareText(&startButton, "Start", &font, 120);
    View::prepareText(&loading, "Loading resources...", &font, 60);
    View::prepareText(&switchOffGeneratingQuestionByAIButton, "AI questions generation (BETA): on", &font, 60);
    View::prepareText(&switchOnGeneratingQuestionByAIButton, "AI questions generation (BETA): off", &font, 60);

    icon.loadFromFile("../resources/images/icon.png");
}


void StartView::handleClickStart(sf::Text &button) {
    startMusic.stop();
    menuMusic.stop();
    gameView->resetGame();
    gameView->runGameView();
}

void StartView::loadGameView() {
    if (!Configuration::isTheFirstRunning()) return;

    std::unique_ptr<GameView> newGameView = std::make_unique<GameView>();
    gameView = std::move(newGameView);
    isLoadedGameView = true;
    Configuration::disableTheFirstRunning();
}






