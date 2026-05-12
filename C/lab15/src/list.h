/**
 * @file list.h
 * @brief Опис структури динамічного масиву (списку) та методів для роботи з ним.
 */

#ifndef LIST_H
#define LIST_H

#include "entity.h"
#include <stddef.h>

/**
 * @struct PhoneList
 * @brief Структура, що представляє динамічний масив телефонів.
 */
typedef struct {
    MobilePhone *items; /**< Покажчик на динамічний масив елементів */
    size_t count;       /**< Поточна кількість елементів у списку */
    size_t capacity;    /**< Місткість виділеної пам'яті */
} PhoneList;

/**
 * @brief Ініціалізує порожній список.
 * @param list Покажчик на список.
 */
void list_init(PhoneList *list);

/**
 * @brief Звільняє пам'ять, виділену під масив.
 * @param list Покажчик на список.
 */
void list_free(PhoneList *list);

/**
 * @brief Виводить вміст списку на екран.
 * @param list Покажчик на список.
 */
void list_print(const PhoneList *list);

/**
 * @brief Додає об'єкт у кінець списку.
 * @param list Покажчик на список.
 * @param phone Об'єкт для додавання.
 */
void list_add(PhoneList *list, const MobilePhone *phone);

/**
 * @brief Видаляє об'єкт зі списку за індексом.
 * @param list Покажчик на список.
 * @param index Індекс елемента для видалення.
 */
void list_remove_at(PhoneList *list, size_t index);

/**
 * @brief Сортує вміст списку за об'ємом RAM (від меншого до більшого).
 * @param list Покажчик на список.
 */
void list_sort_by_ram(PhoneList *list);

/**
 * @brief Функція №1: Розрахувати загальний об'єм оперативної пам'яті.
 * @param list Покажчик на список.
 * @return Загальний об'єм RAM у мегабайтах.
 */
long list_calculate_total_ram(const PhoneList *list);

#endif // LIST_H

