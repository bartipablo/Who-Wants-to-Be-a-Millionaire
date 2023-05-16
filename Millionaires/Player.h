//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_PLAYER_H
#define MILLIONAIRES_PLAYER_H

#include <iostream>


class Player {
private:
    std::string userName;

    int award;

    int playingTime;

public:
    std::string getUserName();

};


#endif //MILLIONAIRES_PLAYER_H
