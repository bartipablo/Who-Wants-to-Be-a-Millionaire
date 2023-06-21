//
// Created by Bartosz Pawłowski on 03/06/2023.
//

#include "AudienceSupportView.h"
#include "../Configuration.h"

AudienceSupportView::AudienceSupportView(int answerAVotes, int answerBVotes, int answerCVotes, int answerDVotes)
        : answerAVotes(answerAVotes), answerBVotes(answerBVotes), answerCVotes(answerCVotes),
          answerDVotes(answerDVotes) {
    prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/audience-support-background.png");
    backgroundSprite.setPosition(-100 * Configuration::resolutionFactor, 0);
    backgroundSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);

    prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");

    View::prepareText(&answerA, "A", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&answerB, "B", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&answerC, "C", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&answerD, "D", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&closeButton, "close", &font, 80 * Configuration::resolutionFactor);

    answerA.setPosition(500 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor);
    answerB.setPosition(900 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor);
    answerC.setPosition(1300 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor);
    answerD.setPosition(1700 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor);
    closeButton.setPosition(1015 * Configuration::resolutionFactor, 1400 * Configuration::resolutionFactor);

    int votesSum = answerAVotes + answerBVotes + answerCVotes + answerDVotes;

    View::prepareText(&noVotesByPercentageA, std::to_string((int) std::round(100 * answerAVotes / votesSum)) + " %", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&noVotesByPercentageB, std::to_string((int) std::round(100 * answerBVotes / votesSum)) + " %", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&noVotesByPercentageC, std::to_string((int) std::round(100 * answerCVotes / votesSum)) + " %", &font, 80 * Configuration::resolutionFactor);
    View::prepareText(&noVotesByPercentageD, std::to_string((int) std::round(100 * answerDVotes / votesSum)) + " %", &font, 80 * Configuration::resolutionFactor);

    noVotesByPercentageA.setPosition(450 * Configuration::resolutionFactor, 470 * Configuration::resolutionFactor);
    noVotesByPercentageB.setPosition(850 * Configuration::resolutionFactor, 470 * Configuration::resolutionFactor);
    noVotesByPercentageC.setPosition(1250 * Configuration::resolutionFactor, 470 * Configuration::resolutionFactor);
    noVotesByPercentageD.setPosition(1650 * Configuration::resolutionFactor, 470 * Configuration::resolutionFactor);

    icon.loadFromFile("../resources/images/icon.png");
}

void AudienceSupportView::runAudienceSupportView() {
    sf::RenderWindow window(sf::VideoMode(2200 * Configuration::resolutionFactor, 1600 * Configuration::resolutionFactor), "Audience support");


    int maxHeight = 600 * Configuration::resolutionFactor;
    sf::Color barColor = sf::Color::Blue;

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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

                if (closeButton.getGlobalBounds().contains(mousePositionFloat))
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::White);

        window.draw(backgroundSprite);
        window.draw(answerA);
        window.draw(answerB);
        window.draw(answerC);
        window.draw(answerD);

        window.draw(noVotesByPercentageA);
        window.draw(noVotesByPercentageB);
        window.draw(noVotesByPercentageC);
        window.draw(noVotesByPercentageD);


        window.draw(closeButton);

        int votesSum = answerAVotes + answerBVotes + answerCVotes + answerDVotes;
        int ABarHeight = (int) ((1.0 * answerAVotes / votesSum) * maxHeight);
        int BBarHeight = (int) ((1.0 * answerBVotes / votesSum) * maxHeight);
        int CBarHeight = (int) ((1.0 * answerCVotes / votesSum) * maxHeight);
        int DBarHeight = (int) ((1.0 * answerDVotes / votesSum) * maxHeight);


        //drawing bar chart
        sf::RectangleShape ABar(sf::Vector2f(100 * Configuration::resolutionFactor, ABarHeight));
        ABar.setPosition(480 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor - ABarHeight);
        ABar.setFillColor(barColor);


        sf::RectangleShape BBar(sf::Vector2f(100 * Configuration::resolutionFactor, BBarHeight));
        BBar.setPosition(880 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor - BBarHeight);
        BBar.setFillColor(barColor);


        sf::RectangleShape CBar(sf::Vector2f(100 * Configuration::resolutionFactor, CBarHeight));
        CBar.setPosition(1280 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor - CBarHeight);
        CBar.setFillColor(barColor);

        sf::RectangleShape DBar(sf::Vector2f(100 * Configuration::resolutionFactor, DBarHeight));
        DBar.setPosition(1680 * Configuration::resolutionFactor, 1200 * Configuration::resolutionFactor - DBarHeight);
        DBar.setFillColor(barColor);


        window.draw(ABar);
        window.draw(BBar);
        window.draw(CBar);
        window.draw(DBar);

        window.display();
    }
}
