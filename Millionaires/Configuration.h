//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#ifndef MILLIONAIRES_CONFIGURATION_H
#define MILLIONAIRES_CONFIGURATION_H


class Configuration {
private:
    static bool runProgram;

public:
    static bool programIsRunning();

    static void disableProgram();
};


#endif //MILLIONAIRES_CONFIGURATION_H
