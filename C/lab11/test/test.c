/**
 * @file test.c
 * @brief Файл з модульними тестами для перевірки роботи математичної логіки.
 * @author Шепеля Ярослав
 * @date 2026-03-30
 */

#include <check.h>
#include <stdlib.h>
#include <math.h>
#include "../src/lib.h"

/**
 * @brief Тест для перевірки правильного знаходження зворотньої матриці.
 * * Перевіряє роботу функції на коректній матриці 2х2.
 * Очікується успішне виконання (код 0) та правильні значення результату.
 */
START_TEST(test_invert_matrix_normal) {
    int n = 2;
    // початкова матриця: [4 7]
    //                    [2 6]
    float mat[] = {4.0f, 7.0f, 2.0f, 6.0f};
    
    // обов'язково ініціалізуємо масив як одиничну матрицю перед передачею
    float inv[4] = {1.0f, 0.0f, 0.0f, 1.0f}; 
    
    int result = invert_matrix(mat, inv, n);
    
    // перевіряємо, що функція повернула 0 (успіх)
    ck_assert_int_eq(result, 0);

    // очікувана зворотня матриця: [ 0.6 -0.7]
    //                             [-0.2  0.4]
    ck_assert_float_eq_tol(inv[0], 0.6f, 0.001f);
    ck_assert_float_eq_tol(inv[1], -0.7f, 0.001f);
    ck_assert_float_eq_tol(inv[2], -0.2f, 0.001f);
    ck_assert_float_eq_tol(inv[3], 0.4f, 0.001f);
}
END_TEST

/**
 * @brief Тест для перевірки реакції на вироджену матрицю.
 * * Перевіряє роботу функції на матриці 2х2, визначник якої дорівнює нулю.
 * Очікується повернення коду помилки (1).
 */
START_TEST(test_invert_matrix_singular) {
    int n = 2;
    // вироджена матриця: [1 2]
    //                    [2 4]
    float mat[] = {1.0f, 2.0f, 2.0f, 4.0f}; 
    
    // обов'язково ініціалізуємо масив як одиничну матрицю
    float inv[4] = {1.0f, 0.0f, 0.0f, 1.0f}; 
    
    int result = invert_matrix(mat, inv, n);
    
    // перевіряємо, що функція повернула 1 (помилка - матриця вироджена)
    ck_assert_int_eq(result, 1); 
}
END_TEST

/**
 * @brief Створення набору тестів для лабораторної роботи.
 * @return Вказівник на створений набір тестів.
 */
Suite *lab11_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Lab11");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_invert_matrix_normal);
    tcase_add_test(tc_core, test_invert_matrix_singular);
    suite_add_tcase(s, tc_core);

    return s;
}

/**
 * @brief Головна функція для запуску тестів.
 * @return EXIT_SUCCESS, якщо всі тести пройдено, інакше EXIT_FAILURE.
 */
int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = lab11_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}