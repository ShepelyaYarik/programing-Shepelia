#include <gtest/gtest.h>
#include <string>
#include "list.hpp"

using std::string;

// Тест базових операцій зі списком чисел
TEST(TemplateListTest, BasicIntOperations) {
    List<int> list;
    
    list.append(10);
    list.append(20);
    list.append(5);
    
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 5);
}

// Тест пошуку мінімуму та індексу
TEST(TemplateListTest, MinAndIndexOf) {
    List<int> list;
    list.append(42);
    list.append(15);
    list.append(88);
    
    EXPECT_EQ(list.min(), 15);
    EXPECT_EQ(list.indexOf(88), 2);
    EXPECT_EQ(list.indexOf(999), -1);
}

// Тест видалення та сортування
TEST(TemplateListTest, SortAndRemove) {
    List<int> list;
    list.append(10);
    list.append(5);
    list.append(100);
    list.append(1);
    
    list.removeAt(1); // видалили 5
    list.sort();      // сортуємо 10, 100, 1 -> 1, 10, 100
    
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 10);
    EXPECT_EQ(list[2], 100);
}

// Тест роботи з рядками std::string
TEST(TemplateListTest, StringSupport) {
    List<string> list;
    list.append(string("Orange"));
    list.append(string("Apple"));
    list.append(string("Banana"));
    
    EXPECT_EQ(list.min(), "Apple");
    
    list.sort();
    EXPECT_EQ(list[0], "Apple");
    EXPECT_EQ(list[1], "Banana");
}

// Тест обробки винятків (генерація out_of_range)
TEST(TemplateListTest, ExceptionHandling) {
    List<int> emptyList;
    
    // Перевірка, що min() для порожнього списку викликає виняток
    ASSERT_THROW(emptyList.min(), std::out_of_range);
    
    // Перевірка виходу за межі масиву
    ASSERT_THROW(emptyList.removeAt(0), std::out_of_range);
}