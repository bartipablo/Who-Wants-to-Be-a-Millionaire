//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "FiftyFifty.h"

void FiftyFifty::use() {
    if (!available) {
        return;
    }

    Answer correctAnswer = question.getCorrectAnswer();
    std::vector <Answer> otherAnswers = question.getIncorrectActiveAnswers();

    int randIndex = getRandomNumber(0, 2);
    Answer incorrectAnswer1 = otherAnswers[randIndex];

    if (randIndex >= 0 && randIndex < otherAnswers.size()) {
        auto it = otherAnswers.begin();
        std::advance(it, randIndex);

        otherAnswers.erase(it);
    }

    randIndex = getRandomNumber(0, 2);
    Answer incorrectAnswer2 = otherAnswers[randIndex];

    //tu wpisać kod który usunie dwie wytypowane odpowiedzi***************

    Lifeline::available = false;
}
