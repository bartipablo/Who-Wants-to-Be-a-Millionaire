#include <iostream>


#include "Model/Lifelines/Lifeline.h"
#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"
#include "Model/Reader.h"
#include "View/StartView.h"
#include "View/PhoneToFriendView.h"
#include "View/AudienceSupportView.h"
#include "View/WinnerView.h"
#include "Configuration.h"

int main() {
    StartView startView;

    while (Configuration::programIsRunning()) {
        startView.runStartView();
    }

    return 0;
}

