#include <gtest/gtest.h>
#include "marker_logic.h"


TEST(MarkerLogicTest, StepOnEmptyArray) {
    std::vector<int> arr;
    MarkerLogic logic(1, 0);

    EXPECT_FALSE(logic.step(arr));
    EXPECT_EQ(logic.getMarkedCount(), 0);
}


TEST(MarkerLogicTest, FirstStepMarksElement) {
    std::vector<int> arr(5, 0);
    MarkerLogic logic(1, static_cast<int>(arr.size()));

    bool result = logic.step(arr);

    EXPECT_TRUE(result);
    EXPECT_EQ(logic.getMarkedCount(), 1);


    EXPECT_NE(std::find(arr.begin(), arr.end(), 1), arr.end());
}


TEST(MarkerLogicTest, MultipleStepsIncreaseCount) {
    std::vector<int> arr(10, 0);
    MarkerLogic logic(2, static_cast<int>(arr.size()));

    int steps = 0;
    for (int i = 0; i < 10; ++i) {
        if (logic.step(arr)) {
            steps++;
        }
    }

    EXPECT_EQ(logic.getMarkedCount(), steps);


    for (int v : arr) {
        if (v != 0) {
            EXPECT_EQ(v, 2);
        }
    }
}


TEST(MarkerLogicTest, StepFailsOnOccupiedCell) {
    std::vector<int> arr(3, 0);
    MarkerLogic logic(3, static_cast<int>(arr.size()));


    arr[0] = 99;
    arr[1] = 99;
    arr[2] = 99;

    bool result = logic.step(arr);

    EXPECT_FALSE(result);
    EXPECT_EQ(logic.getMarkedCount(), 0);
}
