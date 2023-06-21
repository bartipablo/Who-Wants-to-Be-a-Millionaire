//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#ifndef MILLIONAIRES_WINNERVIEW_H
#define MILLIONAIRES_WINNERVIEW_H

#include "View.h"
#include "../Model/GameController.h"
#include "../Configuration.h"

class WinnerView: public View {

private:
    sf::Image icon;

    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;

    sf::Text gainedAmountText;

    sf::Text gainedAmountDescriptionText;

    sf::Text dateText;

    sf::Text hostText;

    sf::Text playerNameText;

    sf::Text playAgainButton;

    sf::Text exitButton;

    sf::Font font;

    int gainedAmount;

public:
    explicit WinnerView(int gainedAmount);

    void runWinnerView();

    void prepareGainedAmount();

    void prepareDate();


};


#endif //MILLIONAIRES_WINNERVIEW_H
