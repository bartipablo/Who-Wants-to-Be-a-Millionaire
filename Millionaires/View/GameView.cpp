//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "GameView.h"

std::string awardsStr[12] = {" 1.      $500", " 2.     $1,000", " 3.     $2,000", " 4.     $5,000", " 5.    $10,000", " 6.    $20,000", " 7.    $50,000",
                          " 8.    $75,000", " 9.   $150,000", "10.  $250,000", "11.  $500,000", "12.$1 MILLION"};

bool nextQuestionFlag = true;

bool musicPlaysFlag = false;

bool answerIsSelected = false;

bool showCorrectAnswer = false;

bool decideAnswerIsCorrect = false;

bool resetAll = false;

void waitForCorrectAnswerFunction() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    showCorrectAnswer = true;
    decideAnswerIsCorrect = true;
}

void waitForNextQuestionFunction(int questionNumber) {
    if (questionNumber == 2 || questionNumber == 7) std::this_thread::sleep_for(std::chrono::seconds(9));
    else std::this_thread::sleep_for(std::chrono::seconds(4));
    resetAll = true;
}


GameView::GameView() {
    //loading from resources:
    prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/game-background.png");
    prepareSprite(&fiftyTexture, &fiftySprite, "./resources/images/lifeline-50.png");
    prepareSprite(&fiftyOrangeTexture, &fiftyOrangeSprite, "./resources/images/lifeline-50-orange.png");
    prepareSprite(&phoneToFriendTexture, &phoneToFriendSprite, "./resources/images/lifeline-phone-a-friend.png");
    prepareSprite(&phoneToFriendOrangeTexture, &phoneToFriendOrangeSprite, "./resources/images/lifeline-phone-a-friend-orange.png");
    prepareSprite(&audienceSupportTexture, &audienceSupportSprite, "./resources/images/lifeline-ask-the-audience.png");
    prepareSprite(&audienceSupportOrangeTexture, &audienceSupportOrangeSprite, "./resources/images/lifeline-ask-the-audience-orange.png");
    prepareSprite(&questionPanelTexture, &questionPanelSprite, "./resources/images/last-question.png");
    prepareSprite(&answerTexture, &answerASprite, "./resources/images/answer.png");
    prepareSprite(&selectedAnswerTexture, &selectedAnswerSprite, "./resources/images/incorrect-answer.png");
    prepareSprite(&correctAnswerTexture, &correctAnswerSprite, "./resources/images/correct-answer.png");
    prepareSprite(&moneyTreeTexture, &moneyTreeSprite, "./resources/images/money-tree.png");
    answerBSprite.setTexture(answerTexture);
    answerCSprite.setTexture(answerTexture);
    answerDSprite.setTexture(answerTexture);

    prepareSound(&gameMusicBuffer1, &gameMusic1, "./resources/sounds/music01.wav");
    prepareSound(&gameMusicBuffer2, &gameMusic2, "./resources/sounds/music02.wav");
    //prepareSound(&gameMusicBuffer3, &gameMusic3, "./resources/sounds/music03.wav");
    prepareSound(&gameMusicBuffer4, &gameMusic4, "./resources/sounds/music04.wav");
    //prepareSound(&gameMusicBuffer5, &gameMusic5, "./resources/sounds/music05.wav");
    //prepareSound(&gameMusicBuffer6, &gameMusic6, "./resources/sounds/music06.wav");
    prepareSound(&gameMusicBuffer7, &gameMusic7, "./resources/sounds/music07.wav");
    prepareSound(&nextQuestionBuffer, &nextQuestionSound, "./resources/sounds/newQuestion.wav");
    prepareSound(&selectAnswerBuffer, &selectAnswerSound, "./resources/sounds/selectAnswer.wav");
    prepareSound(&selectLifeLineBuffer, &selectLifeLineSound, "./resources/sounds/lifeLine.wav");
    prepareSound(&correctAnswerBuffer1, &correctAnswerSound1, "./resources/sounds/correctAnswer1.wav");
    prepareSound(&correctAnswerBuffer2, &correctAnswerSound2, "./resources/sounds/correctAnswer2.wav");
    prepareSound(&incorrectAnswerBuffer, &incorrectAnswerSound, "./resources/sounds/incorrectAnswer.wav");

    View::prepareFont(&font, "./resources/fonts/OpenSans-Bold.ttf");

    for (int i = 0; i < 12; i++) {
        prepareText(&awards[i], awardsStr[i], &font, 50);
    }

    //setting positions
    prepareAwardView();
    prepareLifeLinesView();
    prepareQuestionsAndAnswerPanel();
    prepareSpritesCoordinate();
}

//VIEW-------------------------------------
void GameView::runGameView() {

    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen())
    {
        if (nextQuestionFlag) {
            gameController.loadNextQuestion();
            nextQuestionFlag = false;
            nextQuestionSound.play();
            calculateMoneyTreeCoordinate();
        }

        //music*************************
        if (!musicPlaysFlag) {
            startMusic();
        }
        //music*************************

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    leftMouseClickHandler(mousePosition);
                }
            }
        }
        window.clear();

        window.draw(backgroundSprite);

        //AWARD VIEW
        if (gameController.getQuestionNumber() > 1) {
            window.draw(moneyTreeSprite);
        }

        for (const auto & award : awards) {
            window.draw(award);
        }
        //AWARD VIEW

        //LIFELINES VIEW
        if (gameController.getLifeLineA()->isAvailable()) window.draw(fiftySprite);
        else window.draw(fiftyOrangeSprite);

        if (gameController.getLifeLineB()->isAvailable()) window.draw(phoneToFriendSprite);
        else window.draw(phoneToFriendOrangeSprite);

        if (gameController.getLifeLineC()->isAvailable()) window.draw(audienceSupportSprite);
        else window.draw(audienceSupportOrangeSprite);
        //LIFELINES VIEW

        //QUESTION VIEW
        window.draw(questionPanelSprite);
        //QUESTION VIEW

        //ANSWERS VIEW
        window.draw(answerASprite);
        window.draw(answerBSprite);
        window.draw(answerCSprite);
        window.draw(answerDSprite);

        if (answerIsSelected) window.draw(selectedAnswerSprite);
        if (showCorrectAnswer) window.draw(correctAnswerSprite);
        if (decideAnswerIsCorrect) {
            decideAnswerIsCorrect = false;
            handlingTheSelectedAnswer();
        }

        if(resetAll) handlingTheNextQuestion();

        window.display();
    }
}
//VIEW-------------------------------------



void GameView::prepareAwardView() {
    sf::Vector2f currentScale = awards[0].getScale();
    sf::Vector2f newScale(currentScale.x * 0.75f, currentScale.y * 0.75f);

    for (auto & award : awards) {
        award.setFillColor(sf::Color(255, 140, 0));
        award.setScale(newScale);
    }

    sf::Vector2f  moneyTreeCurrentScale = moneyTreeSprite.getScale();
    sf::Vector2f  newMoneyTreeScale(moneyTreeCurrentScale.x * 0.25f, moneyTreeCurrentScale.y * 0.5f);
    moneyTreeSprite.setScale(newMoneyTreeScale);

    awards[1].setFillColor(sf::Color::White);
    awards[6].setFillColor(sf::Color::White);
    awards[11].setFillColor(sf::Color::White);

    awards[0].setPosition(1930, 990);
    awards[1].setPosition(1930, 900);
    awards[2].setPosition(1930, 810);
    awards[3].setPosition(1930, 720);
    awards[4].setPosition(1930, 630);
    awards[5].setPosition(1930, 540);
    awards[6].setPosition(1930, 450);
    awards[7].setPosition(1930, 360);
    awards[8].setPosition(1930, 270);
    awards[9].setPosition(1930, 180);
    awards[10].setPosition(1930, 90);
    awards[11].setPosition(1930, 0);
}

void GameView::calculateMoneyTreeCoordinate() {
    switch (gameController.getQuestionNumber()) {
        case 2:
            awards[0].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 990-5);
            break;
        case 3:
            awards[0].setFillColor(sf::Color(255, 140, 0));
            awards[1].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 900-5);
            break;
        case 4:
            awards[1].setFillColor(sf::Color::White);
            awards[2].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 810-5);
            break;
        case 5:
            awards[2].setFillColor(sf::Color(255, 140, 0));
            awards[3].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 720-5);
            break;
        case 6:
            awards[3].setFillColor(sf::Color(255, 140, 0));
            awards[4].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 630-5);
            break;
        case 7:
            awards[4].setFillColor(sf::Color(255, 140, 0));
            awards[5].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 540-5);
            break;
        case 8:
            awards[5].setFillColor(sf::Color(255, 140, 0));
            awards[6].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 450-5);
            break;
        case 9:
            awards[6].setFillColor(sf::Color::White);
            awards[7].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 360-5);
            break;
        case 10:
            awards[7].setFillColor(sf::Color(255, 140, 0));
            awards[8].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 270-5);
            break;
        case 11:
            awards[8].setFillColor(sf::Color(255, 140, 0));
            awards[9].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 180-5);
            break;
        case 12:
            awards[9].setFillColor(sf::Color(255, 140, 0));
            awards[10].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930, 90-5);
            break;
        default:
            moneyTreeSprite.setPosition(1930, 990-5);
    }
}

void GameView::prepareLifeLinesView() {
    sf::Vector2f currentScale = fiftySprite.getScale();
    sf::Vector2f newScale(currentScale.x * 0.8f, currentScale.y * 0.8f);

    fiftySprite.setScale(newScale);
    fiftySprite.setPosition(1960, 1110);

    fiftyOrangeSprite.setScale(newScale);
    fiftyOrangeSprite.setPosition(1960, 1110);

    phoneToFriendSprite.setScale(newScale);
    phoneToFriendSprite.setPosition(1960, 1260);

    phoneToFriendOrangeSprite.setScale(newScale);
    phoneToFriendOrangeSprite.setPosition(1960, 1260);

    audienceSupportSprite.setScale(newScale);
    audienceSupportSprite.setPosition(1960, 1410);

    audienceSupportOrangeSprite.setScale(newScale);
    audienceSupportOrangeSprite.setPosition(1960, 1410);
}


void GameView::prepareQuestionsAndAnswerPanel() {
    sf::Vector2f questionCurrentScale = questionPanelSprite.getScale();
    sf::Vector2f newQuestionScale(questionCurrentScale.x * 0.9f, questionCurrentScale.y * 0.9f);

    questionPanelSprite.setScale(newQuestionScale);
    questionPanelSprite.setPosition(70, 1050);

    sf::Vector2f answerCurrentScale = questionPanelSprite.getScale();
    sf::Vector2f newAnswerScale(answerCurrentScale.x * 0.64f, answerCurrentScale.y * 1.0f);

    correctAnswerSprite.setScale(newAnswerScale);
    selectedAnswerSprite.setScale(newAnswerScale);

    answerASprite.setScale(newAnswerScale);
    answerBSprite.setScale(newAnswerScale);
    answerCSprite.setScale(newAnswerScale);
    answerDSprite.setScale(newAnswerScale);

    answerASprite.setPosition(70, 1290);
    answerBSprite.setPosition(980, 1290);
    answerCSprite.setPosition(70, 1420);
    answerDSprite.setPosition(980, 1420);

    switch(gameController.getQuestion().getCorrectAnswer()) {
        case A:
            correctAnswerSprite.setPosition(70, 1290);
            break;
        case B:
            correctAnswerSprite.setPosition(980, 1290);
            break;
        case C:
            correctAnswerSprite.setPosition(70, 1420);
            break;
        case D:
            correctAnswerSprite.setPosition(980, 1420);
            break;
    }
}


void GameView::startMusic() {
    gameMusic1.stop();
    gameMusic2.stop();
    gameMusic3.stop();
    gameMusic4.stop();
    gameMusic5.stop();
    gameMusic6.stop();
    gameMusic7.stop();

    switch (gameController.getQuestionNumber()) {
        case 1:
        case 2:
            gameMusic1.play();
            gameMusic1.setLoop(true);
            break;
        case 3:
        case 4:
            gameMusic1.play();
            gameMusic1.setLoop(true);
            break;
        case 5:
        case 6:
            gameMusic1.play();
            gameMusic1.setLoop(true);
            break;
        case 7:
        case 8:
        case 9:
            gameMusic2.play();
            gameMusic2.setLoop(true);
            break;
        case 10:
        case 11:
            gameMusic4.play();
            gameMusic4.setLoop(true);
            break;
        case 12:
            gameMusic7.play();
            gameMusic7.setLoop(true);
            break;
        default:
            gameMusic1.play();
            gameMusic1.setLoop(true);
    }
    musicPlaysFlag = true;
}


void GameView::prepareSpritesCoordinate() {
    fiftySpriteCoordinate = getSpriteCoordinate(fiftySprite);
    phoneToFriendSpriteCoordinate = getSpriteCoordinate(phoneToFriendSprite);
    audienceSupportSpriteCoordinate = getSpriteCoordinate(audienceSupportSprite);
    answerASpriteCoordinate = getSpriteCoordinate(answerASprite);
    answerBSpriteCoordinate = getSpriteCoordinate(answerBSprite);
    answerCSpriteCoordinate = getSpriteCoordinate(answerCSprite);
    answerDSpriteCoordinate = getSpriteCoordinate(answerDSprite);

}

SpriteCoordinate GameView::getSpriteCoordinate(sf::Sprite sprite) {
    SpriteCoordinate result;
    result.spritePosition = sprite.getPosition();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::Vector2f spriteSize(spriteBounds.width, spriteBounds.height);
    result.spriteSize = spriteSize;
    return result;
}

void GameView::leftMouseClickHandler(sf::Vector2i mousePosition) {
    if (answerIsSelected) return;

    if (mousePosition.x >= answerASpriteCoordinate.spritePosition.x && mousePosition.x < answerASpriteCoordinate.spritePosition.x + answerASpriteCoordinate.spriteSize.x &&
        mousePosition.y >= answerASpriteCoordinate.spritePosition.y && mousePosition.y < answerASpriteCoordinate.spritePosition.y + answerASpriteCoordinate.spriteSize.y)
    {
        answerAButtonHandler();
    }

    else if (mousePosition.x >= answerBSpriteCoordinate.spritePosition.x && mousePosition.x < answerBSpriteCoordinate.spritePosition.x + answerBSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= answerBSpriteCoordinate.spritePosition.y && mousePosition.y < answerBSpriteCoordinate.spritePosition.y + answerBSpriteCoordinate.spriteSize.y)
    {
        answerBButtonHandler();
    }

    else if (mousePosition.x >= answerCSpriteCoordinate.spritePosition.x && mousePosition.x < answerCSpriteCoordinate.spritePosition.x + answerCSpriteCoordinate.spriteSize.x &&
             mousePosition.y >= answerCSpriteCoordinate.spritePosition.y && mousePosition.y < answerCSpriteCoordinate.spritePosition.y + answerCSpriteCoordinate.spriteSize.y)
    {
        answerCButtonHandler();
    }

    else if (mousePosition.x >= answerDSpriteCoordinate.spritePosition.x && mousePosition.x < answerDSpriteCoordinate.spritePosition.x + answerDSpriteCoordinate.spriteSize.x &&
             mousePosition.y >= answerDSpriteCoordinate.spritePosition.y && mousePosition.y < answerDSpriteCoordinate.spritePosition.y + answerDSpriteCoordinate.spriteSize.y)
    {
        answerDButtonHandler();
    }

    else if (mousePosition.x >= fiftySpriteCoordinate.spritePosition.x && mousePosition.x < fiftySpriteCoordinate.spritePosition.x + fiftySpriteCoordinate.spriteSize.x &&
        mousePosition.y >= fiftySpriteCoordinate.spritePosition.y && mousePosition.y < fiftySpriteCoordinate.spritePosition.y + fiftySpriteCoordinate.spriteSize.y)
    {
        lifeLineAButtonHandler();
    }

    else if (mousePosition.x >= phoneToFriendSpriteCoordinate.spritePosition.x && mousePosition.x < phoneToFriendSpriteCoordinate.spritePosition.x + phoneToFriendSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= phoneToFriendSpriteCoordinate.spritePosition.y && mousePosition.y < phoneToFriendSpriteCoordinate.spritePosition.y + phoneToFriendSpriteCoordinate.spriteSize.y)
    {
        lifeLineBButtonHandler();
    }

    else if (mousePosition.x >= audienceSupportSpriteCoordinate.spritePosition.x && mousePosition.x < audienceSupportSpriteCoordinate.spritePosition.x + audienceSupportSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= audienceSupportSpriteCoordinate.spritePosition.y && mousePosition.y < audienceSupportSpriteCoordinate.spritePosition.y + audienceSupportSpriteCoordinate.spriteSize.y)
    {
        lifeLineCButtonHandler();
    }
}


void GameView::answerAButtonHandler() {
    selectedAnswerSprite.setPosition(70, 1290);
    answerIsSelected = true;
    selectAnswerSound.play();
    gameController.setSelectedAnswer(A);
    if (gameController.getQuestionNumber() > 1) waitForCorrectAnswer.join();
    waitForCorrectAnswer = std::thread(waitForCorrectAnswerFunction);
}


void GameView::answerBButtonHandler() {
    selectedAnswerSprite.setPosition(980, 1290);
    answerIsSelected = true;
    selectAnswerSound.play();
    gameController.setSelectedAnswer(B);
    if (gameController.getQuestionNumber() > 1) waitForCorrectAnswer.join();
    waitForCorrectAnswer = std::thread(waitForCorrectAnswerFunction);

}


void GameView::answerCButtonHandler() {
    selectedAnswerSprite.setPosition(70, 1420);
    answerIsSelected = true;
    selectAnswerSound.play();
    gameController.setSelectedAnswer(C);
    if (gameController.getQuestionNumber() > 1) waitForCorrectAnswer.join();
    waitForCorrectAnswer = std::thread(waitForCorrectAnswerFunction);

}

void GameView::answerDButtonHandler() {
    selectedAnswerSprite.setPosition(980, 1420);
    answerIsSelected = true;
    selectAnswerSound.play();
    gameController.setSelectedAnswer(D);
    if (gameController.getQuestionNumber() > 1) waitForCorrectAnswer.join();
    waitForCorrectAnswer = std::thread(waitForCorrectAnswerFunction);
}


void GameView::lifeLineAButtonHandler() {
    if (!gameController.getLifeLineA()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineA()->deactivate();
}

void GameView::lifeLineBButtonHandler() {
    if (!gameController.getLifeLineB()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineB()->deactivate();

}

void GameView::lifeLineCButtonHandler() {
    if (!gameController.getLifeLineC()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineC()->deactivate();

}

void GameView::handlingTheSelectedAnswer() {
    if (gameController.getSelectedAnswer() == gameController.getQuestion().getCorrectAnswer()) {
        switch(gameController.getQuestionNumber()) {
            case 2:
            case 7:
                correctAnswerSound2.play();
                break;
            default:
                correctAnswerSound1.play();
        }
        waitForCorrectAnswer.join();
        waitForCorrectAnswer = std::thread(waitForNextQuestionFunction, gameController.getQuestionNumber());
    }

    else {
        incorrectAnswerSound.play();
        gameMusic1.stop();
    }
}

void GameView::handlingTheNextQuestion() {
    nextQuestionFlag = true;
    musicPlaysFlag = false;
    answerIsSelected = false;
    showCorrectAnswer = false;
    decideAnswerIsCorrect = false;
    resetAll = false;
}
