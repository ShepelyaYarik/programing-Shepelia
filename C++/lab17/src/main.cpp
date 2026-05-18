/**
 * @file main.cpp
 * @brief Головний файл програми.
 * * Демонструє створення об'єктів, наповнення колекції та виклик методів згідно
 * з індивідуальним завданням №18 (Мобільний телефон).
 */

#include "list.h"
#include <iostream>

int main() {
    std::cout << "=== Демонстрація Лабораторної (Завдання 18) ===\n\n";

    {
        PhoneList myList;

        // Створюємо об'єкти динамічно через new і передаємо вказівники у колекцію
        
        // 1. Звичайний кнопковий (не бабусяфон)
        myList.addPhone(new ButtonPhone(false, true, "Nokia 3310", 16, 32, {84, 48}, OS::Symbian, false, 15));
        
        // 2. Бабусяфон
        myList.addPhone(new ButtonPhone(false, false, "Sigma Comfort 50", 8, 16, {128, 160}, OS::None, true, 12));
        
        // 3. Складаний смартфон
        myList.addPhone(new FoldablePhone(true, false, "Samsung Galaxy Z Flip 5", 8192, 256000, {1080, 2640}, OS::Android, true, {720, 748}));
        
        // 4. Звичайний смартфон (базовий клас)
        myList.addPhone(new MobilePhone(true, true, "Google Pixel 8", 8192, 128000, {1080, 2400}, OS::Android));
		std::cout << "\n=== Видаляємо телефон під індексом 1 (Samsung Z Flip) ===\n";
		myList.removePhone(3);
        // Демонстрація вмісту
        myList.printAll();

        // Тестування специфічних методів завдання
        std::cout << "\n1. Загальний об'єм RAM усіх пристроїв: " << myList.calculateTotalRAM() << " MB\n";
        
        myList.printNonBabushkaButtonPhones(); // Очікується вивід Nokia 3310
        myList.printFoldablePhones();          // Очікується вивід Z Flip 5

        std::cout << "\n--- Очищення пам'яті (вихід з області видимості) ---\n";
    } // Деструктор PhoneList автоматично звільнить пам'ять

    return 0;
}