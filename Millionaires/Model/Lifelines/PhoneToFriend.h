//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_PHONETOFRIEND_H
#define MILLIONAIRES_PHONETOFRIEND_H


#include <string>
#include "Lifeline.h"
#include "../Question.h"
#include <vector>
#include "../../Functions/Random.h"

enum FriendReaction {
    sure,
    uncertain,
    doesNotKnow
};


class PhoneToFriend: public Lifeline {
private:
    Question* question;

    std::string friendAnswer;

    FriendReaction getRandomFriendReaction(std::vector<Answer> activeAnswers);

    Answer getFriendAnswer(FriendReaction friendReaction);

public:
    explicit PhoneToFriend(Question* question) : Lifeline(true) {
        this->question = question;
    }

    void use() override;
};


#endif //MILLIONAIRES_PHONETOFRIEND_H
