//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "Answer.h"

Answer getRandomAnswer() {
    int randomNumber = getRandomNumber(0, 3);

    switch(randomNumber) {
        case 0:
            return A;
        case 1:
            return B;
        case 2:
            return C;
        case 3:
            return D;
        default:
            return A;
    }
}

std::string answerToString(Answer answer) {
    switch(answer) {
        case A:
            return "A";
        case B:
            return "B";
        case C:
            return "C";
        case D:
            return "D";
        default:
            return "unknown";
    }
}
