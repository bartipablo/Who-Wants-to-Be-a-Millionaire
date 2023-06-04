//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#include "WinnerView.h"

WinnerView::WinnerView(int gainedAmount) :  gainedAmount(gainedAmount) {
    prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/winner-background.png");
    backgroundSprite.setPosition(-100, 0);
    prepareFont(&font, "./resources/fonts/OpenSans-Bold.ttf");

    prepareText(&hostText, "Regis Philbin", &font, 40);
    hostText.setFillColor(sf::Color::Black);
    hostText.setPosition(1400, 1130);

    prepareText(&playerNameText, "Player", &font, 40);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(1000, 940);

    prepareText(&playAgainButton, "Play again", &font, 70);
    playAgainButton.setPosition(400, 1400);

    prepareText(&exitButton, "exit", &font, 70);
    exitButton.setPosition(1650, 1400);

    prepareGainedAmount();
    prepareDate();
}

void WinnerView::runWinnerView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Who want to be a millionaire?");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat = window.mapPixelToCoords(mousePosition);

                if (exitButton.getGlobalBounds().contains(mousePositionFloat)) {
                    exit(0);
                }

                if (playAgainButton.getGlobalBounds().contains(mousePositionFloat)) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);
        window.draw(gainedAmountText);
        window.draw(dateText);
        window.draw(gainedAmountDescriptionText);
        window.draw(hostText);
        window.draw(playerNameText);
        window.draw(playAgainButton);
        window.draw(exitButton);

        window.display();
    }

}

void WinnerView::prepareGainedAmount() {
    prepareText(&gainedAmountText, std::to_string(gainedAmount), &font, 40);
    gainedAmountText.setFillColor(sf::Color::Black);
    gainedAmountText.setPosition(1450, 948);

    std::string gainedAmountDescriptionStr = "";
    switch(gainedAmount) {
        case 500:
            gainedAmountDescriptionStr = "FIVE HUNDRED";
            break;
        case 1000:
            gainedAmountDescriptionStr = "ONE THOUSAND";
            break;
        case 2000:
            gainedAmountDescriptionStr = "TWO THOUSAND";
            break;
        case 5000:
            gainedAmountDescriptionStr = "FIVE THOUSAND";
            break;
        case 10000:
            gainedAmountDescriptionStr = "TEN THOUSAND";
            break;
        case 20000:
            gainedAmountDescriptionStr = "TWENTY THOUSAND";
            break;
        case 40000:
            gainedAmountDescriptionStr = "FORTY THOUSAND";
            break;
        case 75000:
            gainedAmountDescriptionStr = "SEVENTY-FIVE THOUSAND";
            break;
        case 125000:
            gainedAmountDescriptionStr = "ONE HUNDRED TWENTY-FIVE THOUSAND";
            break;
        case 250000:
            gainedAmountDescriptionStr = "TWO HUNDRED AND FIFTY THOUSAND";
            break;
        case 500000:
            gainedAmountDescriptionStr = "FIVE HUNDRED THOUSAND";
            break;
        case 1000000:
            gainedAmountDescriptionStr = "ONE MILLION";
            break;
    }
    prepareText(&gainedAmountDescriptionText, gainedAmountDescriptionStr, &font, 40);
    gainedAmountDescriptionText.setFillColor(sf::Color::Black);
    gainedAmountDescriptionText.setPosition(750, 1030);


}

void WinnerView::prepareDate() {
    std::time_t currentTime = std::time(nullptr);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", std::localtime(&currentTime));
    std::string currentDate(buffer);

    prepareText(&dateText, currentDate, &font, 30);
    dateText.setFillColor(sf::Color::Black);
    dateText.setPosition(1480, 847);
}
