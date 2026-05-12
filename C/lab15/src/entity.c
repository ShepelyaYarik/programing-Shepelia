/**
 * @file entity.c
 * @brief Реалізація функцій для роботи з однією сутністю MobilePhone.
 */

#include <stdio.h>
#include "entity.h"

void print_single_phone(const MobilePhone *phone) {
    if (!phone) return;
    printf("Модель: %s | RAM: %d МБ | Тип: %d\n", phone->model, phone->ram_mb, phone->type);
}

