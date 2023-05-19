//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_LIFELINE_H
#define MILLIONAIRES_LIFELINE_H


class Lifeline {
protected:
    bool available;

public:
    explicit Lifeline(bool available) {
        this->available = available;
    }

    [[nodiscard]] bool isAvailable() const {
        return available;
    }

    void deactivate() {
        this->available = false;
    }

    virtual void use() = 0;

};


#endif //MILLIONAIRES_LIFELINE_H
