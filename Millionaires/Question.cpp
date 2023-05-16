//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "Question.h"

std::string Question::getAnswerA() {
    return answerA;
}

std::string Question::getAnswerB() {
    return answerB;
}

std::string Question::getAnswerC() {
    return answerC;
}

std::string Question::getAnswerD() {
    return answerD;
}

int Question::getAmount() const {
    return amount;
}

CorrectAnswer Question::getCorrectAnswer() {
    return correctAnswer;
}

bool Question::isGuaranteedAmount() const {
    return guaranteedAmount;
}

std::string Question::getQuestion() {
    return question;
}

Question::Question(std::string question, std::string answerA, std::string answerB, std::string answerC,
                   std::string answerD, CorrectAnswer correctAnswer, int amount, bool guaranteedAmount) {
    this->question = question;
    this->answerA = answerA;
    this->answerB = answerB;
    this->answerC = answerC;
    this->answerD = answerD;
    this->correctAnswer = correctAnswer;
    this->amount = amount;
    this->guaranteedAmount = guaranteedAmount;
}

