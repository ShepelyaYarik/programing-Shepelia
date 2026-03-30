/**
 * @file main.c
 * @brief Головний файл програми. Взаємодія з користувачем.
 * @author Шепеля Ярослав
 * @date 2026-03-30
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {
    printf("Лабораторна робота №11\n");
    printf("Тема: Взаємодія з користувачем шляхом механізму введення/виведення\n");
    printf("Автор: Шепеля Ярослав\n");
    printf("Варіант: 5 (Визначити зворотню матрицю)\n\n");

    int n;
    printf("Введіть розмірність квадратної матриці (N): \n");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Помилка: невірний розмір матриці.\n");
        return 1;
    }

    float *mat = (float *)malloc((size_t)n * (size_t)n * sizeof(float));
    float *inv = (float *)malloc((size_t)n * (size_t)n * sizeof(float));

    if (mat == NULL || inv == NULL) {
        printf("Помилка: не вдалося виділити пам'ять.\n");
        return 1;
    }

    printf("Введіть елементи матриці (числа від -1000 до 1000):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float temp;
            if (scanf("%f", &temp) != 1) {
                printf("Помилка: очікувалось числове значення.\n");
                free(mat);
                free(inv);
                return 1;
            }
            
            if (temp <= -1000.0f || temp >= 1000.0f) {
                printf("Помилка: число %.3f виходить за межі діапазону.\n", temp);
                free(mat);
                free(inv);
                return 1;
            }
            
            *(mat + i * n + j) = temp;

            if (i == j) {
                *(inv + i * n + j) = 1.0f;
            } else {
                *(inv + i * n + j) = 0.0f;
            }
        }
    }

    int result = invert_matrix(mat, inv, n);
    
    if (result == 1) {
        printf("Помилка: матриця вироджена, зворотньої не існує.\n");
        free(mat);
        free(inv);
        return 1;
    }

    printf("\nЗворотня матриця:\n");
    for (int i = 0; i < n; i++) {
        printf("[ "); 
        
        for (int j = 0; j < n; j++) {
            printf("%8.02f ", *(inv + i * n + j));
        }
        
        printf("]\n"); 
    }
    free(mat);
    free(inv);

    return 0;
}