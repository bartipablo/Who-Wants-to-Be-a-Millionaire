#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Model/Lifelines/Lifeline.h"
#include "Model/Lifelines/FiftyFifty.h"
#include "Model/Question.h"




int main() {
    Question question("std::string question", "std::string answerA", "std::string answerB", "std::string answerC",
                      "std::string answerD", A, 123, true);

    FiftyFifty fiftyFifty(question);
    Lifeline* kolo = &fiftyFifty;

    bool flag = kolo->isAvailable();
    kolo->use();

    /*
    GameFrame gameFrame;
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sciezka/do/pliku/dzwiekowego.wav"))
    {
        // Obsługa błędu ładowania pliku
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    sf::RenderWindow window(sf::VideoMode(2000, 1600), "Who want to be a millionaire?");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        // Tutaj umieść kod rysowania elementów GUI
        window.display();
    }

    //question_TEST();
     */
    return 0;
}

