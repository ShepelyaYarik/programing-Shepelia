/**
 * @file entity.h
 * @brief Оголошення класу Phone та допоміжних структур для сутності мобільного телефона.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

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
 * @brief Перелік (Enum class) доступних операційних систем мобільних телефонів.
 */
enum class OperatingSystem {
    Android,      /**< Операційна система Android від Google */
    iOS,          /**< Операційна система iOS від Apple */
    Symbian,      /**< Операційна система Symbian (Nokia) */
    WindowsPhone  /**< Операційна система Windows Phone від Microsoft */
};

/**
 * @class Phone
 * @brief Клас, що представляє сутність "Мобільний телефон".
 */
class Phone {
private:
    bool isWaterproof;       /**< Прапорець водостійкості телефона */
    bool isShockproof;       /**< Прапорець ударостійкості телефона */
    std::string model;       /**< Назва моделі або повна назва телефона */
    int ramMb;               /**< Кількість оперативної пам'яті у Мегабайтах */
    int storageMb;           /**< Розмір вбудованого сховища у Мегабайтах */
    ScreenSize screenSize;   /**< Структура з розмірами екрану */
    OperatingSystem os;      /**< Тип операційної системи */

public:
    Phone();
    Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType);
    Phone(const Phone& other);
    ~Phone();

    /** @name Перевантажені оператори */
    ///@{
    /**
     * @brief Оператор присвоювання.
     */
    Phone& operator=(const Phone& other);

    /**
     * @brief Оператори порівняння (за моделлю та об'ємом RAM).
     */
    bool operator==(const Phone& other) const;
    bool operator!=(const Phone& other) const;
    ///@}

    /** @name Гетери та Сетери */
    ///@{
    bool getIsWaterproof() const;
    bool getIsShockproof() const;
    std::string getModel() const;
    int getRamMb() const;
    int getStorageMb() const;
    ScreenSize getScreenSize() const;
    OperatingSystem getOs() const;
    std::string getOsString() const;

    void setIsWaterproof(bool water);
    void setIsShockproof(bool shock);
    void setModel(const std::string& mod);
    void setRamMb(int ram);
    void setStorageMb(int storage);
    void setScreenSize(ScreenSize screen);
    void setOs(OperatingSystem osType);
    ///@}

    std::string toString() const;
    void fromString(const std::string& data);

    /** @name Дружні оператори введення / виведення */
    ///@{
    friend std::ostream& operator<<(std::ostream& os, const Phone& phone);
    friend std::istream& operator>>(std::istream& is, Phone& phone);
    ///@}
};

#endif // ENTITY_H