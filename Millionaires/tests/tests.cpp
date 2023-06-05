#include "gtest/gtest.h"

#include "../Model/Lifelines/FiftyFifty.h"
#include "../Model/Lifelines/PhoneToFriend.h"
#include "../Model/Lifelines/AudienceSupport.h"

#include "../Model/Reader.h"

/********************************************
        LIFELINES TESTS
 *******************************************/
TEST(FiftyFiftyTests, testActiveAnswerAfterFiftyFifty)
{

    Question exampleQuestion = Reader::getRandomQuestion(1);
    FiftyFifty fiftyFifty(&exampleQuestion);

    fiftyFifty.use();

    int activeQuestion = 0;
    if (exampleQuestion.isActiveAnswerA()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerB()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerC()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerD()) activeQuestion++;

    int expectedActiveQuestion = 2;

    EXPECT_EQ(activeQuestion, expectedActiveQuestion);
}


TEST(FiftyFiftyTests, testActiveAnswerAfterSecondUsedFiftyFifty)
{
    Question exampleQuestion = Reader::getRandomQuestion(1);
    FiftyFifty fiftyFifty(&exampleQuestion);

    fiftyFifty.use();

    exampleQuestion = Reader::getRandomQuestion(2);

    fiftyFifty.use();

    int activeQuestion = 0;
    if (exampleQuestion.isActiveAnswerA()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerB()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerC()) activeQuestion++;
    if (exampleQuestion.isActiveAnswerD()) activeQuestion++;

    int expectedActiveQuestion = 4;

    EXPECT_EQ(activeQuestion, expectedActiveQuestion);
}


TEST(FiftyFiftyTests, testActiveFiftyFiftyAfterUsed)
{
    Question exampleQuestion = Reader::getRandomQuestion(1);
    FiftyFifty fiftyFifty(&exampleQuestion);

    EXPECT_EQ(fiftyFifty.isAvailable(), true);

    fiftyFifty.use();

    EXPECT_EQ(fiftyFifty.isAvailable(), false);
}


TEST(PhoneToFriendTests, testActivePhoneToFriendAfterUsed)
{

    Question exampleQuestion = Reader::getRandomQuestion(1);
    PhoneToFriend phoneToFriend(&exampleQuestion);

    ASSERT_EQ(phoneToFriend.isAvailable(), true);

    phoneToFriend.use();

    ASSERT_EQ(phoneToFriend.isAvailable(), false);
}


TEST(AudienceSupportTests, testActiveAudienceSupportAfterUsed)
{

    Question exampleQuestion = Reader::getRandomQuestion(1);
    AudienceSupport audienceSupport(&exampleQuestion);

    ASSERT_EQ(audienceSupport.isAvailable(), true);

    audienceSupport.use();

    ASSERT_EQ(audienceSupport.isAvailable(), false);
}
/********************************************
        ~LIFELINES TESTS
 *******************************************/

int main() {
    return RUN_ALL_TESTS();
}
