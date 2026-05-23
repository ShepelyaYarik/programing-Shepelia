#include <gtest/gtest.h>
#include "../src/list.h"

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
    EXPECT_EQ(phone.getOs(), OperatingSystem::iOS);
    EXPECT_EQ(phone.getOsString(), "iOS");
    
    // Перевіримо інші ОС для покриття switch-case
    phone.setOs(OperatingSystem::Symbian);
    EXPECT_EQ(phone.getOsString(), "Symbian");
    phone.setOs(OperatingSystem::WindowsPhone);
    EXPECT_EQ(phone.getOsString(), "Windows Phone");
}

// 3. Тест підрахунку загальної оперативної пам'яті в List
TEST(PhoneListTest, CalculatesTotalRamCorrectly) {
    List list;
    
    Phone phone1(false, false, "Test Phone 1", 1024, 4096, {720, 1280}, OperatingSystem::Android);
    Phone phone2(false, false, "Test Phone 2", 2048, 8192, {1080, 1920}, OperatingSystem::iOS);
    
    list.addPhone(phone1);
    list.addPhone(phone2);
    
    EXPECT_EQ(list.getTotalRam(), 3072);
}

// 4. Тест додавання, вставки за індексом та видалення в List
TEST(PhoneListTest, HandlesAddAndRemove) {
    List list;
    Phone phone1(true, true, "Phone 1", 4096, 65536, {1080, 2340}, OperatingSystem::Android);
    Phone phone2(false, false, "Phone 2", 2048, 32768, {1080, 2340}, OperatingSystem::Android);
    
    // Додавання в кінець (дефолтна позиція 0 в порожній список)
    list.addPhone(phone1);
    ASSERT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.getPhone(0).getModel(), "Phone 1");
    
    // Вставка на позицію 0 (зсув першого елемента)
    list.addPhone(phone2, 0);
    ASSERT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getPhone(0).getModel(), "Phone 2");
    
    // Перевірка константної версії getPhone
    const List& constList = list;
    EXPECT_EQ(constList.getPhone(1).getModel(), "Phone 1");

    // Видалення
    list.removePhone(0);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.getPhone(0).getModel(), "Phone 1");

    list.removePhone(0);
    EXPECT_EQ(list.getSize(), 0);
}

// 5. Тест обробки помилок (Out of Bounds)
TEST(PhoneListTest, ThrowsOutOfBoundsExceptions) {
    List list;
    Phone phone;
    list.addPhone(phone);

    // Очікуємо, що метод викине std::out_of_range
    EXPECT_THROW(list.getPhone(5), std::out_of_range);
    EXPECT_THROW(list.removePhone(5), std::out_of_range);
    
    const List& constList = list;
    EXPECT_THROW(constList.getPhone(5), std::out_of_range);
}

// 6. Тест виводу порожнього списку та методу print
TEST(PhoneListTest, PrintMethods) {
    List list;
    // Просто викликаємо, щоб перевірити гілку "The list is empty"
    list.print(); 

    Phone phone;
    phone.print(); // Покриваємо метод виводу самого телефону
    
    list.addPhone(phone);
    list.print(); // Покриваємо вивід заповненого списку
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}