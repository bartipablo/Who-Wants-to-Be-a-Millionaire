//
// Created by Bartosz Pawłowski on 16/05/2023.
//


#include "Reader.h"

int Reader::readAward(int questionNumber) {
    switch(questionNumber) {
        case 1:
            return 500;
        case 2:
            return 1000;
        case 3:
            return 2000;
        case 4:
            return 5000;
        case 5:
            return 10000;
        case 6:
            return 20000;
        case 7:
            return 40000;
        case 8:
            return 75000;
        case 9:
            return 125000;
        case 10:
            return 250000;
        case 11:
            return 500000;
        case 12:
            return 1000000;
        default:
            return 0;
    }
}

bool Reader::readGuaranteedAward(int questionNumber) {
    switch(questionNumber) {
        case 2:
        case 7:
            return true;
        default:
            return false;
    }
}


int Reader::countLinesInFile(std::string fileName) {
    std::ifstream file(fileName);

    int lineCount = 0;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lineCount++;
        }
        file.close();
    } else {
        std::cout << "ERROR: Could not open " << fileName << "\n";
    }

    return lineCount;
}

Question Reader::getRandomQuestion(int questionNumber) {
    std::ostringstream oss;
    oss << questionNumber;
    std::string fileName = "question" + oss.str() + ".csv";

    std::ifstream file(fileName);

    if (file.is_open()) {
        int questionDrawn = getRandomNumber(1, countLinesInFile(fileName));
        std::string readLine;

        for (int i = 0; i < questionDrawn; i++) {
            std::getline(file, readLine);
        }

        std::stringstream ss(readLine);

        std::string question;
        std::string answerA;
        std::string answerB;
        std::string answerC;
        std::string answerD;
        std::string correctAnswerString;


        std::getline(ss, question, ',');
        std::getline(ss, answerA, ',');
        std::getline(ss, answerB, ',');
        std::getline(ss, answerC, ',');
        std::getline(ss, answerD, ',');
        std::getline(ss, correctAnswerString, ',');

        file.close();

        return Question(question, answerA, answerB, answerC,
                        answerD, readCorrectAnswer(correctAnswerString),
                        readAward(questionNumber), readGuaranteedAward(questionNumber));
    } else {
        std::cout << "ERROR: Could not open " << fileName << "\n";
        return Question();
    }
}

Answer Reader::readCorrectAnswer(std::string correctAnswerStr) {
    char correctAnswerNumber = correctAnswerStr[0];
    switch(correctAnswerNumber) {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        case 'D':
            return D;
        default:
            return A;
    }
}





