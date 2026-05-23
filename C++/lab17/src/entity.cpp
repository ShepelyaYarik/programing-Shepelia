#include "entity.h"
#include <iostream>

/**
 * @brief Конструктор за замовчуванням для класу Phone.
 */
Phone::Phone()
    : isWaterproof(false), isShockproof(false), model("unknown"), ramMb(0), storageMb(0), screenSize{0, 0}, os(OperatingSystem::Android) {
    std::cout << "[Лог]: Викликано конструктор за замовчуванням для Phone: " << model << std::endl;
}

/**
 * @brief Конструктор з аргументами (параметризований).
 */
Phone::Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType)
    : isWaterproof(water), isShockproof(shock), model(mod), ramMb(ram), storageMb(storage), screenSize(screen), os(osType) {
    std::cout << "[Лог]: Викликано конструктор з аргументами для Phone: " << model << std::endl;
}

/**
 * @brief Конструктор копіювання класу Phone.
 */
Phone::Phone(const Phone& other)
    : isWaterproof(other.isWaterproof), isShockproof(other.isShockproof), model(other.model), 
      ramMb(other.ramMb), storageMb(other.storageMb), screenSize(other.screenSize), os(other.os) {
    std::cout << "[Лог]: Викликано конструктор копіювання для Phone: " << model << std::endl;
}

/**
 * @brief Деструктор класу Phone.
 */
Phone::~Phone() {
    std::cout << "[Лог]: Викликано деструктор для Phone: " << model << std::endl;
}

// --- ГЕТЕРИ ---
bool Phone::getIsWaterproof() const { return isWaterproof; }
bool Phone::getIsShockproof() const { return isShockproof; }
std::string Phone::getModel() const { return model; }
int Phone::getRamMb() const { return ramMb; }
int Phone::getStorageMb() const { return storageMb; }
ScreenSize Phone::getScreenSize() const { return screenSize; }
OperatingSystem Phone::getOs() const { return os; }

std::string Phone::getOsString() const {
    switch (os) {
        case OperatingSystem::Android: return "Android";
        case OperatingSystem::iOS: return "iOS";
        case OperatingSystem::Symbian: return "Symbian";
        case OperatingSystem::WindowsPhone: return "Windows Phone";
        default: return "Невідома ОС";
    }
}

// --- СЕТЕРИ ---
void Phone::setIsWaterproof(bool water) { isWaterproof = water; }
void Phone::setIsShockproof(bool shock) { isShockproof = shock; }
void Phone::setModel(const std::string& mod) { model = mod; }
void Phone::setRamMb(int ram) { ramMb = ram; }
void Phone::setStorageMb(int storage) { storageMb = storage; }
void Phone::setScreenSize(ScreenSize screen) { screenSize = screen; }
void Phone::setOs(OperatingSystem osType) { os = osType; }

/**
 * @brief Виводить відформатовані технічні характеристики телефона в консоль.
 */
void Phone::print() const {
    std::cout << "Модель: " << model 
              << " | ОС: " << getOsString()
              << " | ОЗУ: " << ramMb << " МБ"
              << " | Сховище: " << storageMb << " МБ"
              << " | Екран: " << screenSize.width << "x" << screenSize.height
              << " | Водостійкість: " << (isWaterproof ? "Так" : "Ні")
              << " | Ударостійкість: " << (isShockproof ? "Так" : "Ні") << std::endl;
}