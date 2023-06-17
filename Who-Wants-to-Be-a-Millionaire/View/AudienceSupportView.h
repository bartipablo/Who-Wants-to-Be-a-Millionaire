//
// Created by Bartosz Pawłowski on 03/06/2023.
//

#ifndef MILLIONAIRES_AUDIENCESUPPORTVIEW_H
#define MILLIONAIRES_AUDIENCESUPPORTVIEW_H

#include "View.h"
#include <cmath>

class AudienceSupportView: public View  {
private:
    int answerAVotes;

    int answerBVotes;

    int answerCVotes;

    int answerDVotes;

    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;

    sf::Font font;

    sf::Text answerA;

    sf::Text answerB;

    sf::Text answerC;

    sf::Text answerD;

    sf::Text noVotesByPercentageA;

    sf::Text noVotesByPercentageB;

    sf::Text noVotesByPercentageC;

    sf::Text noVotesByPercentageD;

    sf::Text closeButton;


public:
    AudienceSupportView(int answerAVotes, int answerBVotes, int answerCVotes, int answerDVotes);

    void runAudienceSupportView();

};


#endif //MILLIONAIRES_AUDIENCESUPPORTVIEW_H
