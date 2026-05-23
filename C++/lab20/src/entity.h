/**
 * @file entity.h
 * @brief Оголошення ієрархії класів телефонів (Phone, ButtonPhone, FoldingPhone) та допоміжних структур.
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
    bool isWaterproof;       /**< Прапорець водостійкості телефона */
    bool isShockproof;       /**< Прапорець ударостійкості телефона */
    std::string model;       /**< Назва моделі або повна назва телефона */
    int ramMb;               /**< Кількість оперативної пам'яті в Мегабайтах */
    int storageMb;           /**< Розмір вбудованого сховища в Мегабайтах */
    ScreenSize screenSize;   /**< Структура розміру екрану */
    OperatingSystem os;      /**< Тип операційної системи */

public:
    /**
     * @brief Конструктор за замовчуванням.
     */
    Phone();

    /**
     * @brief Параметризований конструктор.
     */
    Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType);

    /**
     * @brief Конструктор копіювання.
     */
    Phone(const Phone& other);

    /**
     * @brief Віртуальний деструктор для забезпечення коректного очищення пам'яті спадкоємців.
     */
    virtual ~Phone();

    /**
     * @brief Чисто віртуальний метод для отримання типу телефону (робить клас абстрактним).
     * @return Рядок з типом телефону.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Віртуальний метод для створення глибокої копії об'єкта (Патерн Прототип).
     * @return Вказівник на новий скопійований об'єкт у купі.
     */
    virtual Phone* clone() const = 0;

    /**
     * @brief Віртуальний метод серіалізації об'єкта в рядок.
     */
    virtual std::string toString() const;

    /**
     * @brief Віртуальний метод десеріалізації об'єкта з рядка.
     */
    virtual void fromString(const std::string& data);

    /** @name Перевантажені оператори */
    ///@{
    Phone& operator=(const Phone& other);
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

    /** @name Дружні оператори потоків */
    ///@{
    friend std::ostream& operator<<(std::ostream& os, const Phone& phone);
    friend std::istream& operator>>(std::istream& is, Phone& phone);
    ///@}
};

/**
 * @class ButtonPhone
 * @brief Клас-спадкоємець, що представляє "Кнопковий телефон".
 */
class ButtonPhone final : public Phone {
private:
    bool isGrandpaPhone;  /**< Чи є телефон бабусяфоном */
    int buttonCount;      /**< Кількість кнопок */

public:
    ButtonPhone();
    ButtonPhone(bool water, bool shock, const std::string& mod, int ram, int storage, 
                ScreenSize screen, OperatingSystem osType, bool grandpa, int buttons);
    ButtonPhone(const ButtonPhone& other);
    virtual ~ButtonPhone() override;

    // Поліморфні методи
    virtual std::string getType() const override final;
    virtual Phone* clone() const override final;
    virtual std::string toString() const override final;
    virtual void fromString(const std::string& data) override final;

    // Гетери та сетери
    bool getIsGrandpaPhone() const;
    int getButtonCount() const;
    void setIsGrandpaPhone(bool grandpa);
    void setButtonCount(int buttons);
};

/**
 * @class FoldingPhone
 * @brief Клас-спадкоємець, що представляє "Складаний телефон".
 */
class FoldingPhone final : public Phone {
private:
    bool isFoldInHalf;              /**< Чи складається телефон навпіл */
    ScreenSize foldedScreenSize;    /**< Розмір екрану у складеному стані */

public:
    FoldingPhone();
    FoldingPhone(bool water, bool shock, const std::string& mod, int ram, int storage, 
                 ScreenSize screen, OperatingSystem osType, bool foldHalf, ScreenSize foldedScreen);
    FoldingPhone(const FoldingPhone& other);
    virtual ~FoldingPhone() override;

    // Поліморфні методи (використовуємо final, оскільки клас далі не наслідується)
    virtual std::string getType() const override final;
    virtual Phone* clone() const override final;
    virtual std::string toString() const override final;
    virtual void fromString(const std::string& data) override final;

    // Гетери та сетери
    bool getIsFoldInHalf() const;
    ScreenSize getFoldedScreenSize() const;
    void setIsFoldInHalf(bool foldHalf);
    void setFoldedScreenSize(ScreenSize foldedScreen);
};

/**
 * @class SmartPhone
 * @brief Конкретний клас, що представляє стандартний базовий телефон/смартфон.
 */
class SmartPhone final : public Phone {
public:
    SmartPhone();
    SmartPhone(bool water, bool shock, const std::string& mod, int ram, int storage, 
               ScreenSize screen, OperatingSystem osType);
    SmartPhone(const SmartPhone& other);
    virtual ~SmartPhone() override;

    virtual std::string getType() const override final;
    virtual Phone* clone() const override final;
    virtual std::string toString() const override final;
    virtual void fromString(const std::string& data) override final;
};

#endif // ENTITY_H