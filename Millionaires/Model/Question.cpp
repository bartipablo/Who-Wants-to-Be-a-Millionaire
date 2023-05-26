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

bool Question::isActiveAnswerA() {
    return activeAnswerA;
}

bool Question::isActiveAnswerB() {
    return activeAnswerB;
}

bool Question::isActiveAnswerC() {
    return activeAnswerC;
}

bool Question::isActiveAnswerD() {
    return activeAnswerD;
}

void Question::deactivateAnswerA() {
    activeAnswerA = false;
}

void Question::deactivateAnswerB() {
    activeAnswerB = false;
}

void Question::deactivateAnswerC() {
    activeAnswerC = false;
}

void Question::deactivateAnswerD() {
    activeAnswerD = false;
}

int Question::getAmount() const {
    return amount;
}

Answer Question::getCorrectAnswer() {
    return correctAnswer;
}

bool Question::isGuaranteedAmount() const {
    return guaranteedAmount;
}

std::string Question::getQuestion() {
    return question;
}

Question::Question(std::string question, std::string answerA, std::string answerB, std::string answerC,
                   std::string answerD, Answer correctAnswer, int amount, bool guaranteedAmount, int questionNumber) {
    this->question = question;
    this->answerA = answerA;
    this->answerB = answerB;
    this->answerC = answerC;
    this->answerD = answerD;
    this->correctAnswer = correctAnswer;
    this->amount = amount;
    this->guaranteedAmount = guaranteedAmount;
    this->questionNumber = questionNumber;
    this->activeAnswerA = true;
    this->activeAnswerB = true;
    this->activeAnswerC = true;
    this->activeAnswerD = true;
}

Answer Question::getRandomIncorrectAnswer() {
    std::vector <Answer> incorrectAnswers = getIncorrectActiveAnswers();
    int randomNumber = getRandomNumber(0, incorrectAnswers.size() - 1);
    return incorrectAnswers[randomNumber];
}


std::vector<Answer> Question::getIncorrectActiveAnswers() {
    std::vector <Answer> incorrectAnswers;

    if (correctAnswer != A && activeAnswerA) incorrectAnswers.push_back(A);
    if (correctAnswer != B && activeAnswerB) incorrectAnswers.push_back(B);
    if (correctAnswer != C && activeAnswerC) incorrectAnswers.push_back(C);
    if (correctAnswer != D && activeAnswerD) incorrectAnswers.push_back(D);
    return incorrectAnswers;
}

std::vector<Answer> Question::getActiveAnswers() {
    std::vector <Answer> answers;

    if (activeAnswerA) answers.push_back(A);
    if (activeAnswerB) answers.push_back(B);
    if (activeAnswerC) answers.push_back(C);
    if (activeAnswerD) answers.push_back(D);
    return answers;
}



