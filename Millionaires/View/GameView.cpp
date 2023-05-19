//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "GameView.h"

std::string awardsStr[12] = {"$500", "$1,000", "$2,000", "$5,000", "$10,000", "$20,000", "$50,000",
                          "$75,000", "$150,000", "$250,000", "$500,000", "$1 MILION"};

GameView::GameView() {
    //loading from resources:
    prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/game-background.png");
    prepareSprite(&fiftyTexture, &fiftySprite, "./resources/images/lifeline-50.png");
    prepareSprite(&fiftyOrangeTexture, &fiftyOrangeSprite, "./resources/images/lifeline-50-orange.png");
    prepareSprite(&phoneToFriendTexture, &phoneToFriendSprite, "./resources/images/lifeline-phone-a-friend.png");
    prepareSprite(&phoneToFriendOrangeTexture, &phoneToFriendOrangeSprite, "./resources/images/lifeline-phone-a-friend-orange.png");
    prepareSprite(&audienceSupportTexture, &audienceSupportSprite, "./resources/images/lifeline-ask-the-audience.png");
    prepareSprite(&audienceSupportOrangeTexture, &audienceSupportOrangeSprite, "./resources/images/lifeline-ask-the-audience-orange.png");

    prepareSound(&gameMusicBuffer1, &gameMusic1, "/resources/sounds/music01.wav");
    View::prepareFont(&font, "./resources/fonts/OpenSans-Bold.ttf");

    for (int i = 0; i < 12; i++) {
        prepareText(&awards[i], awardsStr[i], &font, 50);
    }

    //setting positions
    prepareAwardView();
    prepareLifeLinesView();
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

        //AWARD VIEW
        for (int i = 0; i < 12; i++) {
            window.draw(awards[i]);
        }
        //AWARD VIEW

        //LIFELINES VIEW
        if (gameController.getLifeLineA()->isAvailable()) window.draw(fiftySprite);
        else window.draw(fiftyOrangeSprite);

        if (gameController.getLifeLineB()->isAvailable()) window.draw(phoneToFriendSprite);
        else window.draw(phoneToFriendOrangeSprite);

        if (gameController.getLifeLineC()->isAvailable()) window.draw(audienceSupportSprite);
        else window.draw(audienceSupportOrangeSprite);
        //LIFELINES VIEW

        window.display();
    }
}


void GameView::prepareAwardView() {
    for (auto & award : awards) {
        award.setFillColor(sf::Color(255, 140, 0));
    }
    awards[1].setFillColor(sf::Color::White);
    awards[6].setFillColor(sf::Color::White);
    awards[11].setFillColor(sf::Color::White);

    awards[0].setPosition(2000, 990);
    awards[1].setPosition(1980, 900);
    awards[2].setPosition(1980, 810);
    awards[3].setPosition(1980, 720);
    awards[4].setPosition(1960, 630);
    awards[5].setPosition(1960, 540);
    awards[6].setPosition(1960, 450);
    awards[7].setPosition(1960, 360);
    awards[8].setPosition(1940, 270);
    awards[9].setPosition(1940, 180);
    awards[10].setPosition(1940, 90);
    awards[11].setPosition(1930, 0);
}

void GameView::prepareLifeLinesView() {
    sf::Vector2f currentScale = fiftySprite.getScale();
    sf::Vector2f newScale(currentScale.x * 0.8f, currentScale.y * 0.8f);

    fiftySprite.setScale(newScale);
    fiftySprite.setPosition(1960, 1110);

    fiftyOrangeSprite.setScale(newScale);
    fiftyOrangeSprite.setPosition(1960, 1110);

    phoneToFriendSprite.setScale(newScale);
    phoneToFriendSprite.setPosition(1960, 1260);

    phoneToFriendOrangeSprite.setScale(newScale);
    phoneToFriendOrangeSprite.setPosition(1960, 1260);

    audienceSupportSprite.setScale(newScale);
    audienceSupportSprite.setPosition(1960, 1410);

    audienceSupportOrangeSprite.setScale(newScale);
    audienceSupportOrangeSprite.setPosition(1960, 1410);
}




