//
// Created by Bartosz Pawłowski on 20/06/2023.
//

#ifndef WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H
#define WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H

#include <curl/curl.h>
#include "openai.hpp"
#include <iostream>
#include <fstream>
#include <string>

class AIQuestionGenerator {


public:

    static std::string generateQuestionByAI();

    static std::string readKey();

};


#endif //WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H
