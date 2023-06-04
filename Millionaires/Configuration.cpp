//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#include "Configuration.h"

bool Configuration::runProgram = true;


bool Configuration::programIsRunning() {
    return runProgram;
}

void Configuration::disableProgram() {
    runProgram = false;
}
