/**
 * @file main.cpp
 * @brief Демонстрація роботи шаблонного класу List з різними типами даних.
 *
 * Цей файл є точкою входу в програму. Він ілюструє концепцію узагальненого
 * програмування, перевіряючи методи контейнера для базового типу (int)
 * та об'єкта стандартної бібліотеки (std::string) без використання char*.
 */

#include "list.hpp"
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Головна функція програми.
 *
 * Виконує послідовну демонстрацію працездатності всіх методів класу List:
 * додавання елементів, виведення на екран, лінійний пошук індексу,
 * знаходження мінімального значення за допомогою оператора менше (<)
 * та сортування бульбашкою за зростанням.
 *
 * @return int Повертає 0 при успішному завершенні програми.
 */
int main() {
    // 1. Демонстрація роботи зі списком цілих чисел (int)
    cout << "=== Перевірка роботи з типом int ===" << endl;
    List<int> intList;
    intList.append(42);
    intList.append(15);
    intList.append(88);
    intList.append(3);
    intList.append(27);

    cout << "Початковий список чисел: ";
    intList.print();

    // Знаходження мінімального елемента у списку чисел
    cout << "Мінімальний елемент: " << intList.min() << endl;

    // Пошук індексу існуючого та неіснуючого елемента
    int searchVal = 88;
    cout << "Індекс елемента " << searchVal << ": " << intList.indexOf(searchVal) << endl;
    cout << "Індекс неіснуючого елемента (999): " << intList.indexOf(999) << endl;

    // Видалення елемента за індексом (видаляємо число 15, яке стоїть під індексом 1)
    cout << "Видаляємо елемент за індексом 1 це " << intList[1] <<endl;
    intList.removeAt(1);
    cout << "Список після видалення: ";
    intList.print();

    // Сортування елементів масиву за зростанням
    cout << "Сортуємо список..." << endl;
    intList.sort();
    cout << "Відсортований список чисел: ";
    intList.print();

    cout << endl;

    // 2. Демонстрація роботи зі списком рядків (std::string)
    
    cout << "=== Перевірка роботи з типом std::string ===" << endl;
    List<string> stringList;

    stringList.append(string("Kharkiv"));
    stringList.append(string("Kyiv"));
    stringList.append(string("Sumy"));
    stringList.append(string("Lviv"));

    cout << "Початковий список рядків: ";
    stringList.print();

    // Пошук мінімального елемента (для рядків це найменший за кодами ASCII символів)
    cout << "Мінімальний елемент (алфавітно): " << stringList.min() << endl;

    // Пошук індексу текстового рядка
    string searchStr = "Sumy";
    cout << "Індекс елемента \"" << searchStr << "\": " << stringList.indexOf(searchStr) << endl;

    // Лексикографічне сортування рядків (за алфавітом ASCII)
    cout << "Сортуємо список рядків..." << endl;
    stringList.sort();
    cout << "Відсортований список рядків: ";
    stringList.print();

    return 0;
}