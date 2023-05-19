//
// Created by Bartosz Pawłowski on 18/05/2023.
//

#include "GameController.h"

GameController::GameController() : fiftyFifty(&question), phoneToFriend(&question), audienceSupport(&question) {
    this->questionNumber = 0;
    this->lifeLineA = &fiftyFifty;
    this->lifeLineB = &phoneToFriend;
    this->lifeLineC = &audienceSupport;
}


GameController::~GameController() {

}


Question GameController::getQuestion() {
    return question;
}

int GameController::getGuaranteedAmount() {
    return guaranteedAmount;
}

void GameController::setGuaranteedAmount(int guaranteedAmount) {
    this->guaranteedAmount = guaranteedAmount;
}

int GameController::getGainedAmount() {
    gainedAmount;
}

void GameController::setGainedAmount(int gainedAmount) {
    this->gainedAmount = gainedAmount;
}

void GameController::loadNextQuestion() {
    questionNumber++;

    if (questionNumber == 1) {
        guaranteedAmount = 0;
        gainedAmount = 0;
    }
    else {
        if (question.isGuaranteedAmount()) {
            guaranteedAmount = question.getAmount();
        }
        gainedAmount = question.getAmount();
    }

    question = Reader::getRandomQuestion(questionNumber);

}


Lifeline *GameController::getLifeLineA() {
    return lifeLineA;
}


Lifeline *GameController::getLifeLineB() {
    return lifeLineB;
}


Lifeline *GameController::getLifeLineC() {
    return lifeLineC;
}

int GameController::getQuestionNumber() {
    return questionNumber;
}




