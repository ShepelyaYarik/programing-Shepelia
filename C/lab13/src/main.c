/**
 * @file main.c
 * @brief точка входу та обробка аргументів командного рядка
 * @author Yaroslav Shepelia
 */

#include "lib.h"

/**
 * @brief головна функція програми
 *
 * Приймає аргументи з терміналу, викликає функцію обчислення розміру
 * та записує результат у вказаний файл.
 *
 * @param argc кількість аргументів командного рядка
 * @param argv масив рядків з аргументами
 * @return статус завершення програми (0 у разі успіху, 1 у разі помилки)
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_directory> <output_file>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    const char *output_file = argv[2];

    unsigned long long size = get_dir_size(dir_path);

    FILE *out = fopen(output_file, "w");
    if (out == NULL) {
        fprintf(stderr, "Помилка відкриття файлу для запису.\n");
        return 1;
    }

    write_formatted_size(out, size);
    
    fclose(out);

    return 0;
}