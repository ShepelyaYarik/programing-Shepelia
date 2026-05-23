#include <gtest/gtest.h>
#include "../src/list.h"
#include <sstream>

// 1. Тест розрахунку сумарної RAM
TEST(PhoneHierarchyTest, TotalRamCalculation) {
    List list;
    list.addPhone(new ButtonPhone(true, false, "B1", 1024, 2048, {100, 100}, OperatingSystem::Symbian, false, 12));
    list.addPhone(new FoldingPhone(false, false, "F1", 4096, 8192, {200, 200}, OperatingSystem::Android, true, {50, 50}));
    
    EXPECT_EQ(list.getTotalRam(), 5120); // 1024 + 4096 = 5120
}

// 2. Тест фільтрації кнопкових телефонів (не бабусяфонів)
TEST(PhoneHierarchyTest, FilterNonGrandpaButtonPhones) {
    List list;
    // Кнопковий, не бабусяфон (має підійти)
    list.addPhone(new ButtonPhone(true, false, "Nokia Active", 64, 128, {128, 128}, OperatingSystem::Symbian, false, 15));
    // Кнопковий, бабусяфон (має відсіятися)
    list.addPhone(new ButtonPhone(false, false, "Fly Easy", 32, 64, {240, 320}, OperatingSystem::Symbian, true, 12));
    // Складаний (має відсіятися)
    list.addPhone(new FoldingPhone(false, false, "Z Flip", 8192, 128000, {1080, 1920}, OperatingSystem::Android, true, {200, 200}));

    List result = list.getNonGrandpaButtonPhones();
    
    ASSERT_EQ(result.getSize(), 1);
    EXPECT_EQ(result[0].getModel(), "Nokia Active");
}

// 3. Тест фільтрації складаних телефонів
TEST(PhoneHierarchyTest, FilterFoldingPhones) {
    List list;
    list.addPhone(new ButtonPhone(true, false, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian, false, 16));
    list.addPhone(new FoldingPhone(false, false, "Moto Razr", 4096, 64000, {1080, 2000}, OperatingSystem::Android, true, {300, 300}));

    List result = list.getFoldingPhones();
    
    ASSERT_EQ(result.getSize(), 1);
    EXPECT_EQ(result[0].getModel(), "Moto Razr");
}

// 4. Тест глибокого поліморфного копіювання списку (Правило трьох)
TEST(PhoneHierarchyTest, ListDeepCopyAndRuleOfThree) {
    List original;
    original.addPhone(new ButtonPhone(true, false, "Button", 128, 256, {128, 128}, OperatingSystem::Symbian, false, 16));
    
    // Перевірка конструктора копіювання
    List copy(original);
    ASSERT_EQ(copy.getSize(), 1);
    EXPECT_EQ(copy[0].getModel(), "Button");
    
    // Модифікація копії не повинна впливати на оригінал
    copy[0].setModel("Changed Button");
    EXPECT_EQ(original[0].getModel(), "Button");
    EXPECT_EQ(copy[0].getModel(), "Changed Button");
}

// 5. Тест поліморфної серіалізації/десеріалізації через потоки
TEST(PhoneHierarchyTest, StreamSerialization) {
    List writeList;
    writeList.addPhone(new FoldingPhone(true, true, "Galaxy Fold", 12288, 512000, {1812, 2176}, OperatingSystem::Android, true, {904, 2316}));
    
    std::stringstream ss;
    ss << writeList; // Запис маркованого рядка
    
    List readList;
    ss >> readList;  // Поліморфне читання
    
    ASSERT_EQ(readList.getSize(), 1);
    EXPECT_EQ(readList[0].getModel(), "Galaxy Fold");
    EXPECT_EQ(readList[0].getRamMb(), 12288);
    EXPECT_EQ(readList[0].getType(), "Складаний телефон");
}