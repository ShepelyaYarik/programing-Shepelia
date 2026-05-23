/**
 * @file entity.cpp
 * @brief Реалізація методів ієрархії класів Phone, ButtonPhone, SmartPhone, FoldingPhone.
 */

#include "entity.h"
#include <sstream>

using std::string;                
using std::stringstream;
using std::ostream;
using std::istream;
using std::endl;

// РЕАЛІЗАЦІЯ АБСТРАКТНОГО БАЗОВОГО КЛАСУ PHONE


Phone::Phone()
    : isWaterproof(false), isShockproof(false), model("Unknown"), ramMb(0), storageMb(0), screenSize{0, 0}, os(OperatingSystem::Android) {}

Phone::Phone(bool water, bool shock, const string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType)
    : isWaterproof(water), isShockproof(shock), model(mod), ramMb(ram), storageMb(storage), screenSize(screen), os(osType) {}

Phone::Phone(const Phone& other)
    : isWaterproof(other.isWaterproof), isShockproof(other.isShockproof), model(other.model), 
      ramMb(other.ramMb), storageMb(other.storageMb), screenSize(other.screenSize), os(other.os) {}

Phone::~Phone() {}

string Phone::toString() const {
    stringstream ss;
    ss << model << "|" << isWaterproof << "|" << isShockproof << "|"
       << ramMb << "|" << storageMb << "|" << screenSize.width << "|"
       << screenSize.height << "|" << static_cast<int>(os);
    return ss.str();
}

void Phone::fromString(const string& data) {
    if (data.empty()) return;
    stringstream ss(data);
    string tempStr;

    std::getline(ss, model, '|');
    std::getline(ss, tempStr, '|'); isWaterproof = (tempStr == "1");
    std::getline(ss, tempStr, '|'); isShockproof = (tempStr == "1");
    std::getline(ss, tempStr, '|'); ramMb = std::stoi(tempStr);
    std::getline(ss, tempStr, '|'); storageMb = std::stoi(tempStr);
    std::getline(ss, tempStr, '|'); screenSize.width = std::stoi(tempStr);
    std::getline(ss, tempStr, '|'); screenSize.height = std::stoi(tempStr);
    std::getline(ss, tempStr, '|'); os = static_cast<OperatingSystem>(std::stoi(tempStr));
}

Phone& Phone::operator=(const Phone& other) {
    if (this != &other) {
        isWaterproof = other.isWaterproof;
        isShockproof = other.isShockproof;
        model = other.model;
        ramMb = other.ramMb;
        storageMb = other.storageMb;
        screenSize = other.screenSize;
        os = other.os;
    }
    return *this;
}

bool Phone::operator==(const Phone& other) const {
    return (model == other.model && ramMb == other.ramMb && storageMb == other.storageMb);
}

bool Phone::operator!=(const Phone& other) const {
    return !(*this == other);
}

bool Phone::getIsWaterproof() const { return isWaterproof; }
bool Phone::getIsShockproof() const { return isShockproof; }
string Phone::getModel() const { return model; }
int Phone::getRamMb() const { return ramMb; }
int Phone::getStorageMb() const { return storageMb; }
ScreenSize Phone::getScreenSize() const { return screenSize; }
OperatingSystem Phone::getOs() const { return os; }

string Phone::getOsString() const {
    switch (os) {
        case OperatingSystem::Android: return "Android";
        case OperatingSystem::iOS: return "iOS";
        case OperatingSystem::Symbian: return "Symbian";
        case OperatingSystem::WindowsPhone: return "Windows Phone";
        default: return "Unknown";
    }
}

void Phone::setIsWaterproof(bool water) { isWaterproof = water; }
void Phone::setIsShockproof(bool shock) { isShockproof = shock; }
void Phone::setModel(const string& mod) { model = mod; }
void Phone::setRamMb(int ram) { ramMb = ram; }
void Phone::setStorageMb(int storage) { storageMb = storage; }
void Phone::setScreenSize(ScreenSize screen) { screenSize = screen; }
void Phone::setOs(OperatingSystem osType) { os = osType; }

ostream& operator<<(ostream& os, const Phone& phone) {
    os << "Тип: " << phone.getType() << " | Модель: " << phone.model 
       << " | RAM: " << phone.ramMb << " MB | Сховище: " << phone.storageMb 
       << " MB | Екран: " << phone.screenSize.width << "x" << phone.screenSize.height
       << " | OS: " << phone.getOsString()
       << " | Водостійкість: " << (phone.isWaterproof ? "Так" : "Ні")
       << " | Ударостійкість: " << (phone.isShockproof ? "Так" : "Ні");
    return os;
}

istream& operator>>(istream& is, Phone& phone) {
    string line;
    if (std::getline(is, line)) {
        phone.fromString(line);
    }
    return is;
}

// РЕАЛІЗАЦІЯ КЛАСУ BUTTONPHONE (КНОПКОВИЙ)

ButtonPhone::ButtonPhone() : Phone(), isGrandpaPhone(false), buttonCount(0) {}

ButtonPhone::ButtonPhone(bool water, bool shock, const string& mod, int ram, int storage, 
                         ScreenSize screen, OperatingSystem osType, bool grandpa, int buttons)
    : Phone(water, shock, mod, ram, storage, screen, osType), isGrandpaPhone(grandpa), buttonCount(buttons) {}

ButtonPhone::ButtonPhone(const ButtonPhone& other) 
    : Phone(other), isGrandpaPhone(other.isGrandpaPhone), buttonCount(other.buttonCount) {}

ButtonPhone::~ButtonPhone() {}

string ButtonPhone::getType() const { return "Кнопковий телефон"; }

Phone* ButtonPhone::clone() const { return new ButtonPhone(*this); }

string ButtonPhone::toString() const {
    stringstream ss;
    ss << "BUTTON|" << Phone::toString() << "|" << isGrandpaPhone << "|" << buttonCount;
    return ss.str();
}

void ButtonPhone::fromString(const string& data) {
    stringstream ss(data);
    string marker, baseData, tempStr;

    std::getline(ss, marker, '|'); // Очікуємо "BUTTON"
    
    // Витягуємо базову частину (8 полів базового класу)
    string part;
    for (int i = 0; i < 8; ++i) {
        std::getline(ss, part, '|');
        baseData += part + (i < 7 ? "|" : "");
    }
    Phone::fromString(baseData);

    std::getline(ss, tempStr, '|'); isGrandpaPhone = (tempStr == "1");
    std::getline(ss, tempStr, '|'); buttonCount = std::stoi(tempStr);
}

bool ButtonPhone::getIsGrandpaPhone() const { return isGrandpaPhone; }
int ButtonPhone::getButtonCount() const { return buttonCount; }
void ButtonPhone::setIsGrandpaPhone(bool grandpa) { isGrandpaPhone = grandpa; }
void ButtonPhone::setButtonCount(int buttons) { buttonCount = buttons; }

// РЕАЛІЗАЦІЯ КЛАСУ FOLDINGPHONE (СКЛАДАНИЙ)


FoldingPhone::FoldingPhone() : Phone(), isFoldInHalf(false), foldedScreenSize{0, 0} {}

/**
 * @brief Параметризований конструктор для Складаного телефона.
 */
FoldingPhone::FoldingPhone(bool water, bool shock, const string& mod, int ram, int storage, 
                           ScreenSize screen, OperatingSystem osType, bool foldHalf, ScreenSize foldedScreen)
    : Phone(water, shock, mod, ram, storage, screen, osType), isFoldInHalf(foldHalf), foldedScreenSize(foldedScreen) {}

FoldingPhone::FoldingPhone(const FoldingPhone& other) 
    : Phone(other), isFoldInHalf(other.isFoldInHalf), foldedScreenSize(other.foldedScreenSize) {}

FoldingPhone::~FoldingPhone() {}

string FoldingPhone::getType() const { return "Складаний телефон"; }

Phone* FoldingPhone::clone() const { return new FoldingPhone(*this); }

string FoldingPhone::toString() const {
    stringstream ss;
    ss << "FOLDING|" << Phone::toString() << "|" << isFoldInHalf << "|" 
       << foldedScreenSize.width << "|" << foldedScreenSize.height;
    return ss.str();
}

void FoldingPhone::fromString(const string& data) {
    stringstream ss(data);
    string marker, baseData, tempStr;

    std::getline(ss, marker, '|'); // Очікуємо "FOLDING"
    
    string part;
    for (int i = 0; i < 8; ++i) {
        std::getline(ss, part, '|');
        baseData += part + (i < 7 ? "|" : "");
    }
    Phone::fromString(baseData);

    std::getline(ss, tempStr, '|'); isFoldInHalf = (tempStr == "1");
    std::getline(ss, tempStr, '|'); foldedScreenSize.width = std::stoi(tempStr);
    std::getline(ss, tempStr, '|'); foldedScreenSize.height = std::stoi(tempStr);
}

bool FoldingPhone::getIsFoldInHalf() const { return isFoldInHalf; }
ScreenSize FoldingPhone::getFoldedScreenSize() const { return foldedScreenSize; }
void FoldingPhone::setIsFoldInHalf(bool foldHalf) { isFoldInHalf = foldHalf; }
void FoldingPhone::setFoldedScreenSize(ScreenSize foldedScreen) { foldedScreenSize = foldedScreen; }



// РЕАЛІЗАЦІЯ КЛАСУ SMARTPHONE (БАЗОВИЙ ТЕЛЕФОН / СМАРТФОН)


SmartPhone::SmartPhone() : Phone() {}

SmartPhone::SmartPhone(bool water, bool shock, const string& mod, int ram, int storage, 
                       ScreenSize screen, OperatingSystem osType)
    : Phone(water, shock, mod, ram, storage, screen, osType) {}

SmartPhone::SmartPhone(const SmartPhone& other) : Phone(other) {}

SmartPhone::~SmartPhone() {}

string SmartPhone::getType() const { return "Стандартний смартфон"; }

Phone* SmartPhone::clone() const { return new SmartPhone(*this); }

string SmartPhone::toString() const {
    stringstream ss;
    ss << "SMART|" << Phone::toString(); // Маркер типу для файлу
    return ss.str();
}

void SmartPhone::fromString(const string& data) {
    stringstream ss(data);
    string marker, baseData;
    
    std::getline(ss, marker, '|'); // Зчитуємо "SMART"
    std::getline(ss, baseData);    // Усе інше віддаємо базовому класу
    Phone::fromString(baseData);
}