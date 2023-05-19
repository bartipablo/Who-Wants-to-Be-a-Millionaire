//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_AUDIENCESUPPORT_H
#define MILLIONAIRES_AUDIENCESUPPORT_H

#include "Lifeline.h"
#include "../Question.h"

class AudienceSupport: public Lifeline {
private:
    Question* question;

public:
    explicit AudienceSupport(Question* question) : Lifeline(true) {
        this->question = question;
    }

    void use() override;
};


#endif //MILLIONAIRES_AUDIENCESUPPORT_H
