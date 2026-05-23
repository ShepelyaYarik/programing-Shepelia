/**
 * @file entity.cpp
 * @brief Реалізація методів класу Phone (конструктори, гетери, сетери, серіалізація).
 */

#include "entity.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

/**
 * @brief Конструктор за замовчуванням.
 * Заповнює поля початковими значеннями та виводить лог-повідомлення.
 */
Phone::Phone()
    : isWaterproof(false), isShockproof(false), model("Unknown"), ramMb(0), storageMb(0), screenSize{0, 0}, os(OperatingSystem::Android) {
    cout << "[Лог]: Викликано конструктор за замовчуванням для Phone: " << model << endl;
}

/**
 * @brief Параметризований конструктор.
 * Створює об'єкт Phone із заданими технічними характеристиками.
 */
Phone::Phone(bool water, bool shock, const string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType)
    : isWaterproof(water), isShockproof(shock), model(mod), ramMb(ram), storageMb(storage), screenSize(screen), os(osType) {
    cout << "[Лог]: Викликано параметризований конструктор для Phone: " << model << endl;
}

/**
 * @brief Конструктор копіювання.
 * Створює точну копію іншого об'єкта Phone в пам'яті.
 */
Phone::Phone(const Phone& other)
    : isWaterproof(other.isWaterproof), isShockproof(other.isShockproof), model(other.model), 
      ramMb(other.ramMb), storageMb(other.storageMb), screenSize(other.screenSize), os(other.os) {
    cout << "[Лог]: Викликано конструктор копіювання для Phone: " << model << endl;
}

/**
 * @brief Деструктор класу. Логує процес видалення об'єкта з пам'яті.
 */
Phone::~Phone() {
    cout << "[Лог]: Викликано деструктор для Phone: " << model << endl;
}

// --- ГЕТЕРИ / СЕТЕРИ ---

bool Phone::getIsWaterproof() const { return isWaterproof; }
bool Phone::getIsShockproof() const { return isShockproof; }
string Phone::getModel() const { return model; }
int Phone::getRamMb() const { return ramMb; }
int Phone::getStorageMb() const { return storageMb; }
ScreenSize Phone::getScreenSize() const { return screenSize; }
OperatingSystem Phone::getOs() const { return os; }

/**
 * @brief Повертає текстову назву ОС на основі значення enum.
 */
string Phone::getOsString() const {
    switch (os) {
        case OperatingSystem::Android: return "Android";
        case OperatingSystem::iOS: return "iOS";
        case OperatingSystem::Symbian: return "Symbian";
        case OperatingSystem::WindowsPhone: return "Windows Phone";
        default: return "Невідома ОС";
    }
}

void Phone::setIsWaterproof(bool water) { isWaterproof = water; }
void Phone::setIsShockproof(bool shock) { isShockproof = shock; }
void Phone::setModel(const string& mod) { model = mod; }
void Phone::setRamMb(int ram) { ramMb = ram; }
void Phone::setStorageMb(int storage) { storageMb = storage; }
void Phone::setScreenSize(ScreenSize screen) { screenSize = screen; }
void Phone::setOs(OperatingSystem osType) { os = osType; }

// --- МЕТОДИ ПОТОКІВ ---

/**
 * @brief Збирає дані всіх полів об'єкта Phone у форматний рядок за допомогою stringstream.
 * Розділювач — символ '|'.
 */
string Phone::toString() const {
    stringstream ss;
    ss << model << "|"
       << isWaterproof << "|"
       << isShockproof << "|"
       << ramMb << "|"
       << storageMb << "|"
       << screenSize.width << "|"
       << screenSize.height << "|"
       << static_cast<int>(os);
    return ss.str();
}

/**
 * @brief Зчитує рядок та розбирає його на окремі змінні за допомогою stringstream і getline з розділювачем '|'.
 */
void Phone::fromString(const string& data) {
    if (data.empty()) return;
    
    stringstream ss(data);
    string tempStr;
    
    std::getline(ss, model, '|');
    
    std::getline(ss, tempStr, '|');
    isWaterproof = (tempStr == "1");
    
    std::getline(ss, tempStr, '|');
    isShockproof = (tempStr == "1");
    
    std::getline(ss, tempStr, '|');
    ramMb = std::stoi(tempStr);
    
    std::getline(ss, tempStr, '|');
    storageMb = std::stoi(tempStr);
    
    std::getline(ss, tempStr, '|');
    screenSize.width = std::stoi(tempStr);
    
    std::getline(ss, tempStr, '|');
    screenSize.height = std::stoi(tempStr);
    
    std::getline(ss, tempStr, '|');
    os = static_cast<OperatingSystem>(std::stoi(tempStr));
}