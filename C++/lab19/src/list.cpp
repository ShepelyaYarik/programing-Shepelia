/**
 * @file list.cpp
 * @brief Реалізація методів класу-списку List та його операторів.
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
using std::ostream;
using std::istream;

List::List() : data(nullptr), size(0) {}

List::~List() {
    clear();
}

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

size_t List::getSize() const {
    return size;
}

// --- ОПЕРАТОРИ ІНДЕКСУВАННЯ ---

Phone& List::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Індекс виходить за межі масиву");
    }
    return *data[index];
}

const Phone& List::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Індекс виходить за межі масиву");
    }
    return *data[index];
}

void List::print() const {
    if (size == 0) {
        cout << "Список порожній." << endl;
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        cout << "[" << i << "] " << *data[i] << endl;
    }
}

int List::getTotalRam() const {
    int totalRam = 0;
    for (size_t i = 0; i < size; ++i) {
        totalRam += data[i]->getRamMb();
    }
    return totalRam;
}

// --- ОПЕРАТОРИ ПОТОКІВ ДЛЯ КЛАСУ LIST ---

ostream& operator<<(ostream& os, const List& list) {
    for (size_t i = 0; i < list.size; ++i) {
        os << *(list.data[i]) << "\n";
    }
    return os;
}

istream& operator>>(istream& is, List& list) {
    list.clear();
    string line;
    while (std::getline(is, line)) {
        if (line.empty()) continue;
        Phone tempPhone;
        tempPhone.fromString(line);
        list.addPhone(tempPhone, list.size); // Додаємо в кінець
    }
    return is;
}

// --- ФАЙЛОВІ ПОТОКИ (через перевикористання операторів) ---

void List::readFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Не вдалося відкрити файл для читання: " + fileName);
    }
    file >> *this;
    file.close();
}

void List::writeToFile(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Не вдалося відкрити файл для запису: " + fileName);
    }
    file << *this;
    file.close();
}