/**
 * @file main.c
 * @brief Точка входу для демонстрації роботи програми.
 *
 * Цей файл містить функцію main, яка виконує базовий сценарій роботи
 * з бібліотекою lib.h.
 *
 * @note Програма не використовує printf/scanf. Дані задаються константами,
 * а результат перевіряється за допомогою відлагодника (GDB).
 *
 * @author Yaroslav Shepelia
 * @date 2025-11-23
 */

#include "lib.h"
#include <stdlib.h>
#include <time.h>
/** Макровизначення розміру матриці для демонстрації */
#define N 5

/**
 * @brief Головна функція програми.
 * * Виконує наступні кроки:
 * 1. Виділення пам'яті.
 * 2. Заповнення матриці тестовими даними.
 * 3. Отримання діагоналі.
 * 4. Сортування діагоналі.
 * 5. Очищення пам'яті.
 *
 * @return int Код повернення (0 - успіх).
 */
int main(void) {
	 srand((unsigned int)time(NULL));
    // 1. Створюємо матрицю
    int** matrix = create_matrix(N);
    int* result = (int*)malloc(N * sizeof(int));

    if (!matrix || !result) return 1;
    // 50  1   2
    // 3   10  4
    // 5   6   5
    
   // *(*(matrix + 0) + 0) = 50; *(*(matrix + 0) + 1) = 1; *(*(matrix + 0) + 2) = 2;
    //*(*(matrix + 1) + 0) = 3;  *(*(matrix + 1) + 1) = 10; *(*(matrix + 1) + 2) = 4;
   // *(*(matrix + 2) + 0) = 5;  *(*(matrix + 2) + 1) = 6;  *(*(matrix + 2) + 2) = 5;
   fill_matrix_random(matrix, N , 10 , 99);
    // 3. Отримуємо діагональ {50, 10, 5}
    get_diagonal(matrix, N, result); 

    // 4. Сортуємо {5, 10, 50}
    sort_array(result, N);

    // 5. Очищення пам'яті
    free_matrix(matrix, N);
    free(result);

    return 0;
}