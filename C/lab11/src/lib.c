/**
 * @file lib.c
 * @brief Реалізація функції знаходження зворотньої матриці.
 * @author Шепеля Ярослав
 * @date 2026-03-30
 */

#include "lib.h"
#include <math.h>

int invert_matrix(float *mat, float *inv, int n) {
    for (int i = 0; i < n; i++) {
        float pivot = *(mat + i * n + i);
        
        // перевірка на нуль на головній діагоналі
        if (fabs(pivot) < 0.0001f) {
            int swap_row = -1;
            for (int k = i + 1; k < n; k++) {
                if (fabs(*(mat + k * n + i)) > 0.0001f) {
                    swap_row = k;
                    break;
                }
            }
            
            // якщо не знайшли рядок для обміну, матриця вироджена
            if (swap_row == -1) {
                return 1; 
            }
            // перестановка рядків 
            for (int j = 0; j < n; j++) {
                float temp_val = *(mat + i * n + j);
                *(mat + i * n + j) = *(mat + swap_row * n + j);
                *(mat + swap_row * n + j) = temp_val;
                
                temp_val = *(inv + i * n + j);
                *(inv + i * n + j) = *(inv + swap_row * n + j);
                *(inv + swap_row * n + j) = temp_val;
            }
            pivot = *(mat + i * n + i);
        }

        // ділимо рядок на pivot
        for (int j = 0; j < n; j++) {
            *(mat + i * n + j) /= pivot;
            *(inv + i * n + j) /= pivot;
        }

        // віднімаємо від інших рядків
        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = *(mat + k * n + i);
                for (int j = 0; j < n; j++) {
                    *(mat + k * n + j) -= factor * *(mat + i * n + j);
                    *(inv + k * n + j) -= factor * *(inv + i * n + j);
                }
            }
        }
    }
    
    return 0;
}