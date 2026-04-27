/**
 * @file lib.c
 * @brief реалізація логіки обходу файлової системи та форматування
 * @author Yaroslav Shepelia
 */

#include "lib.h"

/**
 * @brief обчислює загальний розмір каталогу рекурсивно
 *
 * Функція відкриває каталог, перебирає всі елементи та додає їх розміри.
 * Якщо зустрічає вкладену папку, викликає саму себе.
 *
 * @param dir_path шлях до каталогу
 * @return загальний розмір у байтах
 */
unsigned long long get_dir_size(const char *dir_path) {
    unsigned long long total_size = 0;
    DIR *dir = opendir(dir_path);
    
    if (dir == NULL) {
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        struct stat statbuf;
        if (lstat(path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                total_size += get_dir_size(path);
            } else {
                total_size += (unsigned long long)statbuf.st_size;
            }
        }
    }
    
    closedir(dir);
    return total_size;
}

/**
 * @brief форматує розмір згідно з вимогами та записує у файл
 *
 * Перетворює байти у більші одиниці виміру (KB, MB, GB тощо),
 * ділячи на 1000, та залишає два знаки після коми.
 *
 * @param file вказівник на файл для запису
 * @param size розмір у байтах
 */
void write_formatted_size(FILE *file, unsigned long long size) {
    if (size == 0) {
        fprintf(file, "0 B\n");
        return;
    }

    const char *units[] = {"B", "KB", "MB", "GB", "TB", "PB"};
    int unit_index = 0;
    double formatted_size = (double)size;

    while (formatted_size >= 1000.0 && unit_index < 5) {
        formatted_size /= 1000.0;
        unit_index++;
    }

    fprintf(file, "%.2f %s\n", formatted_size, units[unit_index]);
}