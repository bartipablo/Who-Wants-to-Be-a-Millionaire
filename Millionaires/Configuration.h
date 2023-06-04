//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#ifndef MILLIONAIRES_CONFIGURATION_H
#define MILLIONAIRES_CONFIGURATION_H


class Configuration {
private:
    static bool runProgram;

    static bool firstRunning;

public:
    static bool programIsRunning();

    static void disableProgram();

    static bool isTheFirstRunning();

    static void disableTheFirstRunning();
};


#endif //MILLIONAIRES_CONFIGURATION_H
