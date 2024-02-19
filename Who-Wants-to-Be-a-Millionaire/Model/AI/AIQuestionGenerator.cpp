//
// Created by Bartosz Pawłowski on 20/06/2023.
//

#include "AIQuestionGenerator.h"

std::string AIQuestionGenerator::readKey() {
    std::ifstream file("../keys/keys");
    std::string content;

    if (file.is_open()) {
        std::string line;

        std::getline(file, line);
        content += line;

        file.close();
    } else {
        std::cerr << "Unable to read key from keys file!" << std::endl;
        std::cerr << "Make sure the file exists (keys directory) and contains your API key" << std::endl;
    }
    return content;
}


std::string AIQuestionGenerator::generateQuestionByAI() {
    std::string key = readKey();
    openai::start(key);

    auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"user", "content":"Complete this pattern with any question you have generated: [Generated question];[Answer];[Answer];[Answer];[Answer];[Correct answer] So, for example: Water is an oxide of:;carbon;silver;iron;hydrogen;hydrogen try to make the questions very difficult, answers must not be more than 30 characters long"}],
        "max_tokens": 1024,
        "temperature": 1.5
    }
    )"_json);
    std::cout << "Response is:\n" << chat.dump(2) << '\n';

    std::string generatedQuestion = chat["choices"][0]["message"]["content"];

    return generatedQuestion;
}




