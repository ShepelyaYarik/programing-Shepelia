/**
 * @file entity.cpp
 * @brief Реалізація методів для сутностей предметної галузі "Мобільний телефон".
 */

#include "entity.h"

std::string osToString(OS os) {
    switch (os) {
        case OS::Android: return "Android";
        case OS::IOS: return "IOS";
        case OS::Symbian: return "Symbian";
        case OS::WindowsPhone: return "Windows Phone";
        case OS::None: return "None";
        default: return "Unknown";
    }
}

MobilePhone::MobilePhone() 
    : waterproof(false), shockproof(false), model("Unknown"), ramMB(0), storageMB(0), screenSize{0, 0}, os(OS::None) {
    std::cout << "[LOG] MobilePhone: Конструктор за замовчуванням\n";
}

MobilePhone::MobilePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, ScreenSize ss, OS os_val)
    : waterproof(wp), shockproof(sp), model(mod), ramMB(ram), storageMB(storage), screenSize(ss), os(os_val) {
    std::cout << "[LOG] MobilePhone: Конструктор з аргументами (" << model << ")\n";
}

MobilePhone::~MobilePhone() {
    std::cout << "[LOG] MobilePhone: Деструктор (" << model << ")\n";
}

bool MobilePhone::isWaterproof() const { return waterproof; }
bool MobilePhone::isShockproof() const { return shockproof; }
std::string MobilePhone::getModel() const { return model; }
int MobilePhone::getRamMB() const { return ramMB; }
int MobilePhone::getStorageMB() const { return storageMB; }
ScreenSize MobilePhone::getScreenSize() const { return screenSize; }
OS MobilePhone::getOS() const { return os; }

void MobilePhone::print() const {
    std::cout << "Model: " << model 
              << " | RAM: " << ramMB << "MB | Storage: " << storageMB << "MB"
              << " | OS: " << osToString(os) 
              << " | Screen: " << screenSize.width << "x" << screenSize.height 
              << " | WP: " << (waterproof ? "Yes" : "No")
              << " | SP: " << (shockproof ? "Yes" : "No") << "\n";
}


ButtonPhone::ButtonPhone() : MobilePhone(), babushkaPhone(false), buttonCount(0) {
    std::cout << "[LOG] ButtonPhone: Конструктор за замовчуванням\n";
}

ButtonPhone::ButtonPhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                         ScreenSize ss, OS os_val, bool isBabushka, int btnCount)
    : MobilePhone(wp, sp, mod, ram, storage, ss, os_val), babushkaPhone(isBabushka), buttonCount(btnCount) {
    std::cout << "[LOG] ButtonPhone: Конструктор з аргументами\n";
}

ButtonPhone::~ButtonPhone() {
    std::cout << "[LOG] ButtonPhone: Деструктор\n";
}

bool ButtonPhone::isBabushkaPhone() const { return babushkaPhone; }
int ButtonPhone::getButtonCount() const { return buttonCount; }

void ButtonPhone::print() const {
    std::cout << "[Кнопковий] ";
    MobilePhone::print(); 
    std::cout << "    -> Buttons: " << buttonCount 
              << " | Babushka-phone: " << (babushkaPhone ? "Yes" : "No") << "\n";
}


FoldablePhone::FoldablePhone() : MobilePhone(), foldsInHalf(false), foldedScreenSize{0,0} {
    std::cout << "[LOG] FoldablePhone: Конструктор за замовчуванням\n";
}

FoldablePhone::FoldablePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                             ScreenSize ss, OS os_val, bool folds, ScreenSize fss)
    : MobilePhone(wp, sp, mod, ram, storage, ss, os_val), foldsInHalf(folds), foldedScreenSize(fss) {
    std::cout << "[LOG] FoldablePhone: Конструктор з аргументами\n";
}

FoldablePhone::~FoldablePhone() {
    std::cout << "[LOG] FoldablePhone: Деструктор\n";
}

bool FoldablePhone::getFoldsInHalf() const { return foldsInHalf; }
ScreenSize FoldablePhone::getFoldedScreenSize() const { return foldedScreenSize; }

void FoldablePhone::print() const {
    std::cout << "[Складаний] ";
    MobilePhone::print();
    std::cout << "    -> Folds: " << (foldsInHalf ? "Yes" : "No") 
              << " | Folded Screen: " << foldedScreenSize.width << "x" << foldedScreenSize.height << "\n";
}