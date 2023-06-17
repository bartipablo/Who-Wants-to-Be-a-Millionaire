//
// Created by Bartosz Pawłowski on 04/06/2023.
//

#include "WinnerView.h"

WinnerView::WinnerView(int gainedAmount) :  gainedAmount(gainedAmount) {
    prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/winner-background.png");
    backgroundSprite.setPosition(-100 * Configuration::resolutionFactor, 0);
    backgroundSprite.setScale(Configuration::resolutionFactor,  Configuration::resolutionFactor);
    prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");

    prepareText(&hostText, "Regis Philbin", &font, 40 * Configuration::resolutionFactor);
    hostText.setFillColor(sf::Color::Black);
    hostText.setPosition(1400 * Configuration::resolutionFactor, 1130 * Configuration::resolutionFactor);

    prepareText(&playerNameText, "Player", &font, 40 * Configuration::resolutionFactor);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(1000 * Configuration::resolutionFactor, 940 * Configuration::resolutionFactor);

    prepareText(&playAgainButton, "Play again", &font, 70 * Configuration::resolutionFactor);
    playAgainButton.setPosition(400 * Configuration::resolutionFactor, 1400 * Configuration::resolutionFactor);

    prepareText(&exitButton, "exit", &font, 70 * Configuration::resolutionFactor);
    exitButton.setPosition(1650 * Configuration::resolutionFactor, 1400 * Configuration::resolutionFactor);

    prepareGainedAmount();
    prepareDate();
}

void WinnerView::runWinnerView() {
    sf::RenderWindow window(sf::VideoMode(2200 * Configuration::resolutionFactor, 1600 * Configuration::resolutionFactor), "Who want to be a millionaire?");

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
                    Configuration::disableProgram();
                    window.close();
                    return;
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
    prepareText(&gainedAmountText, std::to_string(gainedAmount), &font, 40 * Configuration::resolutionFactor);
    gainedAmountText.setFillColor(sf::Color::Black);
    gainedAmountText.setPosition(1450 * Configuration::resolutionFactor, 948 * Configuration::resolutionFactor);

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
    prepareText(&gainedAmountDescriptionText, gainedAmountDescriptionStr, &font, 40 * Configuration::resolutionFactor);
    gainedAmountDescriptionText.setFillColor(sf::Color::Black);
    gainedAmountDescriptionText.setPosition(750 * Configuration::resolutionFactor, 1030 * Configuration::resolutionFactor);
}

void WinnerView::prepareDate() {
    std::time_t currentTime = std::time(nullptr);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", std::localtime(&currentTime));
    std::string currentDate(buffer);

    prepareText(&dateText, currentDate, &font, 30 * Configuration::resolutionFactor);
    dateText.setFillColor(sf::Color::Black);
    dateText.setPosition(1480 * Configuration::resolutionFactor, 847 * Configuration::resolutionFactor);
}
