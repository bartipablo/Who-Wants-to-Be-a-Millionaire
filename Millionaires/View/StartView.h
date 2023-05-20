//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#ifndef MILLIONAIRES_STARTVIEW_H
#define MILLIONAIRES_STARTVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "GameView.h"
#include "View.h"

class StartView: public View {
private:
    sf::Texture logoTexture;

    sf::Texture backgroundTexture;

    sf::Sprite logoSprite;

    sf::Sprite backgroundSprite;

    sf::SoundBuffer startMusicBuffer;

    sf::Sound startMusic;

    sf::SoundBuffer menuMusicBuffer;

    sf::Sound menuMusic;

    sf::Font font;

    sf::Text startButton;

    sf::Text loading;

    void handleClickStart(sf::Text& button);

public:
    StartView();

    void runStartView();

};



#endif //MILLIONAIRES_STARTVIEW_H
