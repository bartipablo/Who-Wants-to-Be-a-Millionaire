//
// Created by Bartosz Pawłowski on 03/06/2023.
//

#include "AudienceSupportView.h"

AudienceSupportView::AudienceSupportView(int answerAVotes, int answerBVotes, int answerCVotes, int answerDVotes)
        : answerAVotes(answerAVotes), answerBVotes(answerBVotes), answerCVotes(answerCVotes),
          answerDVotes(answerDVotes) {
    prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/audience-support-background.png");
    backgroundSprite.setPosition(-100, 0);

    prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");

    View::prepareText(&answerA, "A", &font, 80);
    View::prepareText(&answerB, "B", &font, 80);
    View::prepareText(&answerC, "C", &font, 80);
    View::prepareText(&answerD, "D", &font, 80);
    View::prepareText(&closeButton, "close", &font, 80);

    answerA.setPosition(500, 1200);
    answerB.setPosition(900, 1200);
    answerC.setPosition(1300, 1200);
    answerD.setPosition(1700, 1200);
    closeButton.setPosition(1015, 1400);

    int votesSum = answerAVotes + answerBVotes + answerCVotes + answerDVotes;

    View::prepareText(&noVotesByPercentageA, std::to_string((int) std::round(100 * answerAVotes / votesSum)) + " %", &font, 80);
    View::prepareText(&noVotesByPercentageB, std::to_string((int) std::round(100 * answerBVotes / votesSum)) + " %", &font, 80);
    View::prepareText(&noVotesByPercentageC, std::to_string((int) std::round(100 * answerCVotes / votesSum)) + " %", &font, 80);
    View::prepareText(&noVotesByPercentageD, std::to_string((int) std::round(100 * answerDVotes / votesSum)) + " %", &font, 80);

    noVotesByPercentageA.setPosition(450, 470);
    noVotesByPercentageB.setPosition(850, 470);
    noVotesByPercentageC.setPosition(1250, 470);
    noVotesByPercentageD.setPosition(1650, 470);

}

void AudienceSupportView::runAudienceSupportView() {
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Audience support");

    int maxHeight = 600;
    sf::Color barColor = sf::Color::Blue;

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
        sf::RectangleShape ABar(sf::Vector2f(100, ABarHeight));
        ABar.setPosition(480, 1200 - ABarHeight);
        ABar.setFillColor(barColor);


        sf::RectangleShape BBar(sf::Vector2f(100, BBarHeight));
        BBar.setPosition(880, 1200 - BBarHeight);
        BBar.setFillColor(barColor);


        sf::RectangleShape CBar(sf::Vector2f(100, CBarHeight));
        CBar.setPosition(1280, 1200 - CBarHeight);
        CBar.setFillColor(barColor);

        sf::RectangleShape DBar(sf::Vector2f(100, DBarHeight));
        DBar.setPosition(1680, 1200 - DBarHeight);
        DBar.setFillColor(barColor);


        window.draw(ABar);
        window.draw(BBar);
        window.draw(CBar);
        window.draw(DBar);

        window.display();
    }
}
