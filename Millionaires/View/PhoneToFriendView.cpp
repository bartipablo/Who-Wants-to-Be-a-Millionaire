//
// Created by Bartosz Pawłowski on 27/05/2023.
//

#include <codecvt>
#include "PhoneToFriendView.h"


void PhoneToFriendView::dialogsHandler() {
    dialogsToShow = 0;
    for (int i = 0; i < dialogsNo; i++) {
        if (dialogsToShow == dialogsNo - 1) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else if (dialogsToShow == 1) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        dialogsToShow++;
    }
}


void PhoneToFriendView::runPhoneToFriendView() {
    std::thread dialogsThread([this]() {
        dialogsHandler();
    });
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "Phone to friend");

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
                    dialogsToShow == dialogsNo)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat = window.mapPixelToCoords(mousePosition);

                if (closeButton.getGlobalBounds().contains(mousePositionFloat))
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);
        for (int i = 0; i < dialogsToShow; i++) {
            window.draw(dialogs[i]);
        }
        if (dialogsToShow == dialogsNo) {
            window.draw(closeButton);
        }

        window.display();
    }
    dialogsThread.join();
}

PhoneToFriendView::PhoneToFriendView(Question *question, std::string friendAnswer) {
    this->question = question;
    this->friendAnswer = friendAnswer;

    prepareSprite(&backgroundTexture, &backgroundSprite, "./resources/images/output-onlinepngtools.png");
    backgroundSprite.setPosition(-100, 0);

    prepareFont(&font, "./resources/fonts/OpenSans-Bold.ttf");

    prepareText();
}

std::string PhoneToFriendView::wrapText(std::string inputString, float maxWidth)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(inputString);

    sf::Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(40);
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

    View::prepareText(&dialogs[0], "You: Uwaga czytam pytanie.", &font, 40);
    dialogs[i].setPosition(30, yPosition);
    i++;


    View::prepareText(&dialogs[i], "", &font, 40);
    std::string wrappedText = wrapText("You: " + question->getQuestion(), 1600);
    int wrappedTextLineNo = countLines(wrappedText);
    dialogs[i].setString(wrappedText);
    dialogs[i].setPosition(30, 600 + i*100);
    if (loadPolishCharacters) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring questionLine = converter.from_bytes(wrappedText);
        dialogs[i].setString(questionLine);
    }
    i++;

    if (question->isActiveAnswerA()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerA(), &font, 40);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerA());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30, 600 + i*100 + (wrappedTextLineNo-1)*100);
        i++;
    }

    if (question->isActiveAnswerB()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerB(), &font, 40);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerB());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30, 600 + i*100 + (wrappedTextLineNo-1)*100);
        i++;
    }

    if (question->isActiveAnswerC()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerC(), &font, 40);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerC());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30, 600 + i*100 + (wrappedTextLineNo-1)*100);
        i++;
    }

    if (question->isActiveAnswerD()) {
        View::prepareText(&dialogs[i], "You: " + question->getAnswerD(), &font, 40);
        if (loadPolishCharacters) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring questionLine = converter.from_bytes("You: " + question->getAnswerD());
            dialogs[i].setString(questionLine);
        }
        dialogs[i].setPosition(30, 600 + i*100 + (wrappedTextLineNo-1)*100);
        i++;
    }

    View::prepareText(&dialogs[i], "Friend: " + friendAnswer, &font, 40);
    if (loadPolishCharacters) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring questionLine = converter.from_bytes("Friend: " + friendAnswer);
        dialogs[i].setString(questionLine);
    }
    dialogs[i].setPosition(30, 600 + i*100 + (wrappedTextLineNo-1)*100);
    i++;

    dialogsNo = i;

    View::prepareText(&closeButton, "Close", &font, 80);
    closeButton.setPosition(970, 1400);
}
