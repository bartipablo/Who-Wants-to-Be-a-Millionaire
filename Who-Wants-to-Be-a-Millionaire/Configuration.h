//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#ifndef MILLIONAIRES_CONFIGURATION_H
#define MILLIONAIRES_CONFIGURATION_H

#include <SFML/Graphics.hpp>

class Configuration {
private:
    static bool generateQuestionByAI;

    static bool runProgram;

    static bool firstRunning;

    static double getResolutionFactor();

public:
    static bool isSetGenerateQuestionByAI();

    static bool programIsRunning();

    static void disableProgram();

    static bool isTheFirstRunning();

    static void disableTheFirstRunning();

    static void setGeneratingQuestionByAI(bool flag);

    static double resolutionFactor;

};


#endif //MILLIONAIRES_CONFIGURATION_H
