#include <gtest/gtest.h>
#include <iostream>

#include "parser.hpp"

#define eps 1e-4
using namespace std;

TEST(Parser_TEST_1, parser_one_priority_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "-x+ 2 +7.3 - 2.4 - x";
    double x = 3.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ((stof(output.str()) + 0.1)< eps, true);
}

TEST(Parser_TEST_2, parser_changing_priorities_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "x + 50.3 - x / 2 * x + 3 / 10";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ((stof(output.str()) - 40.975)< eps, true);
}

TEST(Parser_TEST_3, parser_brackets_simple_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "(2- x)";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ((stof(output.str()) - (-3.5))< eps, true);
}

TEST(Parser_TEST_4, parser_brackets_multi_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "(2- x) * (x+ 4.5)";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ((stof(output.str()) - (-30))< eps, true);
}

TEST(Parser_TEST_5, parser_brackets_complex_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "2 *x + (3 -x)/ (-2) +7.3";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ((stof(output.str()) - (19.55))< eps, true);
}

TEST(Parser_TEST_6, parser_divide_by_zero_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "3/ ( x - 5.5)";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ(output.str(), string("Division by zero\n"));
}

TEST(Parser_TEST_7, parser_invalid_string_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "*5 - x";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ(output.str(), string("Invalid string\n"));
}

TEST(Parser_TEST_8, parser_invalid_string_test) {
    stringstream input;
    stringstream output = stringstream();
	string s = "2x";
    double x = 5.5;
    input << s << endl;
    input << x;
    run_for_test(input, output);
    EXPECT_EQ(output.str(), string("Invalid string\n"));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}