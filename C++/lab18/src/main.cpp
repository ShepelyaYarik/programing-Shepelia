/**
 * @file main.cpp
 * @brief Головний файл програми для демонстрації С++ потоків, серіалізації структур та ООП.
 */

#include "list.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Головна функція (точка входу в програму).
 * * Демонструє серіалізацію сутності Phone у текстовий рядок, відновлення об'єкта
 * з рядка, запис списку об'єктів у файл за допомогою файлових потоків та їх читання назад.
 * @return 0 при успішному завершенні програми.
 */
int main() {
    cout << "--- Демонстрація серіалізації та потоків ---" << endl;
  
    Phone p1(true, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian);
    
    // Перевірка toString()
    string serialized = p1.toString();
    cout << "Серіалізована Nokia: " << serialized << endl;

    // Перевірка відтворення об'єкта з рядка
    Phone p2;
    p2.fromString(serialized);
    cout << "Відновлена модель Nokia: " << p2.getModel() << " | RAM: " << p2.getRamMb() << " МБ " << endl;

    cout << "\n--- Робота з файловими потоками (Клас-список) ---" << endl;
    List initialList;
    initialList.addPhone(p1);
    initialList.addPhone(Phone(false, false, "iPhone 15 Pro", 6144, 262144, {1179, 2556}, OperatingSystem::iOS), 1);
    initialList.addPhone(Phone(true, false, "Google Pixel 8", 8192, 131072, {1080, 2400}, OperatingSystem::Android), 0);

    cout << "Початковий список перед збереженням у файл:" << endl;
    initialList.print();

    string filename = "dist/phones_data.txt";
    cout << "\nЗбереження списку у '" << filename << "'..." << endl;
    initialList.writeToFile(filename);

    cout << "Створення другого списку та завантаження даних із файлу..." << endl;
    List loadedList;
    loadedList.readFromFile(filename);

    cout << "Вміст завантаженого списку:" << endl;
    loadedList.print();
    
    cout << "\nЗагальний обсяг RAM у завантаженій колекції: " << loadedList.getTotalRam() << " МБ" << endl;
    cout << "\n--- Кінець роботи програми (Зараз спрацюють деструктори) ---" << endl;
    
    return 0;
}