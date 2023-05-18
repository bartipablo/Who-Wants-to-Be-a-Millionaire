#include <iostream>


#include "Model/Lifelines/Lifeline.h"
#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"
#include "View/StartView.h"



int main() {
    StartView startView;
    startView.runStartView();
    //GameView gameView;
    //gameView.runGameView();

    //std::chrono::seconds sleepDuration(100);
    //std::this_thread::sleep_for(sleepDuration);

    std::cout << "Program po uśpieniu." << std::endl;
    return 0;
}

