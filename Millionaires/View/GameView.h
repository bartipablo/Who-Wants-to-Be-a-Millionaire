//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_GAMEVIEW_H
#define MILLIONAIRES_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "View.h"
#include "../Model/Question.h"
#include "../Model/GameController.h"

class GameView: public View {
private:
    GameController gameController;

    sf::Texture backgroundTexture;

    sf::Texture fiftyTexture;

    sf::Texture fiftyOrangeTexture;

    sf::Texture phoneToFriendTexture;

    sf::Texture phoneToFriendOrangeTexture;

    sf::Texture audienceSupportTexture;

    sf::Texture audienceSupportOrangeTexture;

    sf::Sprite backgroundSprite;

    sf::Sprite fiftySprite;

    sf::Sprite fiftyOrangeSprite;

    sf::Sprite phoneToFriendSprite;

    sf::Sprite phoneToFriendOrangeSprite;

    sf::Sprite audienceSupportSprite;

    sf::Sprite audienceSupportOrangeSprite;

    sf::SoundBuffer gameMusicBuffer1;

    sf::Sound gameMusic1;

    sf::Text awards[12];

    sf::Font font;

    //methods
    void prepareAwardView();

    void prepareLifeLinesView();

public:
    GameView();

    void runGameView();

};


#endif //MILLIONAIRES_GAMEVIEW_H
