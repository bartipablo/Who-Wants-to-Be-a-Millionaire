//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_FIFTYFIFTY_H
#define MILLIONAIRES_FIFTYFIFTY_H

#include "Lifeline.h"
#include "../Question.h"
#include "../../Functions/Random.h"

class FiftyFifty: public Lifeline {
private:
    Question question;

public:
    explicit FiftyFifty(Question question) : Lifeline(true) {
        this->question = question;
    }

    void use() override;
};


#endif //MILLIONAIRES_FIFTYFIFTY_H
