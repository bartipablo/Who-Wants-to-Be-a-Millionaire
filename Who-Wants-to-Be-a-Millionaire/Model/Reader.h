//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_READER_H
#define MILLIONAIRES_READER_H

#include "Question.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

class Reader {
private:
    static int readAward(int questionNumber);

    static bool readGuaranteedAward(int questionNumber);

    static Answer readCorrectAnswer(std::string correctAnswerStr);

    static void shuffleAnswers(std::string& answerStrA, std::string& answerStrB, std::string& answerStrC,
                               std::string& answerStrD, std::string& correctAnswerStr);

public:
    static Question getRandomQuestion(int questionNumber);

    static int countLinesInFile(std::string fileName);

};

#endif //MILLIONAIRES_READER_H
