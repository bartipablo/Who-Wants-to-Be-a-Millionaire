#include "gtest/gtest.h"

#include "../Model/Lifelines/FiftyFifty.h"
#include "../Model/Lifelines/PhoneToFriend.h"
#include "../Model/Lifelines/AudienceSupport.h"

#include "../Model/Question.h"
#include "../Model/Reader.h"
#include "../Model/GameController.h"

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


/********************************************
        READER TESTS
 *******************************************/
TEST(ReaderTests, testCorrectReadData)
{
    Question question = Reader::getRandomQuestion(19);

    ASSERT_EQ(question.getQuestion(), "Woda to tlenek:");
    ASSERT_EQ(question.getAnswerA(), "A. węgla");
    ASSERT_EQ(question.getAnswerB(), "B. srebra");
    ASSERT_EQ(question.getAnswerC(), "C. żelaza");
    ASSERT_EQ(question.getAnswerD(), "D. wodoru");
    ASSERT_EQ(question.getCorrectAnswer(), D);

}
/********************************************
        ~READER TESTS
 *******************************************/



/********************************************
        QUESTION TESTS
 *******************************************/
TEST(QuestionTests, testAnswersGetters)
{
    Question question = Reader::getRandomQuestion(19);
    ASSERT_EQ(question.getCorrectAnswer(), D);

    ASSERT_NE(question.getRandomIncorrectAnswer(), D);
    ASSERT_NE(question.getRandomIncorrectAnswer(), D);
    ASSERT_NE(question.getRandomIncorrectAnswer(), D);
    ASSERT_NE(question.getRandomIncorrectAnswer(), D);
    ASSERT_NE(question.getRandomIncorrectAnswer(), D);

    std::vector<Answer> activeAnswers = question.getActiveAnswers();
    ASSERT_NE(activeAnswers[0], activeAnswers[1]);
    ASSERT_NE(activeAnswers[0], activeAnswers[2]);
    ASSERT_NE(activeAnswers[0], activeAnswers[3]);
    ASSERT_NE(activeAnswers[1], activeAnswers[2]);
    ASSERT_NE(activeAnswers[1], activeAnswers[3]);
    ASSERT_NE(activeAnswers[2], activeAnswers[3]);

    std::vector<Answer> activeIncorrectAnswers = question.getIncorrectActiveAnswers();
    ASSERT_NE(activeIncorrectAnswers[0], D);
    ASSERT_NE(activeIncorrectAnswers[1], D);
    ASSERT_NE(activeIncorrectAnswers[2], D);
    ASSERT_NE(activeIncorrectAnswers[0], activeIncorrectAnswers[1]);
    ASSERT_NE(activeIncorrectAnswers[0], activeIncorrectAnswers[2]);
    ASSERT_NE(activeIncorrectAnswers[1], activeIncorrectAnswers[2]);
}


TEST(QuestionTests, testAnswersGettersWithUnactiveAnswers)
{
    Question question = Reader::getRandomQuestion(19);
    question.deactivateAnswerB();
    question.deactivateAnswerA();

    ASSERT_EQ(question.getCorrectAnswer(), D);

    ASSERT_EQ(question.getRandomIncorrectAnswer(), C);


    std::vector<Answer> activeAnswers = question.getActiveAnswers();
    ASSERT_NE(activeAnswers[0], activeAnswers[1]);

    std::vector<Answer> activeIncorrectAnswers = question.getIncorrectActiveAnswers();
    ASSERT_EQ(activeIncorrectAnswers[0], C);
}

TEST(QuestionTests, testGuarantedAmount)
{
    Question question;
    int expectedAwards[12] = {500, 1000, 2000, 5000, 10000, 20000, 40000, 75000, 125000, 250000, 500000, 1000000};
    bool expectedIsGuarantedAwards[12] = {false, true, false, false, false, false, true ,false, false, false, false, false};

    for (int i = 0; i < 12; i++) {
        question = Reader::getRandomQuestion(i + 1);
        ASSERT_EQ(question.getAmount(), expectedAwards[i]);
        ASSERT_EQ(question.isGuaranteedAmount(), expectedIsGuarantedAwards[i]);
    }
}
/********************************************
        ~QUESTION TESTS
 *******************************************/


/********************************************
        GAMECONTROLLER TESTS
 *******************************************/
TEST(GameControllerTests, GameControllerAwardsTest)
{
    int expectedAwards[12] = {0, 500, 1000, 2000, 5000, 10000, 20000, 40000, 75000, 125000, 250000, 500000};

    GameController gameController;

    for (int i = 0; i < 12; i++) {
        gameController.loadNextQuestion();
        ASSERT_EQ(gameController.getGainedAmount(), expectedAwards[i]);

        if (i < 1)  ASSERT_EQ(gameController.getGuaranteedAmount(), 0);
        if (i >= 2 && i < 7) ASSERT_EQ(gameController.getGuaranteedAmount(), 1000);
        if (i >= 7) ASSERT_EQ(gameController.getGuaranteedAmount(), 40000);
    }

}
/********************************************
        ~GAMECONTROLLER TESTS
 *******************************************/

int main() {
    return RUN_ALL_TESTS();
}
