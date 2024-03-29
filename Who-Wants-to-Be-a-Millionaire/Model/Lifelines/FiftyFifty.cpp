//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "FiftyFifty.h"

void FiftyFifty::use() {
    if (!available) {
        return;
    }

    Answer correctAnswer = question->getCorrectAnswer();
    std::vector <Answer> otherAnswers = question->getIncorrectActiveAnswers();

    int randIndex = getRandomNumber(0, 2);
    Answer incorrectAnswer1 = otherAnswers[randIndex];

    if (randIndex >= 0 && randIndex < otherAnswers.size()) { //removing the selected answer from otherAnswers.
        auto it = otherAnswers.begin();
        std::advance(it, randIndex);

        otherAnswers.erase(it);
    }

    randIndex = getRandomNumber(0, 1);
    Answer incorrectAnswer2 = otherAnswers[randIndex];

    switch (incorrectAnswer1) {
        case A:
            question->deactivateAnswerA();
            break;
        case B:
            question->deactivateAnswerB();
            break;
        case C:
            question->deactivateAnswerC();
            break;
        case D:
            question->deactivateAnswerD();
            break;
    }

    switch (incorrectAnswer2) {
        case A:
            question->deactivateAnswerA();
            break;
        case B:
            question->deactivateAnswerB();
            break;
        case C:
            question->deactivateAnswerC();
            break;
        case D:
            question->deactivateAnswerD();
            break;
    }

    Lifeline::available = false;
}

void FiftyFifty::reset() {
    return;
}
