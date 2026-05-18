/**
 * @file list.cpp
 * @brief Реалізація методів класу колекції PhoneList, включаючи файлові потоки введення/виведення.
 */

#include "list.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;

PhoneList::PhoneList() : count(0), capacity(2) {
    phones = new MobilePhone*[capacity];
}

PhoneList::~PhoneList() {
    clear();
    delete[] phones;
}

void PhoneList::clear() {
    for (size_t i = 0; i < count; ++i) {
        delete phones[i]; 
    }
    count = 0;
}

void PhoneList::resize() {
    capacity *= 2;
    MobilePhone** newPhones = new MobilePhone*[capacity];
    for (size_t i = 0; i < count; ++i) {
        newPhones[i] = phones[i];
    }
    delete[] phones;
    phones = newPhones;
}

void PhoneList::addPhone(MobilePhone* phone, size_t pos) {
    if (count == capacity) resize();
    if (pos > count) pos = count;
    for (size_t i = count; i > pos; --i) {
        phones[i] = phones[i - 1];
    }
    phones[pos] = phone;
    count++;
}

void PhoneList::removePhone(size_t index) {
    if (index >= count) throw std::out_of_range("Index out of bounds");
    delete phones[index];
    for (size_t i = index; i < count - 1; ++i) {
        phones[i] = phones[i + 1];
    }
    count--;
}

void PhoneList::printAll() const {
    cout << "\n--- Всі телефони у колекції ---\n";
    for (size_t i = 0; i < count; ++i) {
        cout << "[" << i << "] " << phones[i]->toString() << "\n";
    }
}

int PhoneList::calculateTotalRAM() const {
    int totalRAM = 0;
    for (size_t i = 0; i < count; ++i) {
        totalRAM += phones[i]->getRamMB();
    }
    return totalRAM;
}

void PhoneList::printNonBabushkaButtonPhones() const {
    cout << "\n--- Кнопкові (НЕ бабусяфони) ---\n";
    for (size_t i = 0; i < count; ++i) {
        ButtonPhone* bp = dynamic_cast<ButtonPhone*>(phones[i]);
        if (bp != nullptr && !bp->isBabushkaPhone()) {
            cout << bp->toString() << "\n";
        }
    }
}

void PhoneList::printFoldablePhones() const {
    cout << "\n--- Складані телефони ---\n";
    for (size_t i = 0; i < count; ++i) {
        FoldablePhone* fp = dynamic_cast<FoldablePhone*>(phones[i]);
        if (fp != nullptr) {
            cout << fp->toString() << "\n";
        }
    }
}

void PhoneList::writeToFile(string& fileName) {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) throw std::runtime_error("Cannot open file for writing");
    
    for (size_t i = 0; i < count; ++i) {
        outFile << phones[i]->toString() << "\n";
    }
    outFile.close();
}

void PhoneList::readFromFile(string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) throw std::runtime_error("Cannot open file for reading");
    
    clear(); // Попереднє очищення пам'яті за умовою
    
    string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        string type;
        std::getline(ss, type, '|');
        
        MobilePhone* phone = nullptr;
        if (type == "MobilePhone") phone = new MobilePhone();
        else if (type == "ButtonPhone") phone = new ButtonPhone();
        else if (type == "FoldablePhone") phone = new FoldablePhone();
        
        if (phone) {
            phone->fromString(line);
            addPhone(phone, count); // Додаємо в кінець списку
        }
    }
    inFile.close();
}