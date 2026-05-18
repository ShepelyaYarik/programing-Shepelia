/**
 * @file lib.h
 * @brief Заголовний файл з описом структур та прототипів функцій для роботи з колекцією мобільних телефонів.
 * * Файл містить визначення перерахувань, структур та об'єднань для імітації 
 * базового класу "Мобільний телефон" та його спадкоємців ("Кнопковий телефон", "Складаний телефон").
 */

#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @enum OSType
 * @brief Перелік підтримуваних операційних систем.
 */
typedef enum {
    OS_ANDROID,         /**< Операційна система Android */
    OS_IOS,             /**< Операційна система iOS */
    OS_SYMBIAN,         /**< Операційна система Symbian */
    OS_WINDOWS_PHONE    /**< Операційна система Windows Phone */
} OSType;

/**
 * @enum PhoneType
 * @brief Перелік типів телефонів (для ідентифікації "спадкоємців").
 */
typedef enum {
    TYPE_SMARTPHONE,    /**< Звичайний смартфон (базовий клас) */
    TYPE_PUSH_BUTTON,   /**< Кнопковий телефон (Спадкоємець 1) */
    TYPE_FOLDABLE       /**< Складаний телефон (Спадкоємець 2) */
} PhoneType;

/**
 * @struct ScreenSize
 * @brief Структура для зберігання розмірів екрану в пікселях.
 */
typedef struct {
    int width;          /**< Ширина екрану */
    int height;         /**< Висота екрану */
} ScreenSize;

/**
 * @struct PushButtonData
 * @brief Додаткові поля для спадкоємця "Кнопковий телефон".
 */
typedef struct {
    int is_grandma_phone; /**< Чи є бабусяфонами (1 - так, 0 - ні) */
    int button_count;     /**< Кількість фізичних кнопок */
} PushButtonData;

/**
 * @struct FoldableData
 * @brief Додаткові поля для спадкоємця "Складаний телефон".
 */
typedef struct {
    int folds_in_half;           /**< Чи складається телефон навпіл (1 - так, 0 - ні) */
    ScreenSize folded_screen;    /**< Розмір додаткового екрану у складеному стані */
} FoldableData;

/**
 * @struct MobilePhone
 * @brief Головна структура, що описує мобільний телефон.
 * * Включає базові поля та об'єднання (union) для зберігання 
 * специфічних даних залежно від типу телефону.
 */
typedef struct {
    int is_waterproof;  /**< Чи є водостійким (1 - так, 0 - ні) */
    int is_shockproof;  /**< Чи є ударостійким (1 - так, 0 - ні) */
    char model[50];     /**< Модель або повна назва телефону */
    int ram_mb;         /**< Об'єм оперативної пам'яті у мегабайтах */
    int storage_mb;     /**< Розмір внутрішнього сховища у мегабайтах */
    ScreenSize screen;  /**< Розмір головного екрану */
    OSType os;          /**< Операційна система пристрою */
    
    PhoneType type;     /**< Тип телефону (смартфон, кнопковий або складаний) */
    
    /**
     * @brief Об'єднання специфічних полів спадкоємців.
     */
    union {
        PushButtonData push_button; /**< Дані для кнопкового телефону */
        FoldableData foldable;      /**< Дані для складаного телефону */
    } specific;
} MobilePhone;

/**
 * @brief Зчитує масив структур телефонів з текстового файлу.
 * * @param filepath Шлях до файлу з даними.
 * @param phones Подвійний покажчик на масив структур (буде виділена пам'ять).
 * @param count Покажчик на змінну, куди буде записано кількість зчитаних елементів.
 */
void read_from_file(const char *filepath, MobilePhone **phones, int *count);

/**
 * @brief Виводить базову інформацію про всі телефони у масиві на екран.
 * * @param phones Покажчик на масив структур.
 * @param count Кількість елементів у масиві.
 */
void print_phones(MobilePhone *phones, int count);

/**
 * @brief Розраховує загальний об'єм оперативної пам'яті всіх телефонів.
 * * @param phones Покажчик на масив структур.
 * @param count Кількість елементів у масиві.
 * @return Загальний об'єм RAM у мегабайтах.
 */
long calculate_total_ram(MobilePhone *phones, int count);

/**
 * @brief Знаходить та виводить на екран кнопкові телефони, що НЕ є бабусяфонами.
 * * @param phones Покажчик на масив структур.
 * @param count Кількість елементів у масиві.
 */
void find_non_grandma_push_phones(MobilePhone *phones, int count);

/**
 * @brief Знаходить та виводить на екран усі складані телефони.
 * * @param phones Покажчик на масив структур.
 * @param count Кількість елементів у масиві.
 */
void find_foldable_phones(MobilePhone *phones, int count);

MobilePhone* find_max_storage(MobilePhone *phones , int count);
/**
 * @brief Сортує за ram_mb від найменшого до найбільшого
 * * @param phones Покажчик на масив структур.
 * @param count Кількість елементів у масиві.
 */
void sort_by_ram(MobilePhone *phones, int count);
#endif