/**
 * @file entity.h
 * @brief Опис структури MobilePhone та пов'язаних типів.
 */

#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    OS_ANDROID,
    OS_IOS,
    OS_SYMBIAN,
    OS_WINDOWS_PHONE
} OSType;

typedef enum {
    TYPE_SMARTPHONE,
    TYPE_PUSH_BUTTON,
    TYPE_FOLDABLE
} PhoneType;

typedef struct {
    int width;
    int height;
} ScreenSize;

typedef struct {
    int is_grandma_phone;
    int button_count;
} PushButtonData;

typedef struct {
    int folds_in_half;
    ScreenSize folded_screen;
} FoldableData;

/**
 * @struct MobilePhone
 * @brief Структура, що описує мобільний телефон.
 */
typedef struct {
    int is_waterproof;
    int is_shockproof;
    char model[50];
    int ram_mb;
    int storage_mb;
    ScreenSize screen;
    OSType os;
    PhoneType type;
    union {
        PushButtonData push_button;
        FoldableData foldable;
    } specific;
} MobilePhone;

/**
 * @brief Виводить інформацію про один телефон.
 * @param phone Покажчик на телефон.
 */
void print_single_phone(const MobilePhone *phone);

#endif // ENTITY_H