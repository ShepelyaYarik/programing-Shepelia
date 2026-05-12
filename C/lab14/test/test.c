#include "../src/lib.h"
#include <assert.h>
#include <string.h>

// 1. Тестування читання з файлу та виводу (збільшує покриття)
void test_read_and_print() {
    const char *test_filepath = "test_temp_input.txt";
    
    // Створюємо тимчасовий файл для тесту
    FILE *f = fopen(test_filepath, "w");
    assert(f != NULL);
    fprintf(f, "1\n");
    // 1(водостійкий) 0(ударостійкий) Модель RAM ROM Ширина Висота ОС(0) Тип(0)
    fprintf(f, "1 0 Test_Pixel_Simulator 4096 128000 1080 1920 0 0\n");
    fclose(f);

    MobilePhone *phones = NULL;
    int count = 0;

    // Викликаємо функцію з lib.c
    read_from_file(test_filepath, &phones, &count);
    
    // Перевіряємо, чи правильно зчиталося
    assert(count == 1);
    assert(phones != NULL);
    assert(strcmp(phones[0].model, "Test_Pixel_Simulator") == 0);
    assert(phones[0].ram_mb == 4096);

    // Викликаємо функцію друку (щоб покрити ці рядки коду)
    printf("\n--- Тестовий вивід print_phones ---\n");
    print_phones(phones, count);

    // Прибираємо за собою
    free(phones);
    remove(test_filepath); // видаляємо тимчасовий файл
    
    printf("[OK] test_read_and_print пройдено.\n");
}

// 2. Тестування розрахунку загального об'єму оперативної пам'яті
void test_calculate_total_ram() {
    MobilePhone phones[3];
    
    phones[0].ram_mb = 1024;
    phones[1].ram_mb = 2048;
    phones[2].ram_mb = 4096;

    long total = calculate_total_ram(phones, 3);

    assert(total == 7168);
    printf("[OK] test_calculate_total_ram пройдено.\n");
}

// 3. Тестування логіки пошуку специфічних телефонів
void test_find_functions() {
    MobilePhone phones[3];

    phones[0].type = TYPE_SMARTPHONE;
    strcpy(phones[0].model, "Google Pixel 6 Pro");

    phones[1].type = TYPE_PUSH_BUTTON;
    strcpy(phones[1].model, "Nokia 3310");
    phones[1].specific.push_button.is_grandma_phone = 0;
    phones[1].specific.push_button.button_count = 15;

    phones[2].type = TYPE_FOLDABLE;
    strcpy(phones[2].model, "Samsung Z Flip");
    phones[2].specific.foldable.folds_in_half = 1;
    phones[2].specific.foldable.folded_screen.width = 1080;
    phones[2].specific.foldable.folded_screen.height = 2640;

    printf("\n--- Вивід функцій пошуку ---\n");
    find_non_grandma_push_phones(phones, 3);
    find_foldable_phones(phones, 3);
    
    printf("[OK] test_find_functions пройдено.\n");
}

int main() {
    printf("Запуск модульних тестів...\n");
    
    test_read_and_print();
    test_calculate_total_ram();
    test_find_functions();
    
    printf("\nВсі тести успішно завершені!\n");
    return EXIT_SUCCESS;
}