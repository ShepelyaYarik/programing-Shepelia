/**
 * @file main.c
 * @brief Головний файл програми для роботи з колекцією мобільних телефонів.
 * * Цей файл містить точку входу в програму (функцію main). Він демонструє
 * читання даних про мобільні телефони з файлу, вивід їх на екран та використання
 * методів для пошуку специфічних пристроїв згідно з індивідуальним завданням.
 */

#include "lib.h"

/**
 * @brief Головна функція програми (точка входу).
 * * Зчитує шлях до вхідного файлу з аргументів командного рядка, ініціалізує
 * масив структур, викликає функції обробки даних та звільняє виділену пам'ять.
 * * @param argc Кількість аргументів командного рядка.
 * @param argv Масив рядків з аргументами (argv[1] очікується як шлях до файлу).
 * @return EXIT_SUCCESS у разі успішного виконання, EXIT_FAILURE у разі помилки.
 */
int main(int argc, char *argv[]) {
    // Перевірка наявності аргументу шляху до файлу
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <шлях_до_вхідного_файлу>\n", argv[0]);
        return EXIT_FAILURE;
    }

    MobilePhone *phones = NULL;
    int count = 0;

    // 1. Зчитування масиву з файлу
    read_from_file(argv[1], &phones, &count);

    printf("Зчитано телефонів: %d\n", count); // 2. Вивід базової інформації
    sort_by_ram(phones, count);    
    print_phones(phones, count);

    long total_ram = calculate_total_ram(phones, count);
    printf("\nЗагальний об'єм RAM усіх пристроїв: %ld МБ\n", total_ram);

    find_non_grandma_push_phones(phones, count);
    find_foldable_phones(phones, count);

    free(phones);

    return EXIT_SUCCESS;
}