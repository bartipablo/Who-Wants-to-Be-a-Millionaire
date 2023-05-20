//
// Created by Bartosz Pawłowski on 18/05/2023.
//

#ifndef MILLIONAIRES_GAMECONTROLLER_H
#define MILLIONAIRES_GAMECONTROLLER_H

#include "Question.h"
#include "./Lifelines/Lifeline.h"
#include "./Lifelines/FiftyFifty.h"
#include "./Lifelines/PhoneToFriend.h"
#include "./Lifelines/AudienceSupport.h"
#include "./Reader.h"

class GameController {
private:
    Answer selectedAnswer;

    Question question;

    //lifelines
    FiftyFifty fiftyFifty;

    PhoneToFriend phoneToFriend;

    AudienceSupport audienceSupport;
    //lifelines

    int questionNumber;

    int guaranteedAmount;

    int gainedAmount;

    Lifeline* lifeLineA;

    Lifeline* lifeLineB;

    Lifeline* lifeLineC;


public:
    GameController();

    ~GameController();

    Question getQuestion();

    int getGuaranteedAmount();

    void setGuaranteedAmount(int guaranteedAmount);

    int getQuestionNumber();

    int getGainedAmount();

    void setGainedAmount(int gainedAmount);

    void loadNextQuestion();

    Lifeline* getLifeLineA();

    Lifeline* getLifeLineB();

    Lifeline* getLifeLineC();

    Answer getSelectedAnswer();

    void setSelectedAnswer(Answer answer);


};


#endif //MILLIONAIRES_GAMECONTROLLER_H
