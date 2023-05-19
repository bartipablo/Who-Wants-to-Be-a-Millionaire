//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_QUESTION_H
#define MILLIONAIRES_QUESTION_H

#include <vector>
#include <iostream>
#include "../Functions/Answer.h"
#include "../Functions/Random.h"


class Question {
private:
    std::string question;
    std::string answerA;
    std::string answerB;
    std::string answerC;
    std::string answerD;

    bool activeAnswerA;
    bool activeAnswerB;
    bool activeAnswerC;
    bool activeAnswerD;

    bool guaranteedAmount;

    int amount;

    int questionNumber;

    Answer correctAnswer;

public:
    Question(std::string question, std::string answerA, std::string answerB, std::string answerC,
             std::string answerD, Answer correctAnswer, int amount, bool guaranteedAmount, int questionNumber);

    Question() {};

    std::string getQuestion();

    std::string getAnswerA();

    std::string getAnswerB();

    std::string getAnswerC();

    std::string getAnswerD();

    bool isActiveAnswerA();

    bool isActiveAnswerB();

    bool isActiveAnswerC();

    bool isActiveAnswerD();

    void deactivateAnswerA();

    void deactivateAnswerB();

    void deactivateAnswerC();

    void deactivateAnswerD();

    [[nodiscard]] bool isGuaranteedAmount() const;

    [[nodiscard]] int getAmount() const;

    Answer getCorrectAnswer();

    Answer getRandomIncorrectAnswer();

    std::vector<Answer> getIncorrectActiveAnswers();

    std::vector<Answer> getActiveAnswers();

};


#endif //MILLIONAIRES_QUESTION_H
