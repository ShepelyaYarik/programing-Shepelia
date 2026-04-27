/**
 * @file main.c
 * @brief Головний файл програми. Відповідає за потокове введення/виведення даних.
 * @author Шепеля Ярослав (КН-925а)
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include<string.h>

/**
 * @brief Точка входу в програму.
 * * Ініціалізує динамічний масив для таблиці частот. Далі в циклі зчитує 
 * текст (з клавіатури або з файлу через pipe) блоками по 1024 байти,
 * накопичуючи статистику. Після завершення потоку введення (EOF) 
 * виводить форматовану частотну таблицю.
 * * @return 0 у разі успішного завершення програми, 1 у разі помилки (наприклад, з пам'яттю).
 */
int main() {
    printf("Лабораторна робота №12. Варіант 21 (Частотна таблиця)\n");
    printf("Виконав: студент групи КН-925а Шепеля Ярослав\n\n");

    char buffer[1024];
    
    int *freq = (int *)malloc(256 * sizeof(int));
    if (freq == NULL) return 1; 

    int total_chars = 0;
   memset(freq, 0, 256*sizeof(int));

    printf("Введіть текст (для продовження ctrl+d)\n");
    
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        calc_frequency(buffer, freq, &total_chars);
    }

    if (total_chars > 0) {
        printf("\nЗагальна кількість символів: %d\n", total_chars);
        printf("Частотна таблиця:\n");
        printf("--------------------------------\n");
        
        for (int i = 0; i < 256; i++) {
            if (*(freq + i) > 0) { 
                float percentage = ((float)*(freq + i) * 100.0f) / (float)total_chars;
                
                // Друковані символи виводимо як текст, невидимі/службові — як шістнадцятковий код
                if (i >= 32 && i <= 126) {
                    printf("Символ '%c': %3d разів (%5.2f%%)\n", i, *(freq + i), percentage);
                } else {
                    printf("Код 0x%02X : %3d разів (%5.2f%%)\n", i, *(freq + i), percentage);
                }
            }
        }
        printf("--------------------------------\n");
    } else {
        printf("\nВи ввели порожній рядок.\n");
    }
	for(int i = 0; i<=(int)strlen(buffer); i++){
		printf("%c" , buffer[i] );
	}
    // Звільнення виділеної пам'яті
    free(freq);
    return 0;
}