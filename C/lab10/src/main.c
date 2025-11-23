#include "lib.h"
#include <stdlib.h>

// Визначаємо константу розміру
#define N 3

int main(void) {
    // 1. Створюємо матрицю
    int** matrix = create_matrix(N);
    int* result = (int*)malloc(N * sizeof(int));

    // Якщо пам'яті немає — аварійний вихід (хоча в lab-ах це рідкість)
    if (!matrix || !result) return 1;

    // 2. Заповнюємо матрицю КОНСТАНТАМИ (імітація вводу)
    // Матриця:
    // 50  1   2
    // 3   10  4
    // 5   6   5
    
    // Рядок 0
    *(*(matrix + 0) + 0) = 50; 
    *(*(matrix + 0) + 1) = 1; 
    *(*(matrix + 0) + 2) = 2;
    
    // Рядок 1
    *(*(matrix + 1) + 0) = 3;  
    *(*(matrix + 1) + 1) = 10; 
    *(*(matrix + 1) + 2) = 4;
    
    // Рядок 2
    *(*(matrix + 2) + 0) = 5;  
    *(*(matrix + 2) + 1) = 6;  
    *(*(matrix + 2) + 2) = 5;

    // 3. Виконуємо бізнес-логіку
    // Тут викладач поставить Breakpoint, щоб перевірити matrix
    get_diagonal(matrix, N, result); 
    // result зараз: {50, 10, 5}

    // Тут викладач перевірить сортування
    sort_array(result, N);
    // result зараз: {5, 10, 50}

    // 4. Очищення пам'яті
    free_matrix(matrix, N);
    free(result);

    return 0;
}