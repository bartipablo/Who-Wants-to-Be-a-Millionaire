//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#include "Configuration.h"

bool Configuration::runProgram = true;


bool Configuration::firstRunning = true;


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
