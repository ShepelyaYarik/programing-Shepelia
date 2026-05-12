/**
 * @file test.c
 * @brief Модульні тести для перевірки динамічного масиву з використанням бібліотеки Check.
 */

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "../src/list.h"

// Тест: Ініціалізація та додавання елемента
START_TEST(test_list_add_and_count)
{
    PhoneList list;
    list_init(&list);
    
    ck_assert_uint_eq(list.count, 0);
	print_single_phone(list.items + 0);
    MobilePhone p1;
    memset(&p1, 0, sizeof(MobilePhone));
    p1.ram_mb = 1024;
    
    list_add(&list, &p1);
    ck_assert_uint_eq(list.count, 1);
    ck_assert_int_eq((list.items + 0)->ram_mb, 1024);
    
    list_free(&list);
}
END_TEST

// Тест: Видалення елемента за індексом
START_TEST(test_list_remove)
{
    PhoneList list;
    list_init(&list);
    
    MobilePhone p1, p2;
    memset(&p1, 0, sizeof(MobilePhone)); p1.ram_mb = 100;
    memset(&p2, 0, sizeof(MobilePhone)); p2.ram_mb = 200;
    
    list_add(&list, &p1);
    list_add(&list, &p2);
    
    list_remove_at(&list, 0); 
    
    ck_assert_uint_eq(list.count, 1);
    ck_assert_int_eq((list.items + 0)->ram_mb, 200); 
    
    list_free(&list);
}
END_TEST

// Тест: Розрахунок загального об'єму RAM (Функція №1)
START_TEST(test_list_calculate_ram)
{
    PhoneList list;
    list_init(&list);
    
    MobilePhone p1, p2;
    memset(&p1, 0, sizeof(MobilePhone)); p1.ram_mb = 1024;
    memset(&p2, 0, sizeof(MobilePhone)); p2.ram_mb = 2048;
    
    list_add(&list, &p1);
    list_add(&list, &p2);
    
    long total = list_calculate_total_ram(&list);
    ck_assert_int_eq(total, 3072);
    
    list_free(&list);
}
END_TEST

// Тест: Сортування масиву
START_TEST(test_list_sort)
{
    PhoneList list;
    list_init(&list);
    
    MobilePhone p1, p2, p3;
    memset(&p1, 0, sizeof(MobilePhone)); p1.ram_mb = 4096;
    memset(&p2, 0, sizeof(MobilePhone)); p2.ram_mb = 1024;
    memset(&p3, 0, sizeof(MobilePhone)); p3.ram_mb = 2048;
    
    list_add(&list, &p1);
    list_add(&list, &p2);
    list_add(&list, &p3);
    
    list_sort_by_ram(&list);
    
    ck_assert_int_eq((list.items + 0)->ram_mb, 1024);
    ck_assert_int_eq((list.items + 1)->ram_mb, 2048);
    ck_assert_int_eq((list.items + 2)->ram_mb, 4096);
    
    list_free(&list);
}
END_TEST

// Формування набору тестів (Suite)
Suite *list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("PhoneList");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_list_add_and_count);
    tcase_add_test(tc_core, test_list_remove);
    tcase_add_test(tc_core, test_list_calculate_ram);
    tcase_add_test(tc_core, test_list_sort);
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = list_suite();
    sr = srunner_create(s);

    // Запуск тестів
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}