#include <iostream>
#include "Question.h"

#include "Writer.h"
#include "Reader.h"


void question_TEST() {
    Question question = Reader::getRandomQuestion(1);
    std::cout << question.getQuestion() << std::endl;
    std::cout << question.getAnswerA() << std::endl;
    std::cout << question.getAnswerB() << std::endl;
    std::cout << question.getAnswerC() << std::endl;
    std::cout << question.getAnswerD() << std::endl;
    std::cout << question.getCorrectAnswer() << std::endl;
    std::cout << question.getAmount() << std::endl;
    std::cout << question.isGuaranteedAmount() << std::endl;
}

int main() {
    question_TEST();
    return 0;
}

