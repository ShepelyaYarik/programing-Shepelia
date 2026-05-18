/**
 * @file list.cpp
 * @brief Реалізація логіки керування колекцією телефонів.
 * * Відповідає за виділення/звільнення динамічної пам'яті, додавання/видалення 
 * елементів та виконання завдань з індивідуального варіанту №18.
 */

#include "list.h"
#include <stdexcept>
#include <iostream>

PhoneList::PhoneList() : count(0), capacity(2) {
    phones = new MobilePhone*[capacity]; // Виділяємо пам'ять під масив вказівників
    std::cout << "[LOG] PhoneList: Створено список\n";
}

PhoneList::~PhoneList() {
    // Важливо: спочатку видаляємо самі об'єкти, на які вказують елементи масиву
    for (size_t i = 0; i < count; ++i) {
        delete phones[i]; 
    }
    // Потім видаляємо сам масив вказівників
    delete[] phones;
    std::cout << "[LOG] PhoneList: Знищено список та звільнено пам'ять об'єктів\n";
}

void PhoneList::resize() {
    capacity *= 2; // Збільшуємо місткість удвічі
    MobilePhone** newPhones = new MobilePhone*[capacity];
    
    // Копіюємо існуючі вказівники у новий масив
    for (size_t i = 0; i < count; ++i) {
        newPhones[i] = phones[i];
    }
    
    delete[] phones; // Звільняємо стару ділянку пам'яті масиву
    phones = newPhones; // Перенаправляємо вказівник на новий масив
}

void PhoneList::addPhone(MobilePhone* phone, size_t pos) {
    if (count == capacity) {
        resize();
    }
    if (pos > count) {
        pos = count; // Запобігаємо виходу за межі (додаємо в кінець)
    }
    
    // Зсуваємо елементи вправо, щоб звільнити місце на позиції pos
    for (size_t i = count; i > pos; --i) {
        phones[i] = phones[i - 1];
    }
    
    phones[pos] = phone;
    count++;
}

void PhoneList::removePhone(size_t index) {
    if (index >= count) throw std::out_of_range("Index out of bounds");
    
    delete phones[index]; // Звільняємо пам'ять самого об'єкта телефону
    
    // Зсуваємо елементи вліво, затираючи "дірку" від видаленого вказівника
    for (size_t i = index; i < count - 1; ++i) {
        phones[i] = phones[i + 1];
    }
    count--;
}

void PhoneList::printAll() const {
    std::cout << "\n--- Усі телефони в колекції ---\n";
    for (size_t i = 0; i < count; ++i) {
        std::cout << "[" << i << "] ";
        // Завдяки поліморфізму (virtual) викличеться print() відповідного спадкоємця
        phones[i]->print(); 
    }
    std::cout << "-------------------------------\n";
}

int PhoneList::calculateTotalRAM() const {
    int totalRAM = 0;
    for (size_t i = 0; i < count; ++i) {
        totalRAM += phones[i]->getRamMB();
    }
    return totalRAM;
}

void PhoneList::printNonBabushkaButtonPhones() const {
    std::cout << "\n--- Кнопкові телефони (НЕ бабусяфони) ---\n";
    bool found = false;
    for (size_t i = 0; i < count; ++i) {
        // dynamic_cast поверне nullptr, якщо об'єкт НЕ є ButtonPhone
        ButtonPhone* bp = dynamic_cast<ButtonPhone*>(phones[i]);
        if (bp != nullptr && !bp->isBabushkaPhone()) {
            bp->print();
            found = true;
        }
    }
    if (!found) std::cout << "Таких телефонів не знайдено.\n";
}

void PhoneList::printFoldablePhones() const {
    std::cout << "\n--- Складані телефони ---\n";
    bool found = false;
    for (size_t i = 0; i < count; ++i) {
        // dynamic_cast перевіряє, чи є об'єкт FoldablePhone
        FoldablePhone* fp = dynamic_cast<FoldablePhone*>(phones[i]);
        if (fp != nullptr) {
            fp->print();
            found = true;
        }
    }
    if (!found) std::cout << "Таких телефонів не знайдено.\n";
}