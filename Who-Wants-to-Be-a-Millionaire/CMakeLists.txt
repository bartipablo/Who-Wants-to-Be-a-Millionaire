cmake_minimum_required(VERSION 3.25)
project(Who-Wants-to-Be-a-Millionaire)

set(CMAKE_CXX_STANDARD 17)

add_executable(Who-Wants-to-Be-a-Millionaire main.cpp Model/Question.cpp Model/Question.h Model/Reader.cpp Model/Reader.h Model/Player.cpp Model/Player.h Model/Writer.cpp Model/Writer.h View/GameView.cpp View/GameView.h Model/Lifelines/Lifeline.h Model/Lifelines/FiftyFifty.cpp Model/Lifelines/FiftyFifty.h Functions/Answer.h Functions/Random.h Functions/Random.cpp Functions/Answer.cpp Model/Lifelines/PhoneToFriend.cpp Model/Lifelines/PhoneToFriend.h Model/Lifelines/AudienceSupport.cpp Model/Lifelines/AudienceSupport.h View/StartView.cpp View/StartView.h View/View.cpp View/View.h Model/GameController.cpp Model/GameController.h View/PhoneToFriendView.cpp View/PhoneToFriendView.h View/AudienceSupportView.cpp View/AudienceSupportView.h View/WinnerView.cpp View/WinnerView.h Configuration.cpp Configuration.h Model/AI/AIQuestionGenerator.cpp Model/AI/AIQuestionGenerator.h)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Who-Wants-to-Be-a-Millionaire sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(Who-Wants-to-Be-a-Millionaire ${CURL_LIBRARIES})


add_subdirectory(tests)