/**
 * @file lib.c
 * @brief Реалізація функції підрахунку частоти символів.
 * @author Шепеля Ярослав (КН-925а)
 */

#include "lib.h"

void calc_frequency(const char *str, int *freq, int *total_chars) {
    //  Проходимо по рядку до символу кінця '\0'
    while (*str != '\0') {
        if (*str != '\n') {
            // (unsigned char) гарантує, що код символу не буде від'ємним, для кирилиці)
            (*(freq + (unsigned char)*str))++;
            (*total_chars)++;
        }
        str++; 
    }
}