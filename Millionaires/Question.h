//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_QUESTION_H
#define MILLIONAIRES_QUESTION_H

#include <iostream>

enum CorrectAnswer {
    A,
    B,
    C,
    D
};


class Question {
private:
    std::string question;
    std::string answerA;
    std::string answerB;
    std::string answerC;
    std::string answerD;

    bool guaranteedAmount;

    int amount;

    CorrectAnswer correctAnswer;

public:
    Question(std::string question, std::string answerA, std::string answerB, std::string answerC,
             std::string answerD, CorrectAnswer correctAnswer, int amount, bool guaranteedAmount);

    Question() {};

    std::string getQuestion();

    std::string getAnswerA();

    std::string getAnswerB();

    std::string getAnswerC();

    std::string getAnswerD();

    [[nodiscard]] bool isGuaranteedAmount() const;

    [[nodiscard]] int getAmount() const;

    CorrectAnswer getCorrectAnswer();

};


#endif //MILLIONAIRES_QUESTION_H
