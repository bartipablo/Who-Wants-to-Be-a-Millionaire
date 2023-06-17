//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_WRITER_H
#define MILLIONAIRES_WRITER_H

#include <fstream>
#include <iostream>
#include <string>

class Writer {
public:
    static void savePlayerResult(std::string userName, int award, int playingTime);
};


#endif //MILLIONAIRES_WRITER_H
