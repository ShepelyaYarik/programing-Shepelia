#ifndef ENTITY_H
#define ENTITY_H

#include <string>

/**
 * @brief Структура, що описує фізичні розміри екрану в пікселях.
 */
struct ScreenSize {
    int width;  /**< Ширина екрану у пікселях */
    int height; /**< Висота екрану у пікселях */
};

/**
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
 * * Містить технічні характеристики пристрою, методи доступу до них
 * (гетери/сетери) та інструменти для виводу інформації на екран.
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
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує поля початковими/нульовими значеннями. Логує виклик.
     */
    Phone();

    /**
     * @brief Конструктор з аргументами (параметризований).
     * @param water Флаг водостійкості.
     * @param shock Флаг ударостійкості.
     * @param mod Назва моделі.
     * @param ram Об'єм ОЗУ в Мб.
     * @param storage Об'єм вбудованої пам'яті в Мб.
     * @param screen Структура розміру екрану.
     * @param osType Тип операційної системи.
     */
    Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType);

    /**
     * @brief Конструктор копіювання.
     * Створює дублікат існуючого об'єкта Phone. Логує виклик.
     * @param other Посилання на об'єкт, який копіюється.
     */
    Phone(const Phone& other);

    /**
     * @brief Деструктор класу Phone.
     * Звільняє ресурси об'єкта та логує процес знищення.
     */
    ~Phone();

    /** @name Гетери (Константні методи доступу) */
    ///@{
    bool getIsWaterproof() const;
    bool getIsShockproof() const;
    std::string getModel() const;
    int getRamMb() const;
    int getStorageMb() const;
    ScreenSize getScreenSize() const;
    OperatingSystem getOs() const;
    
    /**
     * @brief Отримує текстове представлення операційної системи.
     * @return Рядок з назвою ОС.
     */
    std::string getOsString() const;
    ///@}

    /** @name Сетери (Методи модифікації полів) */
    ///@{
    void setIsWaterproof(bool water);
    void setIsShockproof(bool shock);
    void setModel(const std::string& mod);
    void setRamMb(int ram);
    void setStorageMb(int storage);
    void setScreenSize(ScreenSize screen);
    void setOs(OperatingSystem osType);
    ///@}

    /**
     * @brief Виводит повну технічну інформацію про телефон у консоль.
     */
    void print() const;
};

#endif // ENTITY_H