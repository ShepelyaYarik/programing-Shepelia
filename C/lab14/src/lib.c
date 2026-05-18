/**
 * @file lib.c
 * @brief Реалізація функцій для роботи з масивом структур MobilePhone.
 */

#include "lib.h"

void read_from_file(const char *filepath, MobilePhone **phones, int *count) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", count) != 1) {
        *count = 0;
        fclose(file);
        return;
    }

    *phones = (MobilePhone *)malloc((size_t)(*count) * sizeof(MobilePhone));
    if (!*phones) {
        perror("Помилка виділення пам'яті");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < *count; i++) {
        int os_int, type_int;
        fscanf(file, "%d %d %49s %d %d %d %d %d %d", 
               &((*phones + i)->is_waterproof),
               &((*phones + i)->is_shockproof),
               (*phones + i)->model,
               &((*phones + i)->ram_mb),
               &((*phones + i)->storage_mb),
               &((*phones + i)->screen.width),
               &((*phones + i)->screen.height),
               &os_int,
               &type_int);
               
        (*phones + i)->os = (OSType)os_int;
        (*phones + i)->type = (PhoneType)type_int;

        if ((*phones + i)->type == TYPE_PUSH_BUTTON) {
            fscanf(file, "%d %d", 
                   &((*phones + i)->specific.push_button.is_grandma_phone),
                   &((*phones + i)->specific.push_button.button_count));
        } else if ((*phones + i)->type == TYPE_FOLDABLE) {
            fscanf(file, "%d %d %d", 
                   &((*phones + i)->specific.foldable.folds_in_half),
                   &((*phones + i)->specific.foldable.folded_screen.width),
                   &((*phones + i)->specific.foldable.folded_screen.height));
        }
    }
    fclose(file);
}

void print_phones(MobilePhone *phones, int count) {
    for (int i = 0; i < count; i++) {
        printf("Модель: %s | RAM: %d МБ | Тип: %d\n", 
               (phones + i)->model, (phones + i)->ram_mb, (phones + i)->type);
    }
}

long calculate_total_ram(MobilePhone *phones, int count) {
    long total_ram = 0;
    for (int i = 0; i < count; i++) {
        total_ram += (phones + i)->ram_mb;
    }
    return total_ram;
}

MobilePhone* find_max_storage(MobilePhone *phones , int count){
	 MobilePhone *max_phone = phones ;
	 for(int i=1; i<count; i++){
		 if((phones + i)->storage_mb > max_phone->storage_mb){
			 max_phone = (phones + i);
		 }
	 }
	 return max_phone;
 }
void find_non_grandma_push_phones(MobilePhone *phones, int count) {
    printf("\n--- Кнопкові телефони (НЕ бабусяфони) ---\n");
    for (int i = 0; i < count; i++) {
        if ((phones + i)->type == TYPE_PUSH_BUTTON && 
            (phones + i)->specific.push_button.is_grandma_phone == 0) {
            printf("- %s (Кнопок: %d)\n", 
                   (phones + i)->model, 
                   (phones + i)->specific.push_button.button_count);
        }
    }
}

void find_foldable_phones(MobilePhone *phones, int count) {
    printf("\n--- Складані телефони ---\n");
    for (int i = 0; i < count; i++) {
        if ((phones + i)->type == TYPE_FOLDABLE) {
            printf("- %s (Екран у складеному стані: %dx%d)\n", 
                   (phones + i)->model, 
                   (phones + i)->specific.foldable.folded_screen.width, 
                   (phones + i)->specific.foldable.folded_screen.height);
        }
    }
}


void sort_by_ram(MobilePhone *phones, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // Використання арифметики покажчиків замість індексів []
            if ((phones + j)->ram_mb > (phones + j + 1)->ram_mb) {
                MobilePhone temp = *(phones + j);
                *(phones + j) = *(phones + j + 1);
                *(phones + j + 1) = temp;
            }
        }
    }
}