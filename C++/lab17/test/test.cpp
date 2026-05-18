#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/list.h"

// =================================================================
// 1. БАЗОВІ ТЕСТИ ДЛЯ СУТНОСТЕЙ
// =================================================================

TEST(EntityTest, MobilePhoneInitialization) {
    MobilePhone phone(true, false, "Pixel 8", 8192, 128000, {1080, 2400}, OS::Android);
    EXPECT_TRUE(phone.isWaterproof());
    EXPECT_FALSE(phone.isShockproof());
    EXPECT_EQ(phone.getModel(), "Pixel 8");
    EXPECT_EQ(phone.getRamMB(), 8192);
    EXPECT_EQ(phone.getStorageMB(), 128000);
    EXPECT_EQ(phone.getOS(), OS::Android);
}

TEST(EntityTest, ButtonPhoneInitialization) {
    ButtonPhone bp(false, true, "Nokia 3310", 16, 32, {84, 48}, OS::Symbian, false, 15);
    EXPECT_EQ(bp.getModel(), "Nokia 3310");
    EXPECT_FALSE(bp.isBabushkaPhone());
    EXPECT_EQ(bp.getButtonCount(), 15);
    EXPECT_EQ(bp.getRamMB(), 16); 
}

TEST(EntityTest, FoldablePhoneInitialization) {
    FoldablePhone fp(true, false, "Galaxy Z Flip", 8192, 256000, {1080, 2640}, OS::Android, true, {720, 748});
    EXPECT_TRUE(fp.getFoldsInHalf());
    EXPECT_EQ(fp.getFoldedScreenSize().width, 720);
    EXPECT_EQ(fp.getFoldedScreenSize().height, 748);
}

// =================================================================
// 2. БАЗОВІ ТЕСТИ ДЛЯ КОЛЕКЦІЇ
// =================================================================

TEST(PhoneListTest, AddPhoneAndCalculateTotalRAM) {
    PhoneList list;
    list.addPhone(new MobilePhone(true, true, "Phone 1", 1000, 0, {0,0}, OS::Android));
    list.addPhone(new ButtonPhone(false, false, "Phone 2", 500, 0, {0,0}, OS::None, false, 10));
    list.addPhone(new FoldablePhone(true, false, "Phone 3", 2000, 0, {0,0}, OS::Android, true, {0,0}));
    EXPECT_EQ(list.calculateTotalRAM(), 3500);
}

TEST(PhoneListTest, RemovePhoneUpdatesRAM) {
    PhoneList list;
    list.addPhone(new MobilePhone(false, false, "Test1", 1000, 0, {0,0}, OS::Android));
    list.addPhone(new MobilePhone(false, false, "Test2", 2000, 0, {0,0}, OS::Android));
    list.addPhone(new MobilePhone(false, false, "Test3", 3000, 0, {0,0}, OS::Android));
    EXPECT_EQ(list.calculateTotalRAM(), 6000);
    list.removePhone(1);
    EXPECT_EQ(list.calculateTotalRAM(), 4000);
}

TEST(PhoneListTest, RemoveFromEmptyListThrows) {
    PhoneList list;
    EXPECT_THROW(list.removePhone(0), std::out_of_range);
}

TEST(PhoneListTest, RemoveOutOfBoundsThrows) {
    PhoneList list;
    list.addPhone(new MobilePhone(true, true, "Phone", 1024, 0, {0,0}, OS::Android));
    EXPECT_THROW(list.removePhone(1), std::out_of_range);
}

// =================================================================
// 3. ДОДАТКОВІ ТЕСТИ ДЛЯ ПІДНЯТТЯ ПОКРИТТЯ (COVERAGE)
// =================================================================

TEST(EntityTest, DefaultConstructorsCoverage) {
    MobilePhone mp;
    EXPECT_EQ(mp.getRamMB(), 0);
    EXPECT_EQ(mp.getStorageMB(), 0);
    
    ButtonPhone bp;
    EXPECT_EQ(bp.getButtonCount(), 0);
    
    FoldablePhone fp;
    EXPECT_FALSE(fp.getFoldsInHalf());
}

TEST(EntityTest, ExtraGettersAndEnumsCoverage) {
    MobilePhone mp(false, true, "Test", 10, 20, {100, 200}, OS::IOS);
    EXPECT_EQ(mp.getStorageMB(), 20);
    EXPECT_EQ(mp.getScreenSize().width, 100);
    EXPECT_EQ(mp.getScreenSize().height, 200);
    EXPECT_TRUE(mp.isShockproof());
    
    EXPECT_EQ(osToString(OS::Android), "Android");
    EXPECT_EQ(osToString(OS::Symbian), "Symbian");
    EXPECT_EQ(osToString(OS::WindowsPhone), "Windows Phone");
    EXPECT_EQ(osToString(OS::None), "None");
}

TEST(PrintMethodsTest, ExecuteAllPrints) {
    MobilePhone mp(true, true, "Test", 1, 1, {1,1}, OS::Android);
    mp.print();
    
    ButtonPhone bp(true, true, "Test", 1, 1, {1,1}, OS::Android, true, 9);
    bp.print();
    
    FoldablePhone fp(true, true, "Test", 1, 1, {1,1}, OS::Android, true, {1,1});
    fp.print();
}

TEST(PhoneListTest, ExecuteListPrints) {
    PhoneList list;
    list.addPhone(new MobilePhone(true, true, "Test1", 1, 1, {1,1}, OS::Android));
    list.addPhone(new ButtonPhone(true, true, "Test2", 1, 1, {1,1}, OS::Android, false, 9));
    list.addPhone(new FoldablePhone(true, true, "Test3", 1, 1, {1,1}, OS::Android, true, {1,1}));
    
    list.printAll();
    list.printNonBabushkaButtonPhones();
    list.printFoldablePhones();
}

// =================================================================
// ГОЛОВНА ФУНКЦІЯ
// =================================================================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}