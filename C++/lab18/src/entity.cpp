/**
 * @file entity.cpp
 * @brief Реалізація методів класів MobilePhone, ButtonPhone, FoldablePhone та функцій перетворення ОС.
 */

#include "entity.h"
#include <sstream>

using std::string;
using std::stringstream;

string osToString(OS os) {
    switch (os) {
        case OS::Android: return "Android";
        case OS::iOS: return "iOS";
        case OS::Symbian: return "Symbian";
        case OS::WindowsPhone: return "WindowsPhone";
        default: return "None";
    }
}

OS stringToOS(const string& str) {
    if (str == "Android") return OS::Android;
    if (str == "iOS") return OS::iOS;
    if (str == "Symbian") return OS::Symbian;
    if (str == "WindowsPhone") return OS::WindowsPhone;
    return OS::None;
}

// === Реалізація MobilePhone ===

MobilePhone::MobilePhone() 
    : waterproof(false), shockproof(false), model("Unknown"), ramMB(0), storageMB(0), screenSize{0, 0}, os(OS::None) {}

MobilePhone::MobilePhone(bool wp, bool sp, const string& mod, int ram, int storage, ScreenSize ss, OS os_val)
    : waterproof(wp), shockproof(sp), model(mod), ramMB(ram), storageMB(storage), screenSize(ss), os(os_val) {}

MobilePhone::~MobilePhone() {}

bool MobilePhone::isWaterproof() const { return waterproof; }
bool MobilePhone::isShockproof() const { return shockproof; }
string MobilePhone::getModel() const { return model; }
int MobilePhone::getRamMB() const { return ramMB; }
int MobilePhone::getStorageMB() const { return storageMB; }
ScreenSize MobilePhone::getScreenSize() const { return screenSize; }
OS MobilePhone::getOS() const { return os; }

string MobilePhone::toString() const {
    stringstream ss;
    ss << "MobilePhone|" << waterproof << "|" << shockproof << "|" << model << "|" 
       << ramMB << "|" << storageMB << "|" << screenSize.width << "|" << screenSize.height << "|" << osToString(os);
    return ss.str();
}

void MobilePhone::fromString(const string& data) {
    stringstream ss(data);
    string token;
    
    std::getline(ss, token, '|'); // Пропускаємо ідентифікатор типу
    std::getline(ss, token, '|'); waterproof = (token == "1");
    std::getline(ss, token, '|'); shockproof = (token == "1");
    std::getline(ss, model, '|');
    std::getline(ss, token, '|'); ramMB = std::stoi(token);
    std::getline(ss, token, '|'); storageMB = std::stoi(token);
    std::getline(ss, token, '|'); screenSize.width = std::stoi(token);
    std::getline(ss, token, '|'); screenSize.height = std::stoi(token);
    std::getline(ss, token, '|'); os = stringToOS(token);
}

// === Реалізація ButtonPhone ===

ButtonPhone::ButtonPhone() : MobilePhone(), babushkaPhone(false), buttonCount(0) {}

ButtonPhone::ButtonPhone(bool wp, bool sp, const string& mod, int ram, int storage, 
                         ScreenSize ss, OS os_val, bool isBabushka, int btnCount)
    : MobilePhone(wp, sp, mod, ram, storage, ss, os_val), babushkaPhone(isBabushka), buttonCount(btnCount) {}

ButtonPhone::~ButtonPhone() {}

bool ButtonPhone::isBabushkaPhone() const { return babushkaPhone; }
int ButtonPhone::getButtonCount() const { return buttonCount; }

string ButtonPhone::toString() const {
    stringstream ss;
    ss << "ButtonPhone|" << waterproof << "|" << shockproof << "|" << model << "|" 
       << ramMB << "|" << storageMB << "|" << screenSize.width << "|" << screenSize.height << "|" << osToString(os) 
       << "|" << babushkaPhone << "|" << buttonCount;
    return ss.str();
}

void ButtonPhone::fromString(const string& data) {
    MobilePhone::fromString(data); // Заповнюємо базові поля
    stringstream ss(data);
    string token;
    // Пропускаємо перші 9 полей, які вже оброблені базовим класом
    for(int i = 0; i < 9; ++i) {
        std::getline(ss, token, '|');
    }
    std::getline(ss, token, '|'); babushkaPhone = (token == "1");
    std::getline(ss, token, '|'); buttonCount = std::stoi(token);
}

// === Реалізація FoldablePhone ===

FoldablePhone::FoldablePhone() : MobilePhone(), foldsInHalf(false), foldedScreenSize{0,0} {}

FoldablePhone::FoldablePhone(bool wp, bool sp, const string& mod, int ram, int storage, 
                             ScreenSize ss, OS os_val, bool folds, ScreenSize fss)
    : MobilePhone(wp, sp, mod, ram, storage, ss, os_val), foldsInHalf(folds), foldedScreenSize(fss) {}

FoldablePhone::~FoldablePhone() {}

bool FoldablePhone::getFoldsInHalf() const { return foldsInHalf; }
ScreenSize FoldablePhone::getFoldedScreenSize() const { return foldedScreenSize; }

string FoldablePhone::toString() const {
    stringstream ss;
    ss << "FoldablePhone|" << waterproof << "|" << shockproof << "|" << model << "|" 
       << ramMB << "|" << storageMB << "|" << screenSize.width << "|" << screenSize.height << "|" << osToString(os) 
       << "|" << foldsInHalf << "|" << foldedScreenSize.width << "|" << foldedScreenSize.height;
    return ss.str();
}

void FoldablePhone::fromString(const string& data) {
    MobilePhone::fromString(data); // Заповнюємо базові поля
    stringstream ss(data);
    string token;
    // Пропускаємо перші 9 полей
    for(int i = 0; i < 9; ++i) {
        std::getline(ss, token, '|');
    }
    std::getline(ss, token, '|'); foldsInHalf = (token == "1");
    std::getline(ss, token, '|'); foldedScreenSize.width = std::stoi(token);
    std::getline(ss, token, '|'); foldedScreenSize.height = std::stoi(token);
}