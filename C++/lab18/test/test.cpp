/**
 * @file test.cpp
 * @brief Файл модульних тестів (gtest) для перевірки серіалізації, десеріалізації та роботи з файлами.
 */

#include <gtest/gtest.h>
#include "../src/list.h"
#include <fstream>

using std::string;

/**
 * @brief Тест валідації методів toString та fromString для сутностей.
 */
TEST(EntityTest, ToStringAndFromString) {
    ButtonPhone original(true, false, "Nokia", 64, 128, {100, 200}, OS::Symbian, true, 12);
    string data = original.toString();
    
    ButtonPhone parsed;
    parsed.fromString(data);
    
    EXPECT_EQ(parsed.getModel(), "Nokia");
    EXPECT_TRUE(parsed.isWaterproof());
    EXPECT_TRUE(parsed.isBabushkaPhone());
    EXPECT_EQ(parsed.getButtonCount(), 12);
}

/**
 * @brief Тест функціональності файлового збереження (writeToFile) та відновлення (readFromFile) списку.
 */
TEST(ListTest, FileIO) {
    PhoneList list;
    list.addPhone(new MobilePhone(true, true, "Test Phone", 1024, 2048, {1,1}, OS::Android));
    string filename = "dist/test_io.txt";
    
    list.writeToFile(filename);
    
    PhoneList loadedList;
    loadedList.readFromFile(filename);
    
    EXPECT_EQ(loadedList.getCount(), 1);
    EXPECT_EQ(loadedList.calculateTotalRAM(), 1024);
}

/**
 * @brief Точка входу для запускника модульних тестів Google Test.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}