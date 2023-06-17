//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "AudienceSupport.h"
#include "../../View/AudienceSupportView.h"

void AudienceSupport::use() {
    if (!available) {
        return;
    }

    int chanceOfAnsweringCorrectly = determineChanceOfAnsweringCorrectly();

    for (int i = 0; i < numberOfAudiences; i++) {
        int randomNumber = getRandomNumber(0, 100);

        if (randomNumber >= 0 && randomNumber <= chanceOfAnsweringCorrectly) {
            vote(question->getCorrectAnswer());
        }
        else {
            vote(question->getRandomIncorrectAnswer());
        }
    }

    AudienceSupportView audienceSupportView(answerAVotes, answerBVotes, answerCVotes, answerDVotes);
    audienceSupportView.runAudienceSupportView();
    Lifeline::available = false;

}

int AudienceSupport::determineChanceOfAnsweringCorrectly() {
    if (question->isActiveAnswerA() && question->isActiveAnswerB() &&
        question->isActiveAnswerC() && question->isActiveAnswerD()) {
        switch (question->getQuestionNumber()) {
            case 1:
            case 2:
                return 80;
            case 3:
            case 4:
                return 70;
            case 5:
            case 6:
                return 60;
            case 7:
            case 8:
                return 50;
            case 9:
            case 10:
                return 40;
            case 11:
                return 35;
            case 12:
                return 30;
            default:
                return 50;
        }
    }
    else {
        switch (question->getQuestionNumber()) {
            case 1:
            case 2:
                return 95;
            case 3:
            case 4:
                return 85;
            case 5:
            case 6:
                return 75;
            case 7:
            case 8:
                return 65;
            case 9:
            case 10:
                return 60;
            case 11:
                return 57;
            case 12:
                return 55;
            default:
                return 50;
        }
    }

}

void AudienceSupport::vote(Answer answer) {

    switch(answer) {
        case A:
            answerAVotes++;
            break;
        case B:
            answerBVotes++;
            break;
        case C:
            answerCVotes++;
            break;
        case D:
            answerDVotes++;
            break;
    }
}

void AudienceSupport::reset() {
    answerAVotes = 0;
    answerBVotes = 0;
    answerCVotes = 0;
    answerDVotes = 0;
}
