/**
 * @file list.c
 * @brief Реалізація методів для керування динамічним масивом телефонів.
 *
 * Файл містить логіку взаємодії з купою (heap), алгоритми перерозподілу пам'яті
 * та маніпуляції з елементами списку виключно через вказівники.
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Ініціалізує список, виділяючи початковий блок пам'яті.
 *
 */
void list_init(PhoneList *list) {
    list->count = 0;
    list->capacity = 2; /**< Початкова місткість обрана малою для тестування realloc */

    /** Виділяємо пам'ять під структури у купі (heap) */
    list->items = (MobilePhone *)malloc(list->capacity * sizeof(MobilePhone));
    
    if (!list->items) {
        perror("Критична помилка: не вдалося ініціалізувати динамічний масив");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Звільняє пам'ять та зануляє вказівники для запобігання Memory Leaks.
 *
 */
void list_free(PhoneList *list) {
    if (list->items) {
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

/**
 * @brief Виводить список, звертаючись до елементів через арифметику вказівників.
 *
 */
void list_print(const PhoneList *list) {
    printf("--- Стан списку (Елементів: %zu, Місткість: %zu) ---\n", 
           list->count, list->capacity);
    
    for (size_t i = 0; i < list->count; i++) {
        /** Передаємо адресу i-го елемента: (items + i) */
        print_single_phone(list->items + i);
    }
    printf("----------------------------------------------------------\n");
}

/**
 * @brief Додає елемент, за потреби подвоюючи розмір масиву.
 *
 */
void list_add(PhoneList *list, const MobilePhone *phone) {
    /** Якщо масив заповнений, розширюємо його */
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        
        /** Використовуємо тимчасовий вказівник для безпеки даних */
        MobilePhone *new_items = (MobilePhone *)realloc(list->items, 
                                                        list->capacity * sizeof(MobilePhone));
        
        if (!new_items) {
            perror("Помилка: не вдалося розширити пам'ять масиву");
            return; 
        }
        
        list->items = new_items;
    }
    
    /** Копіюємо дані за допомогою розіменування вказівника */
    *(list->items + list->count) = *phone;
    list->count++;
}

/**
 * @brief Видаляє елемент та зсуває решту списку вліво.
 *
 */
void list_remove_at(PhoneList *list, size_t index) {
    if (index >= list->count) {
        fprintf(stderr, "Помилка: Невірний індекс %zu.\n", index);
        return;
    }
    
    /** Зсуваємо дані, використовуючи арифметику вказівників */
    for (size_t i = index; i < list->count - 1; i++) {
        *(list->items + i) = *(list->items + i + 1);
    }
    
    list->count--;
}

/**
 * @brief Сортування бульбашкою за об'ємом RAM.
 *
 */
void list_sort_by_ram(PhoneList *list) {
    if (list->count < 2) return;
    
    for (size_t i = 0; i < list->count - 1; i++) {
        for (size_t j = 0; j < list->count - i - 1; j++) {
            /** Порівнюємо значення через покажчики */
            if ((list->items + j)->ram_mb > (list->items + j + 1)->ram_mb) {
                /** Обмін цілими структурами */
                MobilePhone temp = *(list->items + j);
                *(list->items + j) = *(list->items + j + 1);
                *(list->items + j + 1) = temp;
            }
        }
    }
}

/**
 * @brief Обчислює загальну кількість RAM (Індивідуальне завдання).
 *
 */
long list_calculate_total_ram(const PhoneList *list) {
    long total = 0;
    for (size_t i = 0; i < list->count; i++) {
        total += (list->items + i)->ram_mb;
    }
    return total;
}