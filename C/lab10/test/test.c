/**
 * @file test.c
 * @brief Модульні тести для бібліотеки lib.h.
 *
 * Використовує фреймворк 'Check' для автоматичної перевірки
 * коректності роботи функцій create_matrix, get_diagonal, sort_array.
 *
 * @author Yaroslav Shepelia
 * @date 2025-11-23
 */

#include "../src/lib.h"
#include <check.h>
#include <stdlib.h>

/** Розмір матриці для тестів */
#define SIZE 3

/**
 * @brief Тест отримання діагоналі.
 * * Перевіряє, чи правильно функція вибирає елементи з індексами [i][i].
 */
START_TEST(test_get_diagonal)
{
    // Arrange (Підготовка)
    int** mat = create_matrix(SIZE);
    int* result = (int*)malloc(SIZE * sizeof(int));
    
    *(*(mat + 0) + 0) = 10;
    *(*(mat + 1) + 1) = 20;
    *(*(mat + 2) + 2) = 30;

    // Act (Дія)
    get_diagonal(mat, SIZE, result);

    // Assert (Перевірка)
    ck_assert_int_eq(*(result + 0), 10);
    ck_assert_int_eq(*(result + 1), 20);
    ck_assert_int_eq(*(result + 2), 30);

    // Cleanup (Очищення)
    free_matrix(mat, SIZE);
    free(result);
}
END_TEST

/**
 * @brief Тест сортування масиву.
 * * Перевіряє, чи правильно сортується масив у порядку зростання.
 */
START_TEST(test_sort_array)
{
    int* arr = (int*)malloc(SIZE * sizeof(int));
    *(arr + 0) = 50;
    *(arr + 1) = 10;
    *(arr + 2) = 30;

    sort_array(arr, SIZE);

    ck_assert_int_eq(*(arr + 0), 10);
    ck_assert_int_eq(*(arr + 1), 30);
    ck_assert_int_eq(*(arr + 2), 50);

    free(arr);
}
END_TEST

/**
 * @brief Точка входу для запуску тестів.
 * * Створює тестовий набір (Suite), додає кейси та запускає перевірку.
 * @return int EXIT_SUCCESS якщо помилок немає, інакше EXIT_FAILURE.
 */
int main(void)
{
    Suite *s = suite_create("Програмування");
    TCase *tc_core = tcase_create("Lab10");

    tcase_add_test(tc_core, test_get_diagonal);
    tcase_add_test(tc_core, test_sort_array);

    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}