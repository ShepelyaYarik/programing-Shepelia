/**
 * @file lib.h
 * @brief заголовковий файл з прототипами функцій
 * @author Yaroslav Shepelia
 */

#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/**
 * @brief обчислює загальний розмір каталогу рекурсивно
 *
 * @param dir_path шлях до каталогу
 * @return загальний розмір у байтах
 */
unsigned long long get_dir_size(const char *dir_path);

/**
 * @brief форматує розмір згідно з вимогами та записує у файл
 *
 * @param file вказівник на файл для запису
 * @param size розмір у байтах
 */
void write_formatted_size(FILE *file, unsigned long long size);

#endif