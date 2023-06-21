//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#include "Configuration.h"

bool Configuration::generateQuestionByAI = false;


bool Configuration::runProgram = true;


bool Configuration::firstRunning = true;


double Configuration::resolutionFactor = getResolutionFactor();


bool Configuration::programIsRunning() {
    return runProgram;
}

void Configuration::disableProgram() {
    runProgram = false;
}

bool Configuration::isTheFirstRunning() {
    return firstRunning;
}

void Configuration::disableTheFirstRunning() {
    firstRunning = false;
}

double Configuration::getResolutionFactor() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float result = std::min(static_cast<float>(desktopMode.height) / 1600.0f, static_cast<float>(desktopMode.width) / 2200.0f) * 0.90;
    return result*0.95;
}

bool Configuration::isSetGenerateQuestionByAI() {
    return generateQuestionByAI;
}

void Configuration::setGeneratingQuestionByAI(bool flag) {
    generateQuestionByAI = flag;
}
