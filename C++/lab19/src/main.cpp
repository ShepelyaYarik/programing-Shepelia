/**
 * @file main.cpp
 * @brief Демонстрація перевантаження операторів для класів Phone та List.
 */

#include "list.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {
    cout << "--- Лабораторна робота №19: Перевантаження операторів ---" << endl;
  
    Phone p1(true, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian);
    Phone p2;
    
    // 1. Демонстрація оператора присвоювання
    p2 = p1; 
    
    // 2. Демонстрація операторів порівняння та виведення об'єкта
    cout << "\np1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    
    if (p1 == p2) {
        cout << "[Результат]: Об'єкти p1 та p2 рівні!" << endl;
    }

    p2.setModel("Nokia 3310 Updated");
    if (p1 != p2) {
        cout << "[Результат]: Після модифікації p1 та p2 не рівні." << endl;
    }

    cout << "\n--- Робота з Класом-Списком та оператором [] ---" << endl;
    List initialList;
    initialList.addPhone(p1);
    initialList.addPhone(Phone(false, false, "iPhone 15 Pro", 6144, 262144, {1179, 2556}, OperatingSystem::iOS), 1);
    
    // Використання оператора [] для читання даних
    cout << "Елемент за індексом 1 через operator[]: " << initialList[1] << endl;

    // Використання оператора [] для модифікації об'єкта всередині списку
    initialList[0].setRamMb(128); 
    cout << "Оновлена RAM для елемента 0: " << initialList[0].getRamMb() << " МБ" << endl;

    // 3. Тестування файлових операцій через потоки списку
    string filename = "dist/phones_data.txt";
    cout << "\nЗапис списку у файл за допомогою operator<< ..." << endl;
    initialList.writeToFile(filename);

    List loadedList;
    cout << "Читання списку з файлу за допомогою operator>> ..." << endl;
    loadedList.readFromFile(filename);

    cout << "\nВміст завантаженого списку (через operator<< для List):" << endl;
    cout << loadedList;
    
    cout << "\n--- Кінець роботи програми (Виклик деструкторів) ---" << endl;
    return 0;
}