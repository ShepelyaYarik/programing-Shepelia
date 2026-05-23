/**
 * @file main.cpp
 * @brief Головний файл програми для демонстрації роботи з класами Phone та List.
 */

#include "list.h"
#include <iostream>

int main() {
    std::cout << "--- Демонстрація роботи конструкторів ---" << std::endl;
    
    //  Конструктор за замовчуванням
    Phone p1; 
    
    // Конструктор з аргументами
    Phone p2(true, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian);
    
    // Конструктор копіювання
    Phone p3 = p2; 

    std::cout << "\n--- Робота зі списком (List) ---" << std::endl;
    List phoneList;
    
    phoneList.addPhone(p3);

    phoneList.addPhone(Phone(false, false, "iPhone 15", 6144, 131072, {1179, 2556}, OperatingSystem::iOS), 1);

    phoneList.addPhone(Phone(true, false, "Google Pixel 8", 8192, 131072, {1080, 2400}, OperatingSystem::Android), 0);

    std::cout << "\nПоточний вміст списку:" << std::endl;
    phoneList.print();
	phoneList.getPhone(0).setStorageMb(256000); // сеттер
	std::cout << "\nЗбільшили вдвічі розмір сховища за індексом 0 :  " << phoneList.getPhone(0).getModel()  << " "<< phoneList.getPhone(0).getStorageMb() << "Mb" << std::endl; 
    std::cout << "\nЗагальна оперативна пам'ять у колекції: " << phoneList.getTotalRam() << " МБ" << std::endl;

    std::cout << "\nВидалення елемента за індексом 1..." << std::endl;
    phoneList.removePhone(1);
    
    std::cout << "\nВміст списку після видалення:" << std::endl;
    phoneList.print();

    std::cout << "\n--- Завершення програми (тут спрацюють деструктори) ---" << std::endl;
    return 0;
}