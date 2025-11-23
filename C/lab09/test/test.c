#include "../src/lib.h"
#include <check.h>
#include <stdlib.h>
START_TEST(test_sum)
{
    int input_data[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int expected_sum = 55; 

    int actual_sum = myfunction(input_data);

    ck_assert_int_eq(actual_sum, expected_sum);
}
END_TEST

START_TEST(test_sum_negative)
{
    int input_data[SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int expected_sum = -10;

    int actual_sum = myfunction(input_data);

    ck_assert_int_eq(actual_sum, expected_sum);  // ==
}
END_TEST

START_TEST(test_randgen_range)
{
    int number[SIZE];
    long min = 10;
    long max = 20;
    
    randgen(min, max, number);

    for (int i = 0; i < SIZE; i++) {
        ck_assert_int_ge(number[i], (int)min); // >=
        ck_assert_int_le(number[i], (int)max); // <=
    }
}
END_TEST
int main(void){
	Suite *s = suite_create("Programing");
	TCase *tc_core = tcase_create("lab09");
	tcase_add_test(tc_core, test_sum);
	tcase_add_test(tc_core, test_randgen_range);
	tcase_add_test(tc_core, test_sum_negative);
	suite_add_tcase(s, tc_core);
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;}