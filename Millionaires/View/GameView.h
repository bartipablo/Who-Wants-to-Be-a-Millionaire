//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_GAMEVIEW_H
#define MILLIONAIRES_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "View.h"


class GameView: public View {
private:
    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;
public:
    GameView();

    void runGameView();
};


#endif //MILLIONAIRES_GAMEVIEW_H
