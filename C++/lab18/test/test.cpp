#include <gtest/gtest.h>
#include "../src/list.h"
#include <fstream>

// 1. Тест конструкторів та гетерів класу Phone
TEST(PhoneTest, GettersAndConstructors) {
    ScreenSize screen = {1080, 1920};
    Phone phone(true, false, "Test Model", 4096, 65536, screen, OperatingSystem::Android);

    EXPECT_TRUE(phone.getIsWaterproof());
    EXPECT_FALSE(phone.getIsShockproof());
    EXPECT_EQ(phone.getModel(), "Test Model");
    EXPECT_EQ(phone.getRamMb(), 4096);
    EXPECT_EQ(phone.getStorageMb(), 65536);
    EXPECT_EQ(phone.getScreenSize().width, 1080);
    EXPECT_EQ(phone.getScreenSize().height, 1920);
    EXPECT_EQ(phone.getOs(), OperatingSystem::Android);
    EXPECT_EQ(phone.getOsString(), "Android");
}

// 2. Тест сетерів класу Phone
TEST(PhoneTest, Setters) {
    Phone phone;
    phone.setIsWaterproof(true);
    phone.setIsShockproof(true);
    phone.setModel("New Model");
    phone.setRamMb(2048);
    phone.setStorageMb(16384);
    phone.setScreenSize({720, 1280});
    phone.setOs(OperatingSystem::iOS);

    EXPECT_TRUE(phone.getIsWaterproof());
    EXPECT_TRUE(phone.getIsShockproof());
    EXPECT_EQ(phone.getModel(), "New Model");
    EXPECT_EQ(phone.getRamMb(), 2048);
    EXPECT_EQ(phone.getStorageMb(), 16384);
    EXPECT_EQ(phone.getScreenSize().width, 720);
    EXPECT_EQ(phone.getScreenSize().height, 1280);
    EXPECT_EQ(phone.getOsString(), "iOS");
}

// 3. Тест toString та fromString з новим делімітером '|'
TEST(PhoneStreamTest, SerializationWithVerticalBar) {
    ScreenSize screen = {1080, 2400};
    Phone original(true, false, "Pixel 8 Test", 8192, 128000, screen, OperatingSystem::Android);

    std::string dataStr = original.toString();
    
    // Перевіряємо, що в рядку дійсно з'явилися риски замість крапки з комою
    EXPECT_NE(dataStr.find('|'), std::string::npos);
    EXPECT_EQ(dataStr.find(';'), std::string::npos);
    
    Phone restored;
    restored.fromString(dataStr);

    EXPECT_EQ(restored.getModel(), "Pixel 8 Test");
    EXPECT_TRUE(restored.getIsWaterproof());
    EXPECT_EQ(restored.getRamMb(), 8192);
    EXPECT_EQ(restored.getOs(), OperatingSystem::Android);
}

// 4. Тест файлових операцій List та очищення пам'яті
TEST(ListStreamTest, FileReadWriteAndClear) {
    List writeList;
    Phone p1(false, true, "File Phone 1", 1024, 2048, {480, 800}, OperatingSystem::Symbian);
    Phone p2(true, false, "File Phone 2", 4096, 65536, {1440, 3200}, OperatingSystem::iOS);
    
    writeList.addPhone(p1);
    writeList.addPhone(p2);

    std::string testFile = "dist/test_phones.txt";
    EXPECT_NO_THROW(writeList.writeToFile(testFile));

    List readList;
    EXPECT_NO_THROW(readList.readFromFile(testFile));
    
    ASSERT_EQ(readList.getSize(), 2);
    
    // Враховуємо порядок завантаження елементів твоїм контейнером
    EXPECT_EQ(readList.getPhone(0).getModel(), "File Phone 2");
    EXPECT_EQ(readList.getPhone(1).getModel(), "File Phone 1");

    // Перевірка, що пам'ять очищується і розмір не подвоюється
    EXPECT_NO_THROW(readList.readFromFile(testFile)); 
    EXPECT_EQ(readList.getSize(), 2); 
}

// 5. Тест обробки помилок при відсутності файлу
TEST(ListStreamTest, MissingFileThrowsException) {
    List list;
    EXPECT_THROW(list.readFromFile("non_existent_directory/file.txt"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}