//
// Created by Bartosz Pawłowski on 27/05/2023.
//

#include <codecvt>
#include "PhoneToFriendView.h"
#include "../Configuration.h"

void PhoneToFriendView::dialogsHandler() {
    lineDialogsToShow = 0;
    for (int i = 0; i < lineDialogsNo; i++) {
        if (lineDialogsToShow == lineDialogsNo - 1) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else if (lineDialogsToShow == 1) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        lineDialogsToShow++;
    }
}


void PhoneToFriendView::runPhoneToFriendView() {
    std::thread dialogsThread([this]() {
        dialogsHandler();
    });
    sf::RenderWindow window(sf::VideoMode(2200 * Configuration::resolutionFactor, 1600 * Configuration::resolutionFactor), "Phone to friend");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
                     lineDialogsToShow == lineDialogsNo)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat = window.mapPixelToCoords(mousePosition);

                if (closeButton.getGlobalBounds().contains(mousePositionFloat))
                {
                    try {
                        dialogsThread.join();
                    } catch (const std::exception& e) {
                        std::cout << "Exception: " << e.what() << std::endl;
                    }
                    window.close();
                    return;
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);
        for (int i = 0; i < lineDialogsToShow; i++) {
            window.draw(dialogs[i]);
        }
        if (lineDialogsToShow == lineDialogsNo) {
            window.draw(closeButton);
        }

        window.display();
    }

    try {
        dialogsThread.join();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

PhoneToFriendView::PhoneToFriendView(Question *question, std::string friendAnswer) {
    this->question = question;
    this->friendAnswer = friendAnswer;

    prepareSprite(&backgroundTexture, &backgroundSprite, "../resources/images/output-onlinepngtools.png");
    backgroundSprite.setPosition(-100 * Configuration::resolutionFactor, 0);
    backgroundSprite.setScale(Configuration::resolutionFactor, Configuration::resolutionFactor);

    prepareFont(&font, "../resources/fonts/OpenSans-Bold.ttf");

    prepareText();
}

std::string PhoneToFriendView::wrapText(std::string inputString, float maxWidth)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(inputString);

    sf::Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(40 * Configuration::resolutionFactor);
    tempText.setString(wideString);
    sf::FloatRect tempBounds = tempText.getLocalBounds();
    float tempWidth = tempBounds.width;

    if (tempWidth > maxWidth)
    {
        std::string wrappedString;
        std::string word;
        std::istringstream iss(inputString, std::ios_base::in | std::ios_base::binary);
        while (iss >> word)
        {
            sf::Text tempWordText(tempText);
            tempWordText.setString(wrappedString + word + " ");

            sf::FloatRect tempWordBounds = tempWordText.getLocalBounds();
            float tempWordWidth = tempWordBounds.width;

            if (tempWordWidth > maxWidth)
            {
                wrappedString += "\n" + word + " ";
            }
            else
            {
                wrappedString += word + " ";
            }
        }

        return wrappedString;
    }

    return inputString;
}

int PhoneToFriendView::countLines(const std::string& text) {
    int lineCount = 1;

    for (char c : text)
    {
        if (c == '\n')
        {
            lineCount++;
        }
    }

    return lineCount;
}



void PhoneToFriendView::prepareText() {
    int i = 0;
    int yPosition = 600;

    View::prepareText(&dialogs[0], "You: Uwaga czytam pytanie.", &font, 40 * Configuration::resolutionFactor);
    dialogs[i].setPosition(30 * Configuration::resolutionFactor, yPosition * Configuration::resolutionFactor);
    i++;


    View::prepareText(&dialogs[i], "", &font, 40 * Configuration::resolutionFactor);
    std::string wrappedText = wrapText("You: " + question->getQuestion(), 1600 * Configuration::resolutionFactor);
    int wrappedTextLineNo = countLines(wrappedText);
    dialogs[i].setString(wrappedText);
    dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100) * Configuration::resolutionFactor);
    if (loadPolishCharacters) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring questionLine = converter.from_bytes(wrappedText);
        dialogs[i].setString(questionLine);
    }
    i++;

    if (question->isActiveAnswerA()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerA(), &font, 40 * Configuration::resolutionFactor);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerA());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100 + (wrappedTextLineNo-1)*100) * Configuration::resolutionFactor);
        i++;
    }

    if (question->isActiveAnswerB()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerB(), &font, 40 * Configuration::resolutionFactor);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerB());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100 + (wrappedTextLineNo-1)*100) * Configuration::resolutionFactor);
        i++;
    }

    if (question->isActiveAnswerC()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerC(), &font, 40 * Configuration::resolutionFactor);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerC());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100 + (wrappedTextLineNo-1)*100) * Configuration::resolutionFactor);
        i++;
    }

    if (question->isActiveAnswerD()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerD(), &font, 40 * Configuration::resolutionFactor);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerD());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100 + (wrappedTextLineNo-1)*100) * Configuration::resolutionFactor);
        i++;
    }

    View::prepareText(&dialogs[i], "Friend: " + friendAnswer, &font, 40 * Configuration::resolutionFactor);
    if (loadPolishCharacters) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring questionLine = converter.from_bytes("Friend: " + friendAnswer);
        dialogs[i].setString(questionLine);
    }
    dialogs[i].setPosition(30 * Configuration::resolutionFactor, (600 + i*100 + (wrappedTextLineNo-1)*100) * Configuration::resolutionFactor);
    i++;

    lineDialogsNo = i;

    View::prepareText(&closeButton, "Close", &font, 80 * Configuration::resolutionFactor);
    closeButton.setPosition(970 * Configuration::resolutionFactor, 1400 * Configuration::resolutionFactor);
}
