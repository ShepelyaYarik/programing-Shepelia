/**
 * @file main.cpp
 * @brief Демонстрація поліморфної роботи з ієрархією класів Phone та колекцією List.
 */

#include "list.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {
    cout << "=== Лабораторна робота №20: ООП. Спадкування. Поліморфізм ===" << endl;

    List container;

    // Створюємо та додаємо об'єкти ієрархії через динамічну пам'ять
    container.addPhone(new SmartPhone(true, false, "Google Pixel 8", 8192, 131072, {1080, 2400}, OperatingSystem::Android));
    container.addPhone(new ButtonPhone(true, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian, false, 16));
    container.addPhone(new ButtonPhone(false, false, "Grandma Phone Easy", 16, 32, {240, 320}, OperatingSystem::Android, true, 12));
    container.addPhone(new FoldingPhone(true, false, "Samsung Galaxy Z Flip 5", 8192, 262144, {1080, 2640}, OperatingSystem::Android, true, {720, 748}));
    container.addPhone(new FoldingPhone(false, false, "Motorola Razr 40", 8192, 256000, {1080, 2640}, OperatingSystem::Android, true, {1056, 1066}));
    container.addPhone(new ButtonPhone(false, true, "CAT B26", 64, 128, {240, 320}, OperatingSystem::Symbian, false, 18));

    cout << "\n--- Повний початковий список колекції : ---" << endl;
    container.print();
	
    cout << "\n[Перевірка роботи суто з базовими методами (індекс 0)]:" << endl;
    cout << "Модель першого пристрою: " << container[0].getModel() << endl;
    cout << "Операційна система: " << container[0].getOsString() << endl;

    // 1. Тест першого індивідуального методу: RAM
    cout << "\n[Завдання 1]: Загальний об'єм RAM колекції: " << container.getTotalRam() << " МБ" << endl;
	int totalStorage = container.getTotalStorage() ;
	cout <<  " Загальнна ємність :  " << totalStorage;
    // 2. Тест другого індивідуального методу: Кнопкові, які НЕ є бабусяфонами
    cout << "\n[Завдання 2]: Пошук кнопкових телефонів (НЕ бабусяфонів):" << endl;
    List nonGrandpaButtons = container.getNonGrandpaButtonPhones();
    nonGrandpaButtons.print();

    // 3. Тест третього індивідуального методу: Складані телефони
    cout << "\n[Завдання 3]: Пошук усіх складаних телефонів:" << endl;
    List foldingPhones = container.getFoldingPhones();
    foldingPhones.print();

    // 4. Тестування файлового введення/виведення
    string filepath = "dist/phones_database.txt";
    cout << "\n--- Запис поточної ієрархії у файл " << filepath << " ---" << endl;
    container.writeToFile(filepath);

    cout << "\n--- Зчитування та відновлення об'єктів з файлу в новий список ---" << endl;
    List restoredContainer;
    restoredContainer.readFromFile(filepath);
    restoredContainer.print();

    cout << "\nПрограма завершила роботу. Пам'ять буде очищено деструкторами автоматично." << endl;
    return 0;
}