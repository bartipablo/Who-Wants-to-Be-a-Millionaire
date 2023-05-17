//
// Created by Bartosz Pawłowski on 17/05/2023.
//

#include "StartView.h"


void StartView::runStartView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    bool buttonVisible = false;

    //playing song
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("resources/sounds/StartGame.wav"))
    {
        std::cout << "ERROR: Faile to load StartGame.wav" << std::endl;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();
    //playing song

    //texture
    sf::Texture texture1;
    if (!texture1.loadFromFile("resources/images/background.png")) // Wstaw ścieżkę do pliku obrazka
    {
        std::cout << "ERROR: Faile to load rays.jpeg" << std::endl;
    }

    sf::Texture texture2;
    if (!texture2.loadFromFile("resources/images/logo.png")) // Wstaw ścieżkę do pliku obrazka
    {
        std::cout << "ERROR: Faile to load rays.jpeg" << std::endl;
    }

    sf::Font font;
    if (!font.loadFromFile("resources/fonts/OpenSans-Bold.ttf")) // Wstaw ścieżkę do pliku czcionki
    {
        std::cout << "ERROR: Faile to load rays.jpeg" << std::endl;
    }

    sf::Text buttonText("Start", font, 120);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(930, 1300);


    sf::Sprite sprite1(texture1);
    sf::Sprite sprite2(texture2);
    sprite1.setOrigin(sprite1.getLocalBounds().width / 2, sprite1.getLocalBounds().height / 2);
    sprite1.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    sprite2.setOrigin(sprite2.getLocalBounds().width / 2, sprite2.getLocalBounds().height / 2);
    sprite2.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    float rotationSpeed = 0.015f;
    //texture

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.clear();

        sprite1.rotate(rotationSpeed * 0.5f); // Mnożnik prędkości wynosi 0.5f

        window.draw(sprite1);
        window.draw(sprite2);
        window.draw(buttonText);

        window.display();
    }
}



