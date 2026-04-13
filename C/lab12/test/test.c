/**
 * @file test.c
 * @brief Файл з модульними тестами для перевірки логіки підрахунку частот.
 * @author Шепеля Ярослав (КН-925а)
 */

#include <check.h>
#include <stdlib.h>
#include "../src/lib.h"

/**
 * @brief Тестування на звичайному слові без спецсимволів.
 */
START_TEST(test_calc_frequency_normal) {
    const char *test_str = "hello";
    int freq[256] = {0}; 
    int total = 0;

    calc_frequency(test_str, freq, &total);

    ck_assert_int_eq(total, 5);
    ck_assert_int_eq(*(freq + 'h'), 1);
    ck_assert_int_eq(*(freq + 'e'), 1);
    ck_assert_int_eq(*(freq + 'l'), 2); 
    ck_assert_int_eq(*(freq + 'o'), 1);
    ck_assert_int_eq(*(freq + 'a'), 0); 
}
END_TEST

/**
 * @brief Тестування на порожньому рядку (імітація натискання Enter).
 */
START_TEST(test_calc_frequency_empty) {
    const char *test_str = "\n"; 
    int freq[256] = {0};
    int total = 0;

    calc_frequency(test_str, freq, &total);

    ck_assert_int_eq(total, 0); 
}
END_TEST

/**
 * @brief Формування набору тестів.
 */
Suite *calc_frequency_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Frequency Calculator");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_calc_frequency_normal);
    tcase_add_test(tc_core, test_calc_frequency_empty);
    
    suite_add_tcase(s, tc_core);

    return s;
}

/**
 * @brief Головна функція для запуску модульних тестів.
 */
int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = calc_frequency_suite(); 
    sr = srunner_create(s);     

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}