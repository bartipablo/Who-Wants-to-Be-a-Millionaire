//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "GameView.h"

std::string awardsStr[12] = {" 1.      $500", " 2.     $1,000", " 3.     $2,000", " 4.     $5,000", " 5.    $10,000", " 6.    $20,000", " 7.    $50,000",
                          " 8.    $75,000", " 9.   $150,000", "10.  $250,000", "11.  $500,000", "12.$1 MILLION"};

bool nextQuestionFlag = true;

bool musicPlaysFlag = false;


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
    answerBSprite.setTexture(answerTexture);
    answerCSprite.setTexture(answerTexture);
    answerDSprite.setTexture(answerTexture);

    prepareSound(&gameMusicBuffer1, &gameMusic1, "./resources/sounds/music01.wav");
    prepareSound(&nextQuestionBuffer, &nextQuestionSound, "./resources/sounds/newQuestion.wav");
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
        //ANSWERS VIEW

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

    answerASprite.setScale(newAnswerScale);
    answerBSprite.setScale(newAnswerScale);
    answerCSprite.setScale(newAnswerScale);
    answerDSprite.setScale(newAnswerScale);

    answerASprite.setPosition(70, 1290);
    answerBSprite.setPosition(980, 1290);
    answerCSprite.setPosition(70, 1420);
    answerDSprite.setPosition(980, 1420);

}


void GameView::startMusic() {
    switch (gameController.getQuestionNumber()) {
        case 1:
            gameMusic1.play();
            gameMusic1.setLoop(true);
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
    if (mousePosition.x >= fiftySpriteCoordinate.spritePosition.x && mousePosition.x < fiftySpriteCoordinate.spritePosition.x + fiftySpriteCoordinate.spriteSize.x &&
        mousePosition.y >= fiftySpriteCoordinate.spritePosition.y && mousePosition.y < fiftySpriteCoordinate.spritePosition.y + fiftySpriteCoordinate.spriteSize.y)
    {
        gameController.getLifeLineA()->deactivate();
    }

    else if (mousePosition.x >= phoneToFriendSpriteCoordinate.spritePosition.x && mousePosition.x < phoneToFriendSpriteCoordinate.spritePosition.x + phoneToFriendSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= phoneToFriendSpriteCoordinate.spritePosition.y && mousePosition.y < phoneToFriendSpriteCoordinate.spritePosition.y + phoneToFriendSpriteCoordinate.spriteSize.y)
    {
        gameController.getLifeLineB()->deactivate();
    }

    else if (mousePosition.x >= audienceSupportSpriteCoordinate.spritePosition.x && mousePosition.x < audienceSupportSpriteCoordinate.spritePosition.x + audienceSupportSpriteCoordinate.spriteSize.x &&
        mousePosition.y >= audienceSupportSpriteCoordinate.spritePosition.y && mousePosition.y < audienceSupportSpriteCoordinate.spritePosition.y + audienceSupportSpriteCoordinate.spriteSize.y)
    {
        gameController.getLifeLineC()->deactivate();
    }
}
