//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "Lifelines.h"

bool Lifelines::isAvailableFiftyFifty() const {
    return availableFiftyFifty;
}

bool Lifelines::isAvailablePhoneToFriend() const {
    return availablePhoneToFriend;
}

bool Lifelines::isAvailableAskTheAudience() const {
    return availableAskTheAudience;
}

void Lifelines::setAvailableFiftyFifty(bool availability) {
    this->availableFiftyFifty = availability;
}

void Lifelines::setAvailablePhoneToFriend(bool availability) {
    this->availablePhoneToFriend = availability;
}

void Lifelines::setAvailableAskTheAudience(bool availability) {
    this->availableAskTheAudience = availability;
}

