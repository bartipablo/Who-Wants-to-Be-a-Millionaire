#include <iostream>


#include "Model/Lifelines/Lifeline.h"
#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"
#include "Model/Reader.h"
#include "View/StartView.h"
#include "View/PhoneToFriendView.h"
#include "View/AudienceSupportView.h"


int main() {
    StartView startView;
    startView.runStartView();

    //AudienceSupportView audienceSupportView(1, 99, 3, 4);
    //audienceSupportView.runAudienceSupportView();


    return 0;
}

