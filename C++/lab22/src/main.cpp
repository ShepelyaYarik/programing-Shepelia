/**
 * @file main.cpp
 * @brief Демонстрація роботи з STL-колекцією телефонів List на базі вектора.
 * @author Ярослав Шепеля
 * @date 2026
 */

#include "list.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {
    cout << "=== Лабораторна робота №22: ООП. STL ===" << endl;

    List container;
    container.addPhone(new SmartPhone(true, false, "Google Pixel 8", 8192, 131072, {1080, 2400}, OperatingSystem::Android));
    container.addPhone(new ButtonPhone(true, true, "Nokia 3310", 32, 64, {128, 128}, OperatingSystem::Symbian, false, 16));
    container.addPhone(new ButtonPhone(false, false, "Grandma Phone Easy", 16, 32, {240, 320}, OperatingSystem::Android, true, 12));
    container.addPhone(new FoldingPhone(true, false, "Samsung Galaxy Z Flip 5", 12288, 262144, {1080, 2640}, OperatingSystem::Android, true, {720, 748}));



	const Phone* maxRamPhone = container.getMaxRamPhone();
	cout<<"Пристрій з найбільшою RAM: \n" << maxRamPhone->toString() << " Об'єм RAM:  "  << maxRamPhone->getRamMb() << "MB" << endl ;
    cout << "\n--- Початковий список колекції (READ) ---" << endl;
    container.print();

    cout << "\n--- Оновлення моделі телефону за індексом 2 (UPDATE) ---" << endl;
    container.updateModel(2, "Nokia 3310 Reborn");
    container.print();

    cout << "\n--- Видалення телефону за індексом 2 (DELETE) ---" << endl;
    container.removePhone(2); 
    container.print();

    cout << "\n[Завдання 1]: Загальний об'єм RAM колекції: " << container.getTotalRam() << " МБ" << endl;
    cout << "[Додатково]: Загальна ємність сховища: " << container.getTotalStorage() << " МБ" << endl;

    cout << "\n=== Сортування колекції за RAM за допомогою функтора ===" << endl;
    container.sortByRam();
    container.print();

    cout << "\n=== Об'єднання з іншим списком ===" << endl;
    List secondaryContainer;
    secondaryContainer.addPhone(new ButtonPhone(false, true, "CAT B26", 64, 128, {240, 320}, OperatingSystem::Symbian, false, 18));
    container.mergeWith(secondaryContainer);
    container.print();

    string filepath = "dist/phones_database_stl.txt";
    cout << "\n--- Запис у файл " << filepath << " ---" << endl;
    container.writeToFile(filepath);

    cout << "\n--- Відновлення даних з файлу ---" << endl;
    List restoredContainer;
    restoredContainer.readFromFile(filepath);
    restoredContainer.print();

    cout << "\nПрограма завершена успішно." << endl;
    return 0;
}