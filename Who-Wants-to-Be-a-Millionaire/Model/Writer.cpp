//
// Created by Bartosz Pawłowski on 16/05/2023.
//

#include "Writer.h"

void Writer::savePlayerResult(std::string userName, int award, int playingTime) {
    std::ofstream file("dane.csv", std::ios::app);

    if (file.is_open()) {
        file << userName << "," << award << "," << playingTime << "\n";
        file.close();
        std::cout << "The player's result was saved to a CSV file.\n";
    } else {
        std::cout << "ERROR: Could not open csv file.\n";
    }
}

