#include <iostream>


#include "Model/Lifelines/Lifeline.h"
#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"
#include "Model/Reader.h"
#include "View/StartView.h"
#include "View/PhoneToFriendView.h"

int main() {
    StartView startView;
    startView.runStartView();

    //Reader reader;
    //Question question = reader.getRandomQuestion(1);
    //PhoneToFriendView phoneToFriendView(&question, "elo");
    //phoneToFriendView.runPhoneToFriendView();


    return 0;
}

