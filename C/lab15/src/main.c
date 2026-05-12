/**
 * @file main.c
 * @brief Головний файл програми для демонстрації роботи динамічного масиву.
 */

#include <stdio.h>
#include <string.h>
#include "list.h"

int main() {
    PhoneList my_list;
    list_init(&my_list);

    MobilePhone p1;
    memset(&p1, 0, sizeof(MobilePhone));
    strcpy(p1.model, "Nokia 3310");
    p1.ram_mb = 16;
    p1.type = TYPE_PUSH_BUTTON;

    MobilePhone p2;
    memset(&p2, 0, sizeof(MobilePhone));
    strcpy(p2.model, "Samsung Galaxy S23");
    p2.ram_mb = 8192;
    p2.type = TYPE_SMARTPHONE;

    MobilePhone p3;
    memset(&p3, 0, sizeof(MobilePhone));
    strcpy(p3.model, "iPhone 13");
    p3.ram_mb = 4096;
    p3.type = TYPE_SMARTPHONE;

    // 1. Додавання об'єктів
    printf("Додавання об'єктів...\n");
    list_add(&my_list, &p1);
    list_add(&my_list, &p2);
    list_add(&my_list, &p3);

    // 2. Вивід вмісту
    list_print(&my_list);

    // 3. Розрахунок загального об'єму оперативної пам'яті (Функція №1)
    long total_ram = list_calculate_total_ram(&my_list);
    printf("Загальний об'єм RAM: %ld МБ\n\n", total_ram);

    // 4. Сортування
    printf("Сортування за RAM...\n");
    list_sort_by_ram(&my_list);
    list_print(&my_list);

    // 5. Видалення за індексом (видалимо iPhone 13, який зараз на 1-му індексі після сортування: 16 -> 4096 -> 8192)
    printf("Видалення елемента за індексом 1...\n");
    list_remove_at(&my_list, 1);
    list_print(&my_list);

    // Звільнення пам'яті (запобігання витокам пам'яті для valgrind)
    list_free(&my_list);

    return 0;
}