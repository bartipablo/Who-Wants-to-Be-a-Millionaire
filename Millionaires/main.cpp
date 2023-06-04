#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"
#include "Model/Reader.h"
#include "View/StartView.h"
#include "Configuration.h"

int main() {
    StartView startView;

    while (Configuration::programIsRunning()) {
        startView.runStartView();
    }

    return 0;
}

