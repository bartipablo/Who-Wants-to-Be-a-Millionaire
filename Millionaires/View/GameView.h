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
    bool loadPolishCharacter = true;

    std::thread waitForSumUpThread;

    std::thread waitForCorrectAnswer;

    std::thread phoneToFriendThread;

    std::thread audienceSupportThread;

    GameController gameController;

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

    int winAmount = 0;

    //methods
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

    void lifeLineAButtonHandler();

    void lifeLineBButtonHandler();

    void lifeLineCButtonHandler();

    void handlingTheSelectedAnswer();

    void handlingTheNextQuestion();

    void handlingWinnerView();

    void calculateMoneyTreeCoordinate();

    std::string centerString(std::string string, int width, int fontSize, sf::Font font);

    void setCorrectAnswerCoordinate();

    void waitForSumUp();

public:
    GameView();

    void runGameView();

};


#endif //MILLIONAIRES_GAMEVIEW_H
