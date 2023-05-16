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
#include <random>
#include <cstdlib>


class Reader {
private:
    static int readAmount(int questionNumber);

    static bool readGuaranteedAmount(int questionNumber);

    static int getRandomNumber(int min, int max);

    static CorrectAnswer readCorrectAnswer(std::string correctAnswerStr);

public:
    static Question getRandomQuestion(int questionNumber);

    static int countLinesInFile(std::string fileName);

};


#endif //MILLIONAIRES_READER_H
