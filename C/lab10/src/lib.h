/**
 * @file lib.h
 * @brief Заголовний файл бібліотеки роботи з матрицями.
 *
 * Цей файл містить прототипи функцій для створення матриць,
 * очищення пам'яті, отримання діагональних елементів та сортування.
 * * @author Yaroslav Shepelia
 * @date 2025-11-23
 */

#ifndef LIB_H
#define LIB_H

#include <stddef.h> 
/**
 * @brief Створює квадратну матрицю заданого розміру.
 * @param size Розмірність матриці (N).
 * @return int** Вказівник на матрицю або NULL у випадку помилки.
 */
int** create_matrix(size_t size);

/**
 * @brief Звільняє пам'ять, виділену під матрицю.
 * @param matrix Вказівник на матрицю.
 * @param size Розмірність матриці.
 */
void free_matrix(int** matrix, size_t size);

/**
 * @brief Отримує елементи головної діагоналі матриці.
 * @param matrix Вхідна матриця.
 * @param size Розмірність.
 * @param out_array Буфер для запису результату (має бути виділений заздалегідь).
 */
void get_diagonal(int** matrix, size_t size, int* out_array);

/**
 * @brief Сортує масив методом бульбашки.
 * @param array Масив для сортування.
 * @param size Розмір масиву.
 */
void sort_array(int* array, size_t size);
void fill_matrix_random(int** matrix, size_t size, int min, int max);

#endif