/**
 * @file main.cpp
 * @brief Демонстраційний файл програми для демонстрації збереження та відновлення списку об'єктів з файлу.
 */

#include "list.h"
#include <iostream>

using std::cout;
using std::string;

/**
 * @brief Головна функція програми (точка входу).
 * Демонструє створення об'єктів класів-спадкоємців, запис колекції у файл,
 * автоматичне звільнення пам'яті та повторне читання даних.
 * @return Код завершення програми (0 — успішно).
 */
int main() {
    cout << "=== Лабораторна робота 18 (Потоки) ===\n\n";

    string filename = "dist/phones.txt";

    // Створюємо та записуємо список у файл всередині окремої області видимості
    {
        PhoneList myList;
        myList.addPhone(new MobilePhone(true, true, "Google Pixel 8", 8192, 128000, {1080, 2400}, OS::Android));
        myList.addPhone(new FoldablePhone(true, false, "Galaxy Z Flip", 8192, 256000, {1080, 2640}, OS::Android, true, {720, 748}));
        myList.addPhone(new ButtonPhone(false, false, "Sigma Comfort 50", 8, 16, {128, 160}, OS::None, true, 12));
        myList.addPhone(new ButtonPhone(false, true, "Nokia 3310", 16, 32, {84, 48}, OS::Symbian, false, 15));
        
        cout << "--- Запис у файл: " << filename << " ---\n";
        myList.writeToFile(filename);
    } // Тут myList знищується, вся виділена через new пам'ять звільняється автоматично.

    // Читаємо дані з файлу в інший об'єкт-список
    {
        PhoneList loadedList;
        cout << "--- Читання з файлу: " << filename << " ---\n";
        loadedList.readFromFile(filename);
        
        loadedList.printAll();
        
        cout << "\nЗагальна RAM пристроїв: " << loadedList.calculateTotalRAM() << " MB\n";
    }

    return 0;
}