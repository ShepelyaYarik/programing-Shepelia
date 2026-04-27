#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/lib.h"

START_TEST(test_write_formatted_size) {
    // створюємо тимчасовий файл для запису
    FILE *f = fopen("test_dummy_output.txt", "w+");
    ck_assert_ptr_nonnull(f);

    write_formatted_size(f, 0);
    write_formatted_size(f, 999);
    write_formatted_size(f, 1000);
    write_formatted_size(f, 1500000);

    // повертаємось на початок файлу для читання
    rewind(f);
    char buffer[256];

    // перевіряємо результати
    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "0 B\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "999.00 B\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "1.00 KB\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "1.50 MB\n");

    // закриваємо та видаляємо тестовий файл
    fclose(f);
    remove("test_dummy_output.txt");
}
END_TEST

START_TEST(test_get_dir_size) {
    // перевірка неіснуючого каталогу (повинно повернути 0)
    unsigned long long size_empty = get_dir_size("non_existent_dir_12345");
    ck_assert_int_eq(size_empty, 0);

    // перевірка існуючого каталогу зі створеним файлом
    system("mkdir -p test_dummy_dir");
    system("echo -n 'hello' > test_dummy_dir/a.txt"); // рівно 5 байтів
    
    unsigned long long size = get_dir_size("test_dummy_dir");
    
    // загальний об'єм має бути принаймні 5 байтів + вага самої папки
    ck_assert(size >= 5); 
    
    // очищення тимчасового каталогу
    system("rm -rf test_dummy_dir");
}
END_TEST

int main(void) {
    Suite *s = suite_create("Lab13_Directory_Size");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_write_formatted_size);
    tcase_add_test(tc_core, test_get_dir_size);

    suite_add_tcase(s, tc_core);
    SRunner *sr = srunner_create(s);
    
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}