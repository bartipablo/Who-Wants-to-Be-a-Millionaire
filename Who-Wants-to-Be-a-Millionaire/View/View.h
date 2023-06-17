//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#ifndef MILLIONAIRES_VIEW_H
#define MILLIONAIRES_VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class View {
protected:
    void prepareSprite(sf::Texture* texture, sf::Sprite* sprite, std::string path);

    void prepareSound(sf::SoundBuffer* soundBuffer, sf::Sound* sound, std::string path);

    void prepareFont(sf::Font* font, std::string path);

    void prepareText(sf::Text* text, std::string content, sf::Font* font, int fontSize);
};


#endif //MILLIONAIRES_VIEW_H
