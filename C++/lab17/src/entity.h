/**
 * @file entity.h
 * @brief Містить оголошення базового класу MobilePhone та його спадкоємців.
 * * Цей файл реалізує предметну галузь "Мобільний телефон" для індивідуального завдання №18.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

/**
 * @brief Структура для зберігання розміру екрану.
 */
struct ScreenSize {
    int width;  ///< Ширина екрану в пікселях.
    int height; ///< Висота екрану в пікселях.
};

/**
 * @brief Перелік можливих операційних систем мобільного телефону.
 */
enum class OS { Android, IOS, Symbian, WindowsPhone, None };

/**
 * @brief Перетворює значення переліку OS у рядкове представлення.
 * @param os Операційна система (enum OS).
 * @return Рядок з назвою ОС.
 */
std::string osToString(OS os);


/**
 * @class MobilePhone
 * @brief Базовий клас, що представляє загальний мобільний телефон.
 * * Містить основні характеристики будь-якого мобільного телефону (захист, пам'ять, екран, ОС).
 */
class MobilePhone {
private:
    bool waterproof;       ///< Чи є телефон водостійким.
    bool shockproof;       ///< Чи є телефон ударостійким.
    std::string model;     ///< Назва моделі телефону.
    int ramMB;             ///< Об'єм оперативної пам'яті в мегабайтах.
    int storageMB;         ///< Об'єм внутрішнього сховища в мегабайтах.
    ScreenSize screenSize; ///< Роздільна здатність екрану.
    OS os;                 ///< Встановлена операційна система.

public:
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує телефон нульовими/стандартними значеннями.
     */
    MobilePhone();

    /**
     * @brief Конструктор з параметрами.
     * @param wp Водостійкість (true/false).
     * @param sp Ударостійкість (true/false).
     * @param mod Назва моделі.
     * @param ram Об'єм RAM (МБ).
     * @param storage Об'єм сховища (МБ).
     * @param ss Розмір екрану (ScreenSize).
     * @param os_val Операційна система (OS).
     */
    MobilePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, ScreenSize ss, OS os_val);
    
    /**
     * @brief Віртуальний деструктор.
     * Необхідний для коректного видалення об'єктів-спадкоємців через вказівник на базовий клас.
     */
    virtual ~MobilePhone();

    // Гетери
    /** @return true, якщо телефон водостійкий. */
    bool isWaterproof() const;
    /** @return true, якщо телефон ударостійкий. */
    bool isShockproof() const;
    /** @return Назва моделі. */
    std::string getModel() const;
    /** @return Об'єм оперативної пам'яті в МБ. */
    int getRamMB() const;
    /** @return Об'єм внутрішнього сховища в МБ. */
    int getStorageMB() const;
    /** @return Розмір екрану. */
    ScreenSize getScreenSize() const;
    /** @return Операційна система телефону. */
    OS getOS() const;

    /**
     * @brief Виводить інформацію про телефон у стандартний потік виводу.
     * Віртуальний метод, який перевизначається у спадкоємцях.
     */
    virtual void print() const;
};

/**
 * @class ButtonPhone
 * @brief Клас, що представляє кнопковий телефон. Наслідує MobilePhone.
 */
class ButtonPhone : public MobilePhone {
private:
    bool babushkaPhone; ///< Чи класифікується телефон як "бабусяфон" (великі кнопки, SOS).
    int buttonCount;    ///< Кількість фізичних кнопок на корпусі.

public:
    /**
     * @brief Конструктор за замовчуванням для кнопкового телефону.
     */
    ButtonPhone();

    /**
     * @brief Конструктор з параметрами для кнопкового телефону.
     * Приймає параметри базового класу та специфічні для кнопкового телефону.
     * @param isBabushka Чи є це бабусяфоном.
     * @param btnCount Кількість кнопок.
     */
    ButtonPhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                ScreenSize ss, OS os_val, bool isBabushka, int btnCount);
                
    /** @brief Деструктор кнопкового телефону. */
    ~ButtonPhone() override;

    /** @return true, якщо телефон є бабусяфоном. */
    bool isBabushkaPhone() const;
    /** @return Кількість фізичних кнопок. */
    int getButtonCount() const;

    /**
     * @brief Перевизначений метод виводу інформації для кнопкового телефону.
     */
    void print() const override;
};


/**
 * @class FoldablePhone
 * @brief Клас, що представляє сучасний складаний смартфон. Наслідує MobilePhone.
 */
class FoldablePhone : public MobilePhone {
private:
    bool foldsInHalf;            ///< Чи складається екран навпіл.
    ScreenSize foldedScreenSize; ///< Розмір зовнішнього екрану у складеному стані.

public:
    /**
     * @brief Конструктор за замовчуванням для складаного телефону.
     */
    FoldablePhone();

    /**
     * @brief Конструктор з параметрами для складаного телефону.
     * @param folds Чи складається він навпіл.
     * @param fss Розмір екрану у складеному стані.
     */
    FoldablePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                  ScreenSize ss, OS os_val, bool folds, ScreenSize fss);
                  
    /** @brief Деструктор складаного телефону. */
    ~FoldablePhone() override;

    /** @return true, якщо телефон складається навпіл. */
    bool getFoldsInHalf() const;
    /** @return Розмір зовнішнього (додаткового) екрану. */
    ScreenSize getFoldedScreenSize() const;

    /**
     * @brief Перевизначений метод виводу інформації для складаного телефону.
     */
    void print() const override;
};

#endif 