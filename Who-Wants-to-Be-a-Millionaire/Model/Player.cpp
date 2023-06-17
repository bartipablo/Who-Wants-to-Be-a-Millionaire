//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "Player.h"

#include <utility>


Player::Player(std::string userName, int award, int playingTime) {
    this->userName = std::move(userName);
    this->award = award;
    this->playingTime = playingTime;
}

std::string Player::getUserName() {
    return userName;
}

int Player::getAward() const {
    return award;
}

int Player::getPlayingTime() const {
    return playingTime;
}

