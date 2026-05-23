#include <gtest/gtest.h>
#include "../src/list.h"
#include <sstream>
#include <fstream>

// 1. Тест операторів порівняння та присвоювання класу Phone
TEST(PhoneOperatorTest, AssignmentAndComparison) {
    Phone phone1(true, false, "Operator Model", 4096, 65536, {1080, 1920}, OperatingSystem::Android);
    Phone phone2;
    
    phone2 = phone1; // Перевірка оператора присвоювання
    
    EXPECT_EQ(phone1, phone2); // Перевірка operator==
    
    phone2.setModel("Changed Model");
    EXPECT_NE(phone1, phone2); // Перевірка operator!=
}

// 2. Тест операторів введення/виведення класу Phone
TEST(PhoneOperatorTest, StreamOperators) {
    Phone phone(true, true, "Stream Model", 8192, 128000, {1440, 3200}, OperatingSystem::iOS);
    
    std::stringstream ss;
    ss << phone; // Тест виведення
    
    Phone restored;
    ss >> restored; // Тест введення
    
    EXPECT_EQ(phone, restored);
}

// 3. Тест операторів індексування [] у класі List
TEST(ListOperatorTest, IndexingOperator) {
    List list;
    Phone p1(false, false, "Phone 1", 2048, 16384, {720, 1280}, OperatingSystem::Android);
    Phone p2(true, true, "Phone 2", 4096, 32768, {1080, 2400}, OperatingSystem::iOS);
    
    list.addPhone(p1, 0);
    list.addPhone(p2, 1);
    
    // Перевірка константного / неконстантного зчитування
    EXPECT_EQ(list[0].getModel(), "Phone 1");
    EXPECT_EQ(list[1].getModel(), "Phone 2");
    
    // Перевірка зміни через []
    list[0].setModel("Phone 1 Updated");
    EXPECT_EQ(list[0].getModel(), "Phone 1 Updated");
    
    // Перевірка виходу за межі
    EXPECT_THROW(list[5], std::out_of_range);
}

// 4. Тест операторів потоку списку (List Stream Operators)
TEST(ListOperatorTest, ListStreamOperators) {
    List writeList;
    Phone p1(false, true, "List Phone 1", 1024, 2048, {480, 800}, OperatingSystem::Symbian);
    
    writeList.addPhone(p1, 0);
    
    std::stringstream ss;
    ss << writeList;
    
    List readList;
    ss >> readList;
    
    ASSERT_EQ(readList.getSize(), 1);
    EXPECT_EQ(readList[0].getModel(), "List Phone 1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}