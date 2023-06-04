//
// Created by Bartosz Pawłowski on 27/05/2023.
//

#ifndef MILLIONAIRES_PHONETOFRIENDVIEW_H
#define MILLIONAIRES_PHONETOFRIENDVIEW_H

#include "../Model/Lifelines/PhoneToFriend.h"
#include "../Model/GameController.h"
#include "View.h"
#include <SFML/Graphics.hpp>
#include <thread>

class PhoneToFriendView : public View {
private:
    void dialogsHandler();

    bool loadPolishCharacters = true;

    std::string friendAnswer;

    Question* question;

    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;

    sf::Text dialogs[10];

    sf::Text closeButton;

    int lineDialogsNo;

    int lineDialogsToShow = 0;

    sf::Font font;

    std::string wrapText(std::string inputString, float maxWidth);

    int countLines(const std::string& text);


public:
    PhoneToFriendView(Question* question, std::string friendAnswer);

    void runPhoneToFriendView();

    void prepareText();
};


#endif //MILLIONAIRES_PHONETOFRIENDVIEW_H
