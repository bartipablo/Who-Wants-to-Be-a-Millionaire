//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "PhoneToFriend.h"




void PhoneToFriend::use() {
    std::vector<Answer> activeAnswers = question->getActiveAnswers();
    Answer correctAnswer = question->getCorrectAnswer();

    FriendReaction friendReaction = getRandomFriendReaction(activeAnswers);
    Answer friendAnswer = getFriendAnswer(friendReaction);

    //tutaj umieścić dalszy kod

}


FriendReaction PhoneToFriend::getRandomFriendReaction(std::vector<Answer> activeAnswers) {
    int randomNumber = getRandomNumber(0, 100);

    if (activeAnswers.size() > 2) {
        if (randomNumber < 30) return sure;
        if (randomNumber >= 30 && randomNumber <= 70) return uncertain;
        if (randomNumber > 70) return doesNotKnow;
    }
    else {
        if (randomNumber < 40) return sure;
        if (randomNumber >= 40 && randomNumber <= 80) return uncertain;
        if (randomNumber > 80) return doesNotKnow;
    }
    return doesNotKnow;
}

Answer PhoneToFriend::getFriendAnswer(FriendReaction friendReaction) {
    int randomNumber = getRandomNumber(0, 100);

    if (friendReaction == sure) {
        if (randomNumber <= 90) {
            return question->getCorrectAnswer();
        }
        else {
            return question->getRandomIncorrectAnswer();
        }
    }

    else if (friendReaction == uncertain) {
        if (randomNumber <= 50) {
            return question->getCorrectAnswer();
        }
        else {
            return question->getRandomIncorrectAnswer();
        }
    }

    else if (friendReaction == doesNotKnow) {
        if (randomNumber <= 25) {
            return question->getCorrectAnswer();
        }
        else {
            return question->getRandomIncorrectAnswer();
        }
    }
    return A;
}
