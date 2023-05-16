//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_LIFELINES_H
#define MILLIONAIRES_LIFELINES_H


class Lifelines {

private:
    bool availableFiftyFifty;

    bool availablePhoneToFriend;

    bool availableAskTheAudience;

public:
    [[nodiscard]] bool isAvailableFiftyFifty() const;

    [[nodiscard]] bool isAvailablePhoneToFriend() const;

    [[nodiscard]] bool isAvailableAskTheAudience() const;

    void setAvailableFiftyFifty(bool availability);

    void setAvailablePhoneToFriend(bool availability);

    void setAvailableAskTheAudience(bool availability);

};


#endif //MILLIONAIRES_LIFELINES_H
