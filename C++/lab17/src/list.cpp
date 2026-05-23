#include "list.h"
#include <iostream>
#include <stdexcept>

/**
 * @brief Конструктор за замовчуванням класу List.
 */
List::List() : data(nullptr), size(0) {}

/**
 * @brief Деструктор класу List з повним очищенням купи.
 */
List::~List() {
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
}

/**
 * @brief Додає новий телефон у масив на вказану позицію.
 */
void List::addPhone(const Phone& phone, size_t pos) {
    if (pos > size) {
        pos = size;
    }

    Phone** newData = new Phone*[size + 1];

    for (size_t i = 0; i < pos; ++i) {
        newData[i] = data[i];
    }

    newData[pos] = new Phone(phone);

    for (size_t i = pos; i < size; ++i) {
        newData[i + 1] = data[i];
    }

    delete[] data;
    data = newData;
    ++size;
}

/**
 * @brief Видаляє телефон з колекції за його індексом.
 */
void List::removePhone(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Індекс за межами масиву");
    }

    delete data[index];

    if (size == 1) {
        delete[] data;
        data = nullptr;
        size = 0;
        return;
    }

    Phone** newData = new Phone*[size - 1];

    for (size_t i = 0; i < index; ++i) {
        newData[i] = data[i];
    }
    for (size_t i = index + 1; i < size; ++i) {
        newData[i - 1] = data[i];
    }

    delete[] data;
    data = newData;
    --size;
}

Phone& List::getPhone(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Індекс за межами масиву");
    }
    return *data[index];
}

const Phone& List::getPhone(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Індекс за межами масиву");
    }
    return *data[index];
}

size_t List::getSize() const {
    return size;
}

/**
 * @brief Виводить увесь список телефонів у консоль.
 */
void List::print() const {
    if (size == 0) {
        std::cout << "Список порожній." << std::endl;
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        std::cout << "[" << i << "] ";
        data[i]->print();
    }
}

/**
 * @brief Розраховує загальний об'єм ОЗУ.
 */
int List::getTotalRam() const {
    int totalRam = 0;
    for (size_t i = 0; i < size; ++i) {
        totalRam += data[i]->getRamMb();
    }
    return totalRam;
}