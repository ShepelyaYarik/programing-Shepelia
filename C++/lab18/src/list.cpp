/**
 * @file list.cpp
 * @brief Реалізація методів класу-списку List для управління масивом телефонів та файлових потоків.
 */

#include "list.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

List::List() : data(nullptr), size(0) {}

List::~List() {
    clear();
}

/**
 * @brief Очищує пам'ять. Послідовно видаляє об'єкти Phone із купи,
 * після чого видаляє сам масив покажчиків. Скидає розмір в 0.
 */
void List::clear() {
    if (data != nullptr) {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        data = nullptr;
    }
    size = 0;
}

/**
 * @brief Збільшує масив на 1 елемент та вставляє копію телефона на обрану позицію.
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
 * @brief Зменшує розмір динамічного масиву та видаляє об'єкт з пам'яті за індексом.
 */
void List::removePhone(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Індекс виходить за межі масиву");
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
        throw std::out_of_range("Індекс виходить за межі масиву");
    }
    return *data[index];
}

const Phone& List::getPhone(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Індекс виходить за межі масиву");
    }
    return *data[index];
}

size_t List::getSize() const {
    return size;
}

void List::print() const {
    if (size == 0) {
        cout << "Список порожній." << endl;
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        cout << "[" << i << "] Рядок серіалізації: " << data[i]->toString() << endl;
    }
}

int List::getTotalRam() const {
    int totalRam = 0;
    for (size_t i = 0; i < size; ++i) {
        totalRam += data[i]->getRamMb();
    }
    return totalRam;
}

// --- ФАЙЛОВІ ПОТОКИ ---

/**
 * @brief Відкриває файл через ifstream, очищує поточну пам'ять списку
 * та створює об'єкти на базі зчитаних рядків (із новим розділювачем '|').
 */
void List::readFromFile(const string& fileName) {
    clear(); 

    ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Не вдалося відкрити файл для читання: " + fileName);
    }

    string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Phone tempPhone;
        tempPhone.fromString(line);
        
        size_t currentSize = this->size; 
        addPhone(tempPhone, currentSize);
    }
    file.close();
}

/**
 * @brief Відкриває файл через ofstream та записує туди результат роботи toString() з рискою '|'.
 */
void List::writeToFile(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Не вдалося відкрити файл для запису: " + fileName);
    }

    for (size_t i = 0; i < size; ++i) {
        file << data[i]->toString() << "\n";
    }
    file.close();
}