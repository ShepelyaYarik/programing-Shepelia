/**
 * @file test.cpp
 * @brief Модульні тести для верифікації контейнера List на базі std::vector.
 * @author Ярослав Шепеля
 * @date 2026
 */

#include <gtest/gtest.h>
#include "../src/list.hpp"
#include <sstream>
#include <fstream>

TEST(PhoneStlVectorTest, TotalMemoryAndGetters) {
    List list;
    ScreenSize scr = {1080, 2400};
    SmartPhone* smart = new SmartPhone(true, false, "Pixel 8", 8192, 131072, scr, OperatingSystem::Android);
    
    EXPECT_TRUE(smart->getIsWaterproof());
    EXPECT_FALSE(smart->getIsShockproof());
    EXPECT_EQ(smart->getScreenSize().width, 1080);
    EXPECT_EQ(smart->getOsString(), "Android");

    list.addPhone(smart);
    list.addPhone(new ButtonPhone(false, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian, false, 16));
    
    EXPECT_EQ(list.getTotalRam(), 8224);
    EXPECT_EQ(list.getTotalStorage(), 131136);
}

TEST(PhoneStlVectorTest, EntitySettersAndOperators) {
    SmartPhone p1(false, false, "Test", 100, 200, {0,0}, OperatingSystem::iOS);
    SmartPhone p2(false, false, "Test", 100, 200, {0,0}, OperatingSystem::iOS);
    EXPECT_TRUE(p1 == p2);
    p1.setModel("New Test");
    EXPECT_FALSE(p1 == p2);
    p2 = p1;
    EXPECT_TRUE(p1 == p2);
}

TEST(PhoneStlVectorTest, DerivedClassesGettersSetters) {
    ButtonPhone btn;
    btn.setIsGrandpaPhone(true);
    btn.setButtonCount(12);
    EXPECT_TRUE(btn.getIsGrandpaPhone());
    EXPECT_EQ(btn.getButtonCount(), 12);
    
    FoldingPhone fold;
    fold.setIsFoldInHalf(true);
    EXPECT_TRUE(fold.getIsFoldInHalf());
}

TEST(PhoneStlVectorTest, StlCrudOperationsAndExceptions) {
    List list;
    list.addPhone(new SmartPhone(true, false, "Pixel 7", 8192, 128000, {1080, 2400}, OperatingSystem::Android));
    ASSERT_EQ(list.getSize(), 1);

    list.updateModel(0, "Pixel 7 Pro");
    EXPECT_EQ(list[0].getModel(), "Pixel 7 Pro");

    EXPECT_THROW(list[99].getModel(), std::out_of_range);
    EXPECT_THROW(list.removePhone(99), std::out_of_range);
    EXPECT_THROW(list.updateModel(99, "Error"), std::out_of_range);

    list.removePhone(0);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(PhoneStlVectorTest, SortingAndFiltering) {
    List list;
    list.addPhone(new FoldingPhone(false, false, "Moto Razr", 4096, 64000, {1080, 2000}, OperatingSystem::Android, true, {300, 300}));
    list.addPhone(new ButtonPhone(true, false, "Nokia Active", 64, 128, {128, 128}, OperatingSystem::Symbian, false, 15));
    list.addPhone(new ButtonPhone(false, false, "Grandma Phone", 16, 32, {240, 320}, OperatingSystem::Symbian, true, 12));

    List foldList = list.getFoldingPhones();
    ASSERT_EQ(foldList.getSize(), 1);
    EXPECT_EQ(foldList[0].getModel(), "Moto Razr");

    List btnList = list.getNonGrandpaButtonPhones();
    ASSERT_EQ(btnList.getSize(), 1);
    EXPECT_EQ(btnList[0].getModel(), "Nokia Active");

    list.sortByRam();
    EXPECT_EQ(list[0].getModel(), "Grandma Phone"); 
    EXPECT_EQ(list[1].getModel(), "Nokia Active");   
    EXPECT_EQ(list[2].getModel(), "Moto Razr");     
}

TEST(PhoneStlVectorTest, MergeAndAssignment) {
    List list1;
    list1.addPhone(new SmartPhone(true, false, "Phone 1", 4096, 64000, {1080, 1920}, OperatingSystem::Android));
    List list2;
    list2.addPhone(new SmartPhone(true, false, "Phone 2", 8192, 128000, {1080, 1920}, OperatingSystem::Android));
    
    list1.mergeWith(list2);
    ASSERT_EQ(list1.getSize(), 2);
    
    List list3;
    list3 = list1;
    ASSERT_EQ(list3.getSize(), 2);
    EXPECT_EQ(list3[1].getModel(), "Phone 2");
}

TEST(PhoneStlVectorTest, SerializationAndFileIO) {
    List writeList;
    writeList.addPhone(new SmartPhone(true, false, "SmartS", 1, 2, {3,4}, OperatingSystem::Android));
    
    std::stringstream ss;
    ss << writeList;
    List readList;
    ss >> readList;
    ASSERT_EQ(readList.getSize(), 1);
    
    std::string filename = "test_vector_db.txt";
    writeList.writeToFile(filename);
    List fileList;
    fileList.readFromFile(filename);
    ASSERT_EQ(fileList.getSize(), 1);
    std::remove(filename.c_str());
}