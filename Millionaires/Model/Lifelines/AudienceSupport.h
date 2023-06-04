//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_AUDIENCESUPPORT_H
#define MILLIONAIRES_AUDIENCESUPPORT_H

#include "Lifeline.h"
#include "../Question.h"
#include "../../Functions/Random.h"

class AudienceSupport: public Lifeline {
private:
    Question* question;

    int numberOfAudiences = 100;

    int answerAVotes = 0;

    int answerBVotes = 0;

    int answerCVotes = 0;

    int answerDVotes = 0;

    int determineChanceOfAnsweringCorrectly();

    void vote(Answer answer);

public:
    explicit AudienceSupport(Question* question) : Lifeline(true) {
        this->question = question;
    }

    void use() override;


};


#endif //MILLIONAIRES_AUDIENCESUPPORT_H
