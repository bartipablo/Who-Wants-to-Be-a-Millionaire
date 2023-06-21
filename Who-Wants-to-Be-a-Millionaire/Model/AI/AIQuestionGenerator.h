//
// Created by Bartosz Pawłowski on 20/06/2023.
//

#ifndef WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H
#define WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H

#include <curl/curl.h>
#include "openai.hpp"

class AIQuestionGenerator {


public:

    static std::string generateQuestionByAI();

};


#endif //WHO_WANTS_TO_BE_A_MILLIONAIRE_AIQUESTIONGENERATOR_H
