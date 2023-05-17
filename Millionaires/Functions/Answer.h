//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_ANSWER_H
#define MILLIONAIRES_ANSWER_H

#include "Random.h"

enum Answer {
    A,
    B,
    C,
    D
};

Answer getRandomAnswer();

std::string answerToString(Answer answer);


#endif //MILLIONAIRES_ANSWER_H
