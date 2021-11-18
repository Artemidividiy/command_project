#include <gtest/gtest.h>
#include <iostream>

#include "parser.h"
#include "calculation.h"
#include "utils.h"
#include "f.cpp"

TEST(BINARY_TEST_1, binary_search_test) {
	double a = -1;
    double b = 1;
    int dpi = 100;

    EXPECT_EQ((abs(binary_search(a, b, dpi, f) - (-0.541)) < (b-a) / dpi) ? 0: -1, 0);
}

TEST(CALC_COUNT_TEST_1, clac_count_test) {
	int n = 2;
    double a = -1;
    double b = 1;
    int dpi = 100;
    string mode = "count";
    double ** values = new double*[n];
    for (int i = 0; i < n; ++i){
        values[i] = new double[1];
    }
    Calculation calculation(a, b, dpi, f, mode);
    calculation.calc();
    calculation.get_table(values);

    EXPECT_EQ((abs(values[0][0]- (-0.541)) < (b-a) / dpi) ? 0: -1, 0);
    EXPECT_EQ(values[0][1], 0);

    for (int i = 0; i < n; ++i){
        delete [] values[i];
    }
    delete[] values;
}

TEST(CALC_SIMPLE_TEST_1, clac_simple_test) {
	int n = 2;
    double a = -1;
    double b = 1;
    int dpi = 100;
    string mode = "count";
    double ** values = new double*[n];
    for (int i = 0; i < n; ++i){
        values[i] = new double[1];
    }
    Calculation calculation(a, b, dpi, f, mode);
    calculation.calc();
    calculation.get_table(values);

    EXPECT_EQ((abs(values[0][0]- (-0.541)) < (b-a) / dpi) ? 0: -1, 0);
    EXPECT_EQ(values[0][1], 0);

    for (int i = 0; i < n; ++i){
        delete [] values[i];
    }
    delete[] values;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}