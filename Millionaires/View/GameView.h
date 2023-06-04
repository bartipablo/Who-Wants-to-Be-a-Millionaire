//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#ifndef MILLIONAIRES_GAMEVIEW_H
#define MILLIONAIRES_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#include "View.h"
#include "../Model/Question.h"
#include "../Model/GameController.h"
#include "WinnerView.h"

typedef struct {
    sf::Vector2f spritePosition;
    sf::Vector2f spriteSize;
} SpriteCoordinate;


class GameView: public View {
private:
    /**************************************
        GUI FLAGS
    **************************************/
    bool loadPolishCharacter = true;

    bool nextQuestionFlag = true;

    bool musicPlaysFlag = false;

    bool answerIsSelected = false;

    bool showCorrectAnswer = false;

    bool decideAnswerIsCorrect = false;

    bool resetAll = false;

    bool sumUp = false;
    /**************************************
        ~GUI FLAGS
    **************************************/

    /**************************************
        THREADS
    **************************************/
    std::thread waitForSumUpThread;
    void waitForSumUpAfterChosenAnswer();

    std::thread waitForCorrectAnswerThread;
    void waitForCorrectAnswerAfterSelectedAnswer();
    void waitForNextQuestionAfterSelectedAnswer();

    std::thread phoneToFriendThread;

    std::thread audienceSupportThread;
    /**************************************
        ~THREADS
    **************************************/

    /**************************************
        SFML ELEMENTS
    **************************************/
    sf::Texture backgroundTexture;

    sf::Texture fiftyTexture;

    sf::Texture fiftyOrangeTexture;

    sf::Texture phoneToFriendTexture;

    sf::Texture phoneToFriendOrangeTexture;

    sf::Texture audienceSupportTexture;

    sf::Texture audienceSupportOrangeTexture;

    sf::Texture questionPanelTexture;

    sf::Texture answerTexture;

    sf::Texture correctAnswerTexture;

    sf::Texture incorrectAnswerTexture;

    sf::Texture selectedAnswerTexture;

    sf::Texture moneyTreeTexture;

    sf::Texture resignButtonTexture;

    sf::Sprite resignButtonSprite;
    SpriteCoordinate resignButtonCoordinate;

    sf::Sprite backgroundSprite;

    sf::Sprite fiftySprite;
    SpriteCoordinate fiftySpriteCoordinate;

    sf::Sprite fiftyOrangeSprite;

    sf::Sprite phoneToFriendSprite;
    SpriteCoordinate phoneToFriendSpriteCoordinate;

    sf::Sprite phoneToFriendOrangeSprite;

    sf::Sprite audienceSupportSprite;
    SpriteCoordinate audienceSupportSpriteCoordinate;

    sf::Sprite audienceSupportOrangeSprite;

    sf::Sprite questionPanelSprite;
    SpriteCoordinate questionPanelSpriteCoordinate;


    sf::Sprite answerASprite;
    SpriteCoordinate answerASpriteCoordinate;

    sf::Sprite answerBSprite;
    SpriteCoordinate answerBSpriteCoordinate;

    sf::Sprite answerCSprite;
    SpriteCoordinate answerCSpriteCoordinate;

    sf::Sprite answerDSprite;
    SpriteCoordinate answerDSpriteCoordinate;

    sf::Sprite correctAnswerSprite;

    sf::Sprite selectedAnswerSprite;

    sf::Sprite moneyTreeSprite;

    sf::SoundBuffer gameMusicBuffer1;

    sf::SoundBuffer gameMusicBuffer2;

    sf::SoundBuffer gameMusicBuffer3;

    sf::SoundBuffer gameMusicBuffer4;

    sf::SoundBuffer gameMusicBuffer5;

    sf::SoundBuffer gameMusicBuffer6;

    sf::SoundBuffer gameMusicBuffer7;

    sf::SoundBuffer nextQuestionBuffer;

    sf::SoundBuffer selectAnswerBuffer;

    sf::SoundBuffer selectLifeLineBuffer;

    sf::SoundBuffer correctAnswerBuffer1;

    sf::SoundBuffer correctAnswerBuffer2;

    sf::SoundBuffer incorrectAnswerBuffer;

    sf::SoundBuffer winningBuffer1;

    sf::SoundBuffer winningBuffer2;

    sf::Sound gameMusic1;

    sf::Sound gameMusic2;

    sf::Sound gameMusic3;

    sf::Sound gameMusic4;

    sf::Sound gameMusic5;

    sf::Sound gameMusic6;

    sf::Sound gameMusic7;

    sf::Sound nextQuestionSound;

    sf::Sound selectAnswerSound;

    sf::Sound selectLifeLineSound;

    sf::Sound correctAnswerSound1;

    sf::Sound correctAnswerSound2;

    sf::Sound incorrectAnswerSound;

    sf::Sound winningSound1;

    sf::Sound winningSound2;

    sf::Text awards[12];

    sf::Text questionText[3];
    int questionTextWidth[3] = {0, 0, 0};

    sf::Text answerA;

    sf::Text answerB;

    sf::Text answerC;

    sf::Text answerD;

    sf::Font font;

    /**************************************
        ~SFML ELEMENTS
    **************************************/

    int winAmount = 0;

    GameController gameController;

    std::string awardsStr[12] = {" 1.      $500", " 2.     $1,000", " 3.     $2,000", " 4.     $5,000", " 5.    $10,000", " 6.    $20,000", " 7.    $50,000",
                                 " 8.    $75,000", " 9.   $150,000", "10.  $250,000", "11.  $500,000", "12.$1 MILLION"};

    /**************************************
             Methods
    **************************************/
    void prepareQuestionView();

    void prepareAnswerView();

    void prepareAwardView();

    void prepareLifeLinesView();

    void prepareQuestionsAndAnswerPanel();

    void startMusic();

    void prepareSpritesCoordinate();

    void leftMouseClickHandler(sf::Vector2i mousePosition);

    SpriteCoordinate getSpriteCoordinate(sf::Sprite sprite);

    void answerAButtonHandler();

    void answerBButtonHandler();

    void answerCButtonHandler();

    void answerDButtonHandler();

    void commonHandlerAfterSelectedAnswer();

    void lifeLineAButtonHandler();

    void lifeLineBButtonHandler();

    void lifeLineCButtonHandler();

    void handlingTheSelectedAnswer();

    void handlingTheNextQuestion();

    void calculateMoneyTreeCoordinate();

    std::string centerString(std::string string, int width, int fontSize, sf::Font font);

    void setCorrectAnswerCoordinate();

    void stopMusics();

    void resignButtonHandler();

    /**************************************
             Methods
    **************************************/

public:
    GameView();

    void runGameView();

    void resetGame();

};

#endif //MILLIONAIRES_GAMEVIEW_H
