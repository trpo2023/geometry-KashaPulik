#include <ctest.h>
#include <libgeometry/lexer.h>

CTEST(lexer, this_is_the_end)
{
    char test_string[] = "circle(0 0, 1)\n";
    _Bool result = this_is_the_end(test_string);
    _Bool expected = 0;
    ASSERT_EQUAL(expected, result);

    char test_string_2[] = "circle(0 0, 1)";
    result = this_is_the_end(test_string_2);
    expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, string_to_double)
{
    char test_string[] = "circle(0 0, 1.53)";
    double result = string_to_double(test_string, 7, 7);
    double expected = 0;
    ASSERT_DBL_NEAR(expected, result);

    result = string_to_double(test_string, 12, 15);
    expected = 1.53;
    ASSERT_DBL_NEAR(expected, result);
}

CTEST(lexer, copy_letter_sequence)
{
    char test_string[] = "circle(0 0, 1)";
    unsigned int index = 8;
    char* result = copy_letter_sequence(test_string, &index);
    char expected[] = "circle";
    unsigned int expected_index = 6;
    ASSERT_STR(expected, result);
    ASSERT_EQUAL_U(expected_index, index);

    char bad_test_string[] = "123";
    result = copy_letter_sequence(bad_test_string, &index);
    ASSERT_NULL(result);

    free(result);
}

CTEST(lexer, tolower_string)
{
    char test_string[] = "CiRcle(0 0, 1)";
    tolower_string(test_string, 6);
    char expected[] = "circle(0 0, 1)";
    ASSERT_STR(expected, test_string);
}

CTEST(lexer, there_is_symbol)
{
    char test_string[] = "circle(0 0, 1)";
    _Bool result = there_is_symbol(test_string, 6, '(');
    _Bool expected = 1;
    ASSERT_EQUAL(expected, result);

    result = there_is_symbol(test_string, 0, 'g');
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, is_circle)
{
    char test_string[] = "circle(0 0, 1)";
    _Bool result = is_circle(test_string);
    _Bool expected = 1;
    ASSERT_EQUAL(expected, result);

    char bad_test_string[] = "circl(0 0, 1)";
    result = is_circle(bad_test_string);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, copy_part_of_string)
{
    char test_string[] = "circle(0 0, 1)";
    char* result_string = copy_part_of_string(test_string, 6, 14);
    char expected[] = "(0 0, 1)";
    ASSERT_STR(expected, result_string);

    char* bad_result_string = copy_part_of_string(test_string, 4, 4);
    ASSERT_NULL(bad_result_string);

    free(result_string);
    free(bad_result_string);
}

CTEST(lexer, skip_space)
{
    char test_string[] = "   circle(0 0, 1)";
    int result = skip_space(test_string, 0);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, skip_double)
{
    char test_string[] = "circle(0.0 0.0, 1.5)";
    int result = skip_double(test_string, 7);
    int expected = 10;
    ASSERT_EQUAL(expected, result);

    result = skip_double(test_string, 0);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, skip_digits)
{
    char test_string[] = "circle(0.005 0.0, 1.5)";
    int result = skip_digits(test_string, 9);
    int expected = 12;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, is_double)
{
    char test_string[] = "circle(0.005 0.0, 1.0x)";
    _Bool result = is_double(test_string, 7, 12);
    _Bool expected = 1;
    ASSERT_EQUAL(expected, result);

    result = is_double(test_string, 18, 22);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, empty_string)
{
    char empty_str[] = "    ";
    char not_empty_str[] = "   a";
    _Bool result = empty_string(empty_str, 0);
    _Bool expected = 1;
    ASSERT_EQUAL(expected, result);

    result = empty_string(not_empty_str, 0);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, circle_handling)
{
    char test_string[] = "circle(0 0, 1)";
    unsigned int index = 0;
    _Bool result = circle_handling(test_string, &index);
    _Bool expected = 1;
    unsigned int expected_index = 6;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);

    char bad_test_string[] = "circl(0 0, 1)";
    index = 0;
    result = circle_handling(bad_test_string, &index);
    expected = 0;
    expected_index = 0;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);
}

CTEST(lexer, bracket_handling)
{
    char test_string[] = "circle(0 0, 1)";
    unsigned int index = 6;
    _Bool result = bracket_handling(test_string, &index, 1);
    _Bool expected = 1;
    unsigned int expected_index = 7;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);

    index = 13;
    result = bracket_handling(test_string, &index, 2);
    expected = 1;
    expected_index = 14;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);

    char bad_test_string[] = "circle)0 0, 1)";
    index = 6;
    result = bracket_handling(bad_test_string, &index, 1);
    expected = 0;
    expected_index = 6;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);

    index = 6;
    result = bracket_handling(test_string, &index, 4);
    expected = 0;
    expected_index = 6;
    ASSERT_EQUAL(expected, result);
    ASSERT_EQUAL_U(expected_index, index);
}

CTEST(lexer, double_handling)
{
    char test_string[] = "circle(1 1.5, 1.x)";
    unsigned int index = 7;
    double result_parametr = 0;
    _Bool result = double_handling(test_string, &index, &result_parametr);
    unsigned int expected_index = 9;
    double expected_parametr = 1;
    _Bool expected = 1;
    ASSERT_EQUAL_U(expected_index, index);
    ASSERT_DBL_NEAR(expected_parametr, result_parametr);
    ASSERT_EQUAL(expected, result);

    index = 9;
    result_parametr = 0;
    result = double_handling(test_string, &index, &result_parametr);
    expected_index = 12;
    expected_parametr = 1.5;
    expected = 1;
    ASSERT_EQUAL_U(expected_index, index);
    ASSERT_DBL_NEAR(expected_parametr, result_parametr);
    ASSERT_EQUAL(expected, result);

    index = 14;
    result = double_handling(test_string, &index, &result_parametr);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, comma_handling)
{
    char test_string[] = "circle(0 0, 1)";
    unsigned int index = 10;
    _Bool result = comma_handling(test_string, &index);
    unsigned int expected_index = 12;
    _Bool expected = 1;
    ASSERT_EQUAL_U(expected_index, index);
    ASSERT_EQUAL(expected, result);

    char bad_test_string[] = "circle(0 0 1)";
    index = 10;
    result = comma_handling(bad_test_string, &index);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(lexer, end_handling)
{
    char test_string[] = "circle(0 0, 1)";
    unsigned int index = 14;
    _Bool result = end_handling(test_string, index);
    _Bool expected = 1;
    ASSERT_EQUAL(expected, result);

    index = 13;
    result = end_handling(test_string, index);
    expected = 0;
    ASSERT_EQUAL(expected, result);
}