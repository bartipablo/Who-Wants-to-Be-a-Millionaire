//
// Created by Bartosz Pawłowski on 27/05/2023.
//

#ifndef MILLIONAIRES_PHONETOFRIENDVIEW_H
#define MILLIONAIRES_PHONETOFRIENDVIEW_H

#include "../Model/Lifelines/PhoneToFriend.h"
#include "../Model/GameController.h"

class PhoneToFriendView {
private:
    GameController gameController;

public:
    void runPhoneToFriendView();
};


#endif //MILLIONAIRES_PHONETOFRIENDVIEW_H
