/**
 * @file entity.hpp
 * @brief Оголошення та реалізація ієрархії класів телефонів (Phone, ButtonPhone, FoldingPhone, SmartPhone).
 * @author Ярослав Шепеля
 * @date 2026
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <iostream>
#include <sstream>

/**
 * @struct ScreenSize
 * @brief Структура, що описує фізичні розміри екрану в пікселях.
 */
struct ScreenSize {
    int width;  /**< Ширина екрану у пікселях */
    int height; /**< Висота екрану у пікселях */
};

/**
 * @enum OperatingSystem
 * @brief Перелік доступних операційних систем мобільних телефонів.
 */
enum class OperatingSystem {
    Android,      /**< Операційна система Android від Google */
    iOS,          /**< Операційна система iOS від Apple */
    Symbian,      /**< Операційна система Symbian (Nokia) */
    WindowsPhone  /**< Операційна система Windows Phone від Microsoft */
};

/**
 * @class Phone
 * @brief Абстрактний базовий клас, що представляє сутність "Мобільний телефон".
 */
class Phone {
private:
    bool isWaterproof;       
    bool isShockproof;       
    std::string model;       
    int ramMb;               
    int storageMb;           
    ScreenSize screenSize;   
    OperatingSystem os;      

public:
    Phone() : isWaterproof(false), isShockproof(false), model("Unknown"), ramMb(0), storageMb(0), screenSize{0, 0}, os(OperatingSystem::Android) {}
    
    Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType)
        : isWaterproof(water), isShockproof(shock), model(mod), ramMb(ram), storageMb(storage), screenSize(screen), os(osType) {}

    Phone(const Phone& other)
        : isWaterproof(other.isWaterproof), isShockproof(other.isShockproof), model(other.model), 
          ramMb(other.ramMb), storageMb(other.storageMb), screenSize(other.screenSize), os(other.os) {}

    virtual ~Phone() {}

    virtual std::string getType() const = 0;
    virtual Phone* clone() const = 0;

    virtual std::string toString() const {
        std::stringstream ss;
        ss << model << "|" << isWaterproof << "|" << isShockproof << "|"
           << ramMb << "|" << storageMb << "|" << screenSize.width << "|"
           << screenSize.height << "|" << static_cast<int>(os);
        return ss.str();
    }

    virtual void fromString(const std::string& data) {
        if (data.empty()) return;
        std::stringstream ss(data);
        std::string tempStr;

        std::getline(ss, model, '|');
        std::getline(ss, tempStr, '|'); isWaterproof = (tempStr == "1");
        std::getline(ss, tempStr, '|'); isShockproof = (tempStr == "1");
        std::getline(ss, tempStr, '|'); ramMb = std::stoi(tempStr);
        std::getline(ss, tempStr, '|'); storageMb = std::stoi(tempStr);
        std::getline(ss, tempStr, '|'); screenSize.width = std::stoi(tempStr);
        std::getline(ss, tempStr, '|'); screenSize.height = std::stoi(tempStr);
        std::getline(ss, tempStr, '|'); os = static_cast<OperatingSystem>(std::stoi(tempStr));
    }

    Phone& operator=(const Phone& other) {
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

    bool operator==(const Phone& other) const {
        return (model == other.model && ramMb == other.ramMb && storageMb == other.storageMb);
    }

    bool operator!=(const Phone& other) const { return !(*this == other); }

    bool getIsWaterproof() const { return isWaterproof; }
    bool getIsShockproof() const { return isShockproof; }
    std::string getModel() const { return model; }
    int getRamMb() const { return ramMb; }
    int getStorageMb() const { return storageMb; }
    ScreenSize getScreenSize() const { return screenSize; }
    OperatingSystem getOs() const { return os; }

    std::string getOsString() const {
        switch (os) {
            case OperatingSystem::Android: return "Android";
            case OperatingSystem::iOS: return "iOS";
            case OperatingSystem::Symbian: return "Symbian";
            case OperatingSystem::WindowsPhone: return "Windows Phone";
            default: return "Unknown";
        }
    }

    void setIsWaterproof(bool water) { isWaterproof = water; }
    void setIsShockproof(bool shock) { isShockproof = shock; }
    void setModel(const std::string& mod) { model = mod; }
    void setRamMb(int ram) { ramMb = ram; }
    void setStorageMb(int storage) { storageMb = storage; }
    void setScreenSize(ScreenSize screen) { screenSize = screen; }
    void setOs(OperatingSystem osType) { os = osType; }

    friend std::ostream& operator<<(std::ostream& out, const Phone& phone) {
        out << "Тип: " << phone.getType() << " | Модель: " << phone.model 
            << " | RAM: " << phone.ramMb << " MB | Сховище: " << phone.storageMb 
            << " MB | Екран: " << phone.screenSize.width << "x" << phone.screenSize.height
            << " | OS: " << phone.getOsString()
            << " | Водостійкість: " << (phone.isWaterproof ? "Так" : "Ні")
            << " | Ударостійкість: " << (phone.isShockproof ? "Так" : "Ні");
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Phone& phone) {
        std::string line;
        if (std::getline(in, line)) { phone.fromString(line); }
        return in;
    }
}; 

/**
 * @class ButtonPhone
 * @brief Клас-спадкоємець, що представляє "Кнопковий телефон".
 */
class ButtonPhone final : public Phone {
private:
    bool isGrandpaPhone;  
    int buttonCount;      

public:
    ButtonPhone() : Phone(), isGrandpaPhone(false), buttonCount(0) {}
    ButtonPhone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType, bool grandpa, int buttons)
        : Phone(water, shock, mod, ram, storage, screen, osType), isGrandpaPhone(grandpa), buttonCount(buttons) {}
    ButtonPhone(const ButtonPhone& other) : Phone(other), isGrandpaPhone(other.isGrandpaPhone), buttonCount(other.buttonCount) {}
    virtual ~ButtonPhone() override {}

    std::string getType() const override { return "Кнопковий телефон"; }
    Phone* clone() const override { return new ButtonPhone(*this); }

    std::string toString() const override {
        std::stringstream ss;
        ss << "BUTTON|" << Phone::toString() << "|" << isGrandpaPhone << "|" << buttonCount;
        return ss.str();
    }

    void fromString(const std::string& data) override {
        std::stringstream ss(data);
        std::string marker, baseData, tempStr;
        std::getline(ss, marker, '|'); 
        
        std::string part;
        for (int i = 0; i < 8; ++i) {
            std::getline(ss, part, '|');
            baseData += part + (i < 7 ? "|" : "");
        }
        Phone::fromString(baseData);

        std::getline(ss, tempStr, '|'); isGrandpaPhone = (tempStr == "1");
        std::getline(ss, tempStr, '|'); buttonCount = std::stoi(tempStr);
    }

    bool getIsGrandpaPhone() const { return isGrandpaPhone; }
    int getButtonCount() const { return buttonCount; }
    void setIsGrandpaPhone(bool grandpa) { isGrandpaPhone = grandpa; }
    void setButtonCount(int buttons) { buttonCount = buttons; }
};

/**
 * @class FoldingPhone
 * @brief Клас-спадкоємець, що представляє "Складаний телефон".
 */
class FoldingPhone final : public Phone {
private:
    bool isFoldInHalf;              
    ScreenSize foldedScreenSize;    

public:
    FoldingPhone() : Phone(), isFoldInHalf(false), foldedScreenSize{0, 0} {}
    FoldingPhone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType, bool foldHalf, ScreenSize foldedScreen)
        : Phone(water, shock, mod, ram, storage, screen, osType), isFoldInHalf(foldHalf), foldedScreenSize(foldedScreen) {}
    FoldingPhone(const FoldingPhone& other) : Phone(other), isFoldInHalf(other.isFoldInHalf), foldedScreenSize(other.foldedScreenSize) {}
    virtual ~FoldingPhone() override {}

    std::string getType() const override { return "Складаний телефон"; }
    Phone* clone() const override { return new FoldingPhone(*this); }

    std::string toString() const override {
        std::stringstream ss;
        ss << "FOLDING|" << Phone::toString() << "|" << isFoldInHalf << "|" << foldedScreenSize.width << "|" << foldedScreenSize.height;
        return ss.str();
    }

    void fromString(const std::string& data) override {
        std::stringstream ss(data);
        std::string marker, baseData, tempStr;
        std::getline(ss, marker, '|'); 
        
        std::string part;
        for (int i = 0; i < 8; ++i) {
            std::getline(ss, part, '|');
            baseData += part + (i < 7 ? "|" : "");
        }
        Phone::fromString(baseData);

        std::getline(ss, tempStr, '|'); isFoldInHalf = (tempStr == "1");
        std::getline(ss, tempStr, '|'); foldedScreenSize.width = std::stoi(tempStr);
        std::getline(ss, tempStr, '|'); foldedScreenSize.height = std::stoi(tempStr);
    }

    bool getIsFoldInHalf() const { return isFoldInHalf; }
    ScreenSize getFoldedScreenSize() const { return foldedScreenSize; }
    void setIsFoldInHalf(bool foldHalf) { isFoldInHalf = foldHalf; }
    void setFoldedScreenSize(ScreenSize foldedScreen) { foldedScreenSize = foldedScreen; }
};

/**
 * @class SmartPhone
 * @brief Конкретний клас, що представляє стандартний базовий телефон/смартфон.
 */
class SmartPhone final : public Phone {
public:
    SmartPhone() : Phone() {}
    SmartPhone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType)
        : Phone(water, shock, mod, ram, storage, screen, osType) {}
    SmartPhone(const SmartPhone& other) : Phone(other) {}
    virtual ~SmartPhone() override {}

    std::string getType() const override { return "Стандартний смартфон"; }
    Phone* clone() const override { return new SmartPhone(*this); }

    std::string toString() const override {
        std::stringstream ss;
        ss << "SMART|" << Phone::toString();
        return ss.str();
    }

    void fromString(const std::string& data) override {
        std::stringstream ss(data);
        std::string marker, baseData;
        std::getline(ss, marker, '|'); 
        std::getline(ss, baseData);    
        Phone::fromString(baseData);
    }
};

#endif // ENTITY_HPP