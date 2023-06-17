//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#include "View.h"

void View::prepareSprite(sf::Texture* texture, sf::Sprite* sprite, std::string path) {
        if (!texture->loadFromFile(path)) {
            std::cout << "ERROR: Faile to load " << path << std::endl;
        }
        sprite->setTexture(*texture);
}


void View::prepareSound(sf::SoundBuffer* soundBuffer, sf::Sound* sound, std::string path) {
    if (!soundBuffer->loadFromFile(path))
    {
        std::cout << "ERROR: Faile to load " << path << std::endl;
    }
    sound->setBuffer(*soundBuffer);
}


void View::prepareFont(sf::Font* font, std::string path) {
    if (!font->loadFromFile(path))
    {
        std::cout << "ERROR: Faile to load " << path << std::endl;
    }
}


void View::prepareText(sf::Text* text, std::string content, sf::Font* font, int fontSize) {
    *text = sf::Text(content, *font, fontSize);
}




