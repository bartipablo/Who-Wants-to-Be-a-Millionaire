cmake_minimum_required(VERSION 3.25)
# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run tests.cpp ../Model/Question.cpp ../Model/Question.h ../Model/Reader.cpp ../Model/Reader.h ../Model/Player.cpp ../Model/Player.h ../Model/Writer.cpp ../Model/Writer.h ../View/GameView.cpp ../View/GameView.h ../Model/Lifelines/Lifeline.h ../Model/Lifelines/FiftyFifty.cpp ../Model/Lifelines/FiftyFifty.h ../Functions/Answer.h ../Functions/Random.h ../Functions/Random.cpp ../Functions/Answer.cpp ../Model/Lifelines/PhoneToFriend.cpp ../Model/Lifelines/PhoneToFriend.h ../Model/Lifelines/AudienceSupport.cpp ../Model/Lifelines/AudienceSupport.h ../View/StartView.cpp ../View/StartView.h ../View/View.cpp ../View/View.h ../Model/GameController.cpp ../Model/GameController.h ../View/PhoneToFriendView.cpp ../View/PhoneToFriendView.h ../View/AudienceSupportView.cpp ../View/AudienceSupportView.h ../View/WinnerView.cpp ../View/WinnerView.h ../Configuration.cpp ../Configuration.h)
#add_executable(Google_Tests_run FiftyFiftyTests.cpp test2.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)

include_directories(/usr/local/include)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Google_Tests_run sfml-system sfml-window sfml-graphics sfml-audio sfml-network)