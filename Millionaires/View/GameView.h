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


typedef struct {
    sf::Vector2f spritePosition;
    sf::Vector2f spriteSize;
} SpriteCoordinate;


class GameView: public View {
private:
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

    sf::SoundBuffer gameMusicBuffer1;

    sf::SoundBuffer nextQuestionBuffer;

    sf::Sound gameMusic1;

    sf::Sound nextQuestionSound;

    sf::Text awards[12];

    sf::Font font;

    //methods
    void prepareAwardView();

    void prepareLifeLinesView();

    void prepareQuestionsAndAnswerPanel();

    void startMusic();

    void prepareSpritesCoordinate();

    void leftMouseClickHandler(sf::Vector2i mousePosition);

    SpriteCoordinate getSpriteCoordinate(sf::Sprite sprite);

public:
    GameView();

    void runGameView();

};


#endif //MILLIONAIRES_GAMEVIEW_H
