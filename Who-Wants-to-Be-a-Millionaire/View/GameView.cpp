//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include <codecvt>
#include "GameView.h"

/**************************************
        FUNCTION TO THREADS
 **************************************/
void GameView::waitForCorrectAnswerAfterSelectedAnswer() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    showCorrectAnswer = true;
    decideAnswerIsCorrect = true;
}


void GameView::waitForSumUpAfterChosenAnswer() {
    stopMusics();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    winningSound2.play();
    sumUp = true;
}


void GameView::waitForNextQuestionAfterSelectedAnswer() {
    int questionNumber = gameController.getQuestionNumber();
    if (questionNumber == 2 || questionNumber == 7) std::this_thread::sleep_for(std::chrono::seconds(9));
    else if (questionNumber == 12) std::this_thread::sleep_for(std::chrono::seconds(12));
    else std::this_thread::sleep_for(std::chrono::seconds(4));
    resetAll = true;
}
/**************************************
        ~FUNCTION TO THREADS
 **************************************/


/**************************************
        VIEW
 **************************************/
void GameView::runGameView() {

    sf::RenderWindow window(sf::VideoMode(2200 * Configuration::resolutionFactor, 1600 * Configuration::resolutionFactor), "Who want to be a millionaire?");

    backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    while (window.isOpen())
    {
        if (sumUp) {
            window.close();
            WinnerView winnerView(winAmount);
            winnerView.runWinnerView();
            return;
        }

        if (nextQuestionFlag) {
            gameController.loadNextQuestion();
            prepareQuestionView();
            prepareAnswerView();
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
            if (event.type == sf::Event::Closed) {
                try {
                    waitForCorrectAnswerThread.join();
                } catch (const std::exception& e) {
                    //std::cout << "Exception: " << e.what() << std::endl;
                }
                try {
                    waitForSumUpThread.join();
                } catch (const std::exception& e) {
                    //std::cout << "Exception: " << e.what() << std::endl;
                }
                window.close();
                Configuration::disableProgram();
                return;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    leftMouseClickHandler(mousePosition);
                }
            }
        }
        window.clear();

        window.draw(backgroundSprite);

        window.draw(resignButtonSprite);
        window.draw(resignText);

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
        window.draw(questionText[0]);
        window.draw(questionText[1]);
        window.draw(questionText[2]);
        //QUESTION VIEW

        //ANSWERS SPRITE VIEW
        window.draw(answerASprite);
        window.draw(answerBSprite);
        window.draw(answerCSprite);
        window.draw(answerDSprite);
        //ANSWERS SPRITE VIEW

        if (answerIsSelected) window.draw(selectedAnswerSprite);
        if (showCorrectAnswer) window.draw(correctAnswerSprite);

        //ANSWERS TEXT VIEW
        if (gameController.getQuestion().isActiveAnswerA()) window.draw(answerA);
        if (gameController.getQuestion().isActiveAnswerB()) window.draw(answerB);
        if (gameController.getQuestion().isActiveAnswerC()) window.draw(answerC);
        if (gameController.getQuestion().isActiveAnswerD()) window.draw(answerD);
        //ANSWERS TEXT VIEW

        if (decideAnswerIsCorrect) {
            decideAnswerIsCorrect = false;
            handlingTheSelectedAnswer();
        }

        if(resetAll) handlingTheNextQuestion();

        window.display();
    }
}
/**************************************
        ~VIEW
 **************************************/


/**************************************
        VIEW PREPARING AND SERVICE
 **************************************/
GameView::GameView() {
    //loading from resources:
    prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/game-background.png");
    prepareSprite(&fiftyTexture, &fiftySprite, "../resources/images/lifeline-50.png");
    prepareSprite(&fiftyOrangeTexture, &fiftyOrangeSprite, "../resources/images/lifeline-50-orange.png");
    prepareSprite(&phoneToFriendTexture, &phoneToFriendSprite, "../resources/images/lifeline-phone-a-friend.png");
    prepareSprite(&phoneToFriendOrangeTexture, &phoneToFriendOrangeSprite, "../resources/images/lifeline-phone-a-friend-orange.png");
    prepareSprite(&audienceSupportTexture, &audienceSupportSprite, "../resources/images/lifeline-ask-the-audience.png");
    prepareSprite(&audienceSupportOrangeTexture, &audienceSupportOrangeSprite, "../resources/images/lifeline-ask-the-audience-orange.png");
    prepareSprite(&questionPanelTexture, &questionPanelSprite, "../resources/images/last-question.png");
    prepareSprite(&answerTexture, &answerASprite, "../resources/images/answer.png");
    prepareSprite(&selectedAnswerTexture, &selectedAnswerSprite, "../resources/images/incorrect-answer.png");
    prepareSprite(&correctAnswerTexture, &correctAnswerSprite, "../resources/images/correct-answer.png");
    prepareSprite(&moneyTreeTexture, &moneyTreeSprite, "../resources/images/money-tree.png");
    answerBSprite.setTexture(answerTexture);
    answerCSprite.setTexture(answerTexture);
    answerDSprite.setTexture(answerTexture);

    prepareSound(&gameMusicBuffer1, &gameMusic1, "../resources/sounds/music01.flac");
    prepareSound(&gameMusicBuffer2, &gameMusic2, "../resources/sounds/music02.flac");
    prepareSound(&gameMusicBuffer3, &gameMusic3, "../resources/sounds/music03.flac");
    prepareSound(&gameMusicBuffer4, &gameMusic4, "../resources/sounds/music04.flac");
    prepareSound(&nextQuestionBuffer, &nextQuestionSound, "../resources/sounds/newQuestion.flac");
    prepareSound(&selectAnswerBuffer, &selectAnswerSound, "../resources/sounds/selectAnswer.flac");
    prepareSound(&selectLifeLineBuffer, &selectLifeLineSound, "../resources/sounds/lifeLine.flac");
    prepareSound(&correctAnswerBuffer1, &correctAnswerSound1, "../resources/sounds/correctAnswer1.flac");
    prepareSound(&correctAnswerBuffer2, &correctAnswerSound2, "../resources/sounds/correctAnswer2.flac");
    prepareSound(&incorrectAnswerBuffer, &incorrectAnswerSound, "../resources/sounds/incorrectAnswer.flac");
    prepareSound(&winningBuffer1, &winningSound1, "../resources/sounds/Winning2.flac");
    prepareSound(&winningBuffer2, &winningSound2, "../resources/sounds/Winning1.flac");

    View::prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");

    for (int i = 0; i < 12; i++) {
        prepareText(&awards[i], awardsStr[i], &font, 50);
    }

    prepareSprite(&resignButtonTexture, &resignButtonSprite, "../resources/images/incorrect-answer.png");
    prepareText(&resignText, "resign", &font, 50 * Configuration::resolutionFactor);
    resignButtonCoordinate = getSpriteCoordinate(resignButtonSprite);


    scale();

    //setting positions
    prepareAwardView();
    prepareLifeLinesView();
    prepareQuestionsAndAnswerPanel();
    prepareSpritesCoordinate();
    prepareResignButton();

    icon.loadFromFile("../resources/images/icon.png");
}


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

    awards[0].setPosition(1930 * Configuration::resolutionFactor, 990 * Configuration::resolutionFactor);
    awards[1].setPosition(1930 * Configuration::resolutionFactor, 900 * Configuration::resolutionFactor);
    awards[2].setPosition(1930 * Configuration::resolutionFactor, 810 * Configuration::resolutionFactor);
    awards[3].setPosition(1930 * Configuration::resolutionFactor, 720 * Configuration::resolutionFactor);
    awards[4].setPosition(1930 * Configuration::resolutionFactor, 630 * Configuration::resolutionFactor);
    awards[5].setPosition(1930 * Configuration::resolutionFactor, 540 * Configuration::resolutionFactor);
    awards[6].setPosition(1930 * Configuration::resolutionFactor, 450 * Configuration::resolutionFactor);
    awards[7].setPosition(1930 * Configuration::resolutionFactor, 360 * Configuration::resolutionFactor);
    awards[8].setPosition(1930 * Configuration::resolutionFactor, 270 * Configuration::resolutionFactor);
    awards[9].setPosition(1930 * Configuration::resolutionFactor, 180 * Configuration::resolutionFactor);
    awards[10].setPosition(1930 * Configuration::resolutionFactor, 90 * Configuration::resolutionFactor);
    awards[11].setPosition(1930 * Configuration::resolutionFactor, 0 * Configuration::resolutionFactor);
}


void GameView::calculateMoneyTreeCoordinate() {
    switch (gameController.getQuestionNumber()) {
        case 2:
            awards[0].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930  * Configuration::resolutionFactor, (990-5)  * Configuration::resolutionFactor);
            break;
        case 3:
            awards[0].setFillColor(sf::Color(255, 140, 0));
            awards[1].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930  * Configuration::resolutionFactor, (900-5)  * Configuration::resolutionFactor);
            break;
        case 4:
            awards[1].setFillColor(sf::Color::White);
            awards[2].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930  * Configuration::resolutionFactor, (810-5)  * Configuration::resolutionFactor);
            break;
        case 5:
            awards[2].setFillColor(sf::Color(255, 140, 0));
            awards[3].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (720-5) * Configuration::resolutionFactor);
            break;
        case 6:
            awards[3].setFillColor(sf::Color(255, 140, 0));
            awards[4].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (630-5) * Configuration::resolutionFactor);
            break;
        case 7:
            awards[4].setFillColor(sf::Color(255, 140, 0));
            awards[5].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (540-5) * Configuration::resolutionFactor);
            break;
        case 8:
            awards[5].setFillColor(sf::Color(255, 140, 0));
            awards[6].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (450-5) * Configuration::resolutionFactor);
            break;
        case 9:
            awards[6].setFillColor(sf::Color::White);
            awards[7].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (360-5) * Configuration::resolutionFactor);
            break;
        case 10:
            awards[7].setFillColor(sf::Color(255, 140, 0));
            awards[8].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (270-5) * Configuration::resolutionFactor);
            break;
        case 11:
            awards[8].setFillColor(sf::Color(255, 140, 0));
            awards[9].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (180-5) * Configuration::resolutionFactor);
            break;
        case 12:
            awards[9].setFillColor(sf::Color(255, 140, 0));
            awards[10].setFillColor(sf::Color::Black);
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (90-5) * Configuration::resolutionFactor);
            break;
        default:
            moneyTreeSprite.setPosition(1930 * Configuration::resolutionFactor, (990-5) * Configuration::resolutionFactor);
    }
}


void GameView::prepareLifeLinesView() {
    sf::Vector2f currentScale = fiftySprite.getScale();
    sf::Vector2f newScale(currentScale.x * 0.8f, currentScale.y * 0.8f);

    fiftySprite.setScale(newScale);
    fiftySprite.setPosition(1960 * Configuration::resolutionFactor, 1110 * Configuration::resolutionFactor);

    fiftyOrangeSprite.setScale(newScale);
    fiftyOrangeSprite.setPosition(1960 * Configuration::resolutionFactor, 1110 * Configuration::resolutionFactor);

    phoneToFriendSprite.setScale(newScale);
    phoneToFriendSprite.setPosition(1960 * Configuration::resolutionFactor, 1260 * Configuration::resolutionFactor);

    phoneToFriendOrangeSprite.setScale(newScale);
    phoneToFriendOrangeSprite.setPosition(1960 * Configuration::resolutionFactor, 1260 * Configuration::resolutionFactor);

    audienceSupportSprite.setScale(newScale);
    audienceSupportSprite.setPosition(1960 * Configuration::resolutionFactor, 1410 * Configuration::resolutionFactor);

    audienceSupportOrangeSprite.setScale(newScale);
    audienceSupportOrangeSprite.setPosition(1960 * Configuration::resolutionFactor, 1410 * Configuration::resolutionFactor);
}


void GameView::prepareQuestionsAndAnswerPanel() {
    sf::Vector2f questionCurrentScale = questionPanelSprite.getScale();
    sf::Vector2f newQuestionScale(questionCurrentScale.x * 0.9f, questionCurrentScale.y * 0.9f);

    questionPanelSprite.setScale(newQuestionScale);
    questionPanelSprite.setPosition(70 * Configuration::resolutionFactor, 1050 * Configuration::resolutionFactor);

    sf::Vector2f answerCurrentScale = questionPanelSprite.getScale();
    sf::Vector2f newAnswerScale(answerCurrentScale.x * 0.64f, answerCurrentScale.y * 1.0f);

    correctAnswerSprite.setScale(newAnswerScale);
    selectedAnswerSprite.setScale(newAnswerScale);

    answerASprite.setScale(newAnswerScale);
    answerBSprite.setScale(newAnswerScale);
    answerCSprite.setScale(newAnswerScale);
    answerDSprite.setScale(newAnswerScale);

    answerASprite.setPosition(70 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
    answerBSprite.setPosition(980 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
    answerCSprite.setPosition(70 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);
    answerDSprite.setPosition(980 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);

    switch(gameController.getQuestion().getCorrectAnswer()) {
        case A:
            correctAnswerSprite.setPosition(70 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
            break;
        case B:
            correctAnswerSprite.setPosition(980 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
            break;
        case C:
            correctAnswerSprite.setPosition(70 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);
            break;
        case D:
            correctAnswerSprite.setPosition(980 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);
            break;
    }
}


void GameView::prepareSpritesCoordinate() {
    fiftySpriteCoordinate = getSpriteCoordinate(fiftySprite);
    phoneToFriendSpriteCoordinate = getSpriteCoordinate(phoneToFriendSprite);
    audienceSupportSpriteCoordinate = getSpriteCoordinate(audienceSupportSprite);
    questionPanelSpriteCoordinate = getSpriteCoordinate(questionPanelSprite);
    answerASpriteCoordinate = getSpriteCoordinate(answerASprite);
    answerBSpriteCoordinate = getSpriteCoordinate(answerBSprite);
    answerCSpriteCoordinate = getSpriteCoordinate(answerCSprite);
    answerDSpriteCoordinate = getSpriteCoordinate(answerDSprite);
}


void GameView::prepareQuestionView() {
    std::string texts[3] = {"", "", ""};
    sf::Text tempText;
    prepareText(&tempText, "", &font, 40  * Configuration::resolutionFactor);

    int usingLines = 0;

    std::string wrappedText;
    std::string word;
    std::istringstream iss(gameController.getQuestion().getQuestion());

    while (iss >> word) {
        std::string tmpstr1 = wrappedText + " " + word;
        tempText.setString(tmpstr1);

        if (tempText.getLocalBounds().width > questionPanelSpriteCoordinate.spriteSize.x - 300 * Configuration::resolutionFactor) {
            wrappedText = centerString(wrappedText, (int) (questionPanelSpriteCoordinate.spriteSize.x - 200 * Configuration::resolutionFactor), 40 * Configuration::resolutionFactor, font);
            texts[usingLines] = wrappedText;
            if (usingLines + 1 > 2) {
                break;
            }
            wrappedText = "";
            wrappedText += word;
            usingLines++;
        }
        else {
            if (!wrappedText.empty()) {
                wrappedText += " ";
            }
            wrappedText += word;
        }
    }
    wrappedText = centerString(wrappedText, (questionPanelSpriteCoordinate.spriteSize.x - 300  * Configuration::resolutionFactor), 40 * Configuration::resolutionFactor, font);
    texts[usingLines] = wrappedText;

    prepareText(&questionText[0], texts[0], &font, 40 * Configuration::resolutionFactor);
    prepareText(&questionText[1], texts[1], &font, 40 * Configuration::resolutionFactor);
    prepareText(&questionText[2], texts[2], &font, 40 * Configuration::resolutionFactor);

    if (loadPolishCharacter) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring questionLine1 = converter.from_bytes(texts[0]);
        std::wstring questionLine2 = converter.from_bytes(texts[1]);
        std::wstring questionLine3 = converter.from_bytes(texts[2]);

        questionText[0].setString(questionLine1);
        questionText[1].setString(questionLine2);
        questionText[2].setString(questionLine3);
    }

    switch(usingLines) {
        case 0:
            questionText[0].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 80 * Configuration::resolutionFactor));
            break;
        case 1:
            questionText[0].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
            questionText[1].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 90 * Configuration::resolutionFactor));
            break;

        default:
            questionText[0].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
            questionText[1].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 80 * Configuration::resolutionFactor));
            questionText[2].setPosition((questionPanelSpriteCoordinate.spritePosition.x + 100 * Configuration::resolutionFactor),
                                        (questionPanelSpriteCoordinate.spritePosition.y + 120 * Configuration::resolutionFactor));
    }
}


void GameView::prepareAnswerView() {
    prepareText(&answerA, gameController.getQuestion().getAnswerA(), &font, 40 * Configuration::resolutionFactor);
    prepareText(&answerB, gameController.getQuestion().getAnswerB(), &font, 40 * Configuration::resolutionFactor);
    prepareText(&answerC, gameController.getQuestion().getAnswerC(), &font, 40 * Configuration::resolutionFactor);
    prepareText(&answerD, gameController.getQuestion().getAnswerD(), &font, 40 * Configuration::resolutionFactor);

    if (loadPolishCharacter) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wStringAnswerA = converter.from_bytes(gameController.getQuestion().getAnswerA());
        std::wstring wStringAnswerB = converter.from_bytes(gameController.getQuestion().getAnswerB());
        std::wstring wStringAnswerC = converter.from_bytes(gameController.getQuestion().getAnswerC());
        std::wstring wStringAnswerD = converter.from_bytes(gameController.getQuestion().getAnswerD());

        answerA.setString(wStringAnswerA);
        answerB.setString(wStringAnswerB);
        answerC.setString(wStringAnswerC);
        answerD.setString(wStringAnswerD);
    }


    answerA.setPosition((answerASpriteCoordinate.spritePosition.x + 80 * Configuration::resolutionFactor), (answerASpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
    answerB.setPosition((answerBSpriteCoordinate.spritePosition.x + 80 * Configuration::resolutionFactor), (answerBSpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
    answerC.setPosition((answerCSpriteCoordinate.spritePosition.x + 80 * Configuration::resolutionFactor), (answerCSpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
    answerD.setPosition((answerDSpriteCoordinate.spritePosition.x + 80 * Configuration::resolutionFactor), (answerDSpriteCoordinate.spritePosition.y + 40 * Configuration::resolutionFactor));
}


void GameView::prepareResignButton() {
    sf::Vector2f currentSize = resignButtonSprite.getScale();
    resignButtonSprite.setScale((currentSize.x * 0.25f) * Configuration::resolutionFactor, (currentSize.y * 0.50f) * Configuration::resolutionFactor);
    resignButtonSprite.setPosition(30 * Configuration::resolutionFactor, 30 * Configuration::resolutionFactor);

    sf::Color color(72,34,120);
    resignText.setFillColor(color);
    resignText.setPosition(140 * Configuration::resolutionFactor, 38 * Configuration::resolutionFactor);
}


void GameView::setCorrectAnswerCoordinate() {
    switch(gameController.getQuestion().getCorrectAnswer()) {
        case A:
            correctAnswerSprite.setPosition(answerASpriteCoordinate.spritePosition.x, answerASpriteCoordinate.spritePosition.y);
            break;
        case B:
            correctAnswerSprite.setPosition(answerBSpriteCoordinate.spritePosition.x, answerBSpriteCoordinate.spritePosition.y);
            break;
        case C:
            correctAnswerSprite.setPosition(answerCSpriteCoordinate.spritePosition.x, answerCSpriteCoordinate.spritePosition.y);
            break;
        case D:
            correctAnswerSprite.setPosition(answerDSpriteCoordinate.spritePosition.x, answerDSpriteCoordinate.spritePosition.y);
            break;
    }
}


void GameView::startMusic() {
    stopMusics();

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
            gameMusic3.play();
            gameMusic3.setLoop(true);
            break;
        case 12:
            gameMusic4.play();
            gameMusic4.setLoop(true);
            break;
        default:
            gameMusic1.play();
            gameMusic1.setLoop(true);
    }
    musicPlaysFlag = true;
}


void GameView::stopMusics() {
    gameMusic1.stop();
    gameMusic2.stop();
    gameMusic3.stop();
    gameMusic4.stop();
}


SpriteCoordinate GameView::getSpriteCoordinate(sf::Sprite sprite) {
    SpriteCoordinate result;
    result.spritePosition = sprite.getPosition();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::Vector2f spriteSize(spriteBounds.width, spriteBounds.height);
    result.spriteSize = spriteSize;
    return result;
}


std::string GameView::centerString(std::string string, int width, int fontSize, sf::Font font) {
    sf::Text tempText;
    tempText.setCharacterSize(fontSize);
    tempText.setString(string);
    tempText.setFont(font);
    while (tempText.getLocalBounds().width < width) {
        string = " " + string + " ";
        tempText.setString(string);
    }
    return string;
}

void GameView::scale() {
    backgroundSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    fiftySprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    fiftyOrangeSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    phoneToFriendSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    phoneToFriendOrangeSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    audienceSupportSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    audienceSupportOrangeSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    questionPanelSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    answerASprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    answerBSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    answerCSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    answerDSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    correctAnswerSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    selectedAnswerSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    moneyTreeSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    for (int i = 0; i < 12; i++) {
        awards[i].setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    }
    //answerA.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    //answerB.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    //answerC.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
    //answerD.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);
}

/**************************************
        ~VIEW PREPARING AND SERVICE
 **************************************/


/**************************************
        ACTION HANDLERS
 **************************************/

void GameView::leftMouseClickHandler(sf::Vector2i mousePosition) {
    if (answerIsSelected) return;

    setCorrectAnswerCoordinate();

    if (mousePosition.x >= answerASpriteCoordinate.spritePosition.x && mousePosition.x < answerASpriteCoordinate.spritePosition.x + answerASpriteCoordinate.spriteSize.x &&
        mousePosition.y >= answerASpriteCoordinate.spritePosition.y && mousePosition.y < answerASpriteCoordinate.spritePosition.y + answerASpriteCoordinate.spriteSize.y &&
        gameController.getQuestion().isActiveAnswerA())
    {
        answerAButtonHandler();
    }

    else if (mousePosition.x >= answerBSpriteCoordinate.spritePosition.x && mousePosition.x < answerBSpriteCoordinate.spritePosition.x + answerBSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= answerBSpriteCoordinate.spritePosition.y && mousePosition.y < answerBSpriteCoordinate.spritePosition.y + answerBSpriteCoordinate.spriteSize.y &&
            gameController.getQuestion().isActiveAnswerB())
    {
        answerBButtonHandler();
    }

    else if (mousePosition.x >= answerCSpriteCoordinate.spritePosition.x && mousePosition.x < answerCSpriteCoordinate.spritePosition.x + answerCSpriteCoordinate.spriteSize.x &&
             mousePosition.y >= answerCSpriteCoordinate.spritePosition.y && mousePosition.y < answerCSpriteCoordinate.spritePosition.y + answerCSpriteCoordinate.spriteSize.y &&
            gameController.getQuestion().isActiveAnswerC())
    {
        answerCButtonHandler();
    }

    else if (mousePosition.x >= answerDSpriteCoordinate.spritePosition.x && mousePosition.x < answerDSpriteCoordinate.spritePosition.x + answerDSpriteCoordinate.spriteSize.x &&
             mousePosition.y >= answerDSpriteCoordinate.spritePosition.y && mousePosition.y < answerDSpriteCoordinate.spritePosition.y + answerDSpriteCoordinate.spriteSize.y &&
            gameController.getQuestion().isActiveAnswerD())
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

    else if (mousePosition.x >= resignButtonCoordinate.spritePosition.x && mousePosition.x < resignButtonCoordinate.spritePosition.x + resignButtonCoordinate.spriteSize.x &&
        mousePosition.y >= resignButtonCoordinate.spritePosition.y && mousePosition.y < resignButtonCoordinate.spritePosition.y + resignButtonCoordinate.spriteSize.y)
    {
        resignButtonHandler();
    }
}


void GameView::commonHandlerAfterSelectedAnswer() {
    answerIsSelected = true;
    selectAnswerSound.play();
    try {
        waitForCorrectAnswerThread.join();
    } catch (const std::exception& e) {
        //std::cout << "Exception: " << e.what() << std::endl;
    }
    std::thread thread([this]() {
        waitForCorrectAnswerAfterSelectedAnswer();
    });
    waitForCorrectAnswerThread = std::move(thread);
}


void GameView::answerAButtonHandler() {
    selectedAnswerSprite.setPosition(70 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
    gameController.setSelectedAnswer(A);
    commonHandlerAfterSelectedAnswer();
}


void GameView::answerBButtonHandler() {
    selectedAnswerSprite.setPosition(980 * Configuration::resolutionFactor, 1290 * Configuration::resolutionFactor);
    gameController.setSelectedAnswer(B);
    commonHandlerAfterSelectedAnswer();
}


void GameView::answerCButtonHandler() {
    selectedAnswerSprite.setPosition(70 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);
    gameController.setSelectedAnswer(C);
    commonHandlerAfterSelectedAnswer();
}


void GameView::answerDButtonHandler() {
    selectedAnswerSprite.setPosition(980 * Configuration::resolutionFactor, 1420 * Configuration::resolutionFactor);
    gameController.setSelectedAnswer(D);
    commonHandlerAfterSelectedAnswer();
}


void GameView::lifeLineAButtonHandler() {
    if (!gameController.getLifeLineA()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineA()->use();
}


void GameView::lifeLineBButtonHandler() {
    if (!gameController.getLifeLineB()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineB()->use();
}


void GameView::lifeLineCButtonHandler() {
    if (!gameController.getLifeLineC()->isAvailable()) return;
    selectLifeLineSound.play();
    gameController.getLifeLineC()->use();

}


void GameView::handlingTheSelectedAnswer() {
    if (gameController.getSelectedAnswer() == gameController.getQuestion().getCorrectAnswer()) {
        switch(gameController.getQuestionNumber()) {
            case 2:
            case 7:
                correctAnswerSound2.play();
                break;
            case 12:
                winningSound1.play();
            default:
                correctAnswerSound1.play();
        }
        try {
            waitForCorrectAnswerThread.join();
        } catch (const std::exception& e) {
            //std::cout << "Exception: " << e.what() << std::endl;
        }
        std::thread thread([this]() {
            waitForNextQuestionAfterSelectedAnswer();
        });
        waitForCorrectAnswerThread = std::move(thread);
    }

    else {
        try {
            waitForCorrectAnswerThread.join();
        } catch (const std::exception& e) {
            //std::cout << "Exception: " << e.what() << std::endl;
        }
        try {
            waitForSumUpThread.join();
        } catch (const std::exception& e) {
            //std::cout << "Exception: " << e.what() << std::endl;
        }
        incorrectAnswerSound.play();
        std::thread dialogsThread([this]() {
            waitForSumUpAfterChosenAnswer();
        });
        waitForSumUpThread = std::move(dialogsThread);
        winAmount = gameController.getGuaranteedAmount();
    }
}


void GameView::handlingTheNextQuestion() {
    if (gameController.getQuestion().getQuestionNumber() == 12) {
        sumUp = true;
        winAmount = 1000000;
        stopMusics();
    }
    nextQuestionFlag = true;
    musicPlaysFlag = false;
    answerIsSelected = false;
    showCorrectAnswer = false;
    decideAnswerIsCorrect = false;
    resetAll = false;
}


void GameView::resignButtonHandler() {
    stopMusics();
    winningSound2.play();
    winAmount = gameController.getGainedAmount();
    sumUp = true;
}

void GameView::resetGame() {
    for (auto & award : awards) {
        award.setFillColor(sf::Color(255, 140, 0));
    }

    awards[1].setFillColor(sf::Color::White);
    awards[6].setFillColor(sf::Color::White);
    awards[11].setFillColor(sf::Color::White);

    gameController.resetGameController();
    loadPolishCharacter = true;
    nextQuestionFlag = true;
    musicPlaysFlag = false;
    answerIsSelected = false;
    showCorrectAnswer = false;
    decideAnswerIsCorrect = false;
    resetAll = false;
    sumUp = false;
}

/**************************************
        ~ACTION HANDLERS
 **************************************/