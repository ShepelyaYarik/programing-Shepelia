/**
 * @file entity.h
 * @brief Оголошення класу Phone та допоміжних структур для сутності мобільного телефона.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

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
 * * Містить технічні характеристики пристрою, методи доступу до них,
 * а також інструменти для серіалізації та десеріалізації об'єкта через рядки.
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
     * Ініціалізує всі поля базовими безпечними значеннями.
     */
    Phone();

    /**
     * @brief Параметризований конструктор для ініціалізації об'єкта конкретними даними.
     * @param water Прапорець водостійкості.
     * @param shock Прапорець ударостійкості.
     * @param mod Назва моделі телефона.
     * @param ram Об'єм оперативної пам'яті (МБ).
     * @param storage Об'єм вбудованої пам'яті (МБ).
     * @param screen Роздільна здатність екрану.
     * @param osType Тип операційної системи.
     */
    Phone(bool water, bool shock, const std::string& mod, int ram, int storage, ScreenSize screen, OperatingSystem osType);
    
    /**
     * @brief Конструктор копіювання.
     * Створює дублікат існуючого об'єкта Phone.
     * @param other Посилання на об'єкт, який копіюється.
     */
    Phone(const Phone& other);
    
    /**
     * @brief Деструктор класу Phone.
     * Звільняє ресурси, зайняті об'єктом.
     */
    ~Phone();

    /** @name Гетери (Константні методи доступу) */
    ///@{
    /**
     * @brief Перевіряє, чи є телефон водостійким.
     * @return true, якщо телефон водостійкий, інакше false.
     */
    bool getIsWaterproof() const;

    /**
     * @brief Перевіряє, чи є телефон ударостійким.
     * @return true, if телефон ударостійкий, інакше false.
     */
    bool getIsShockproof() const;

    /**
     * @brief Повертає назву моделі телефона.
     * @return Рядок із назвою моделі.
     */
    std::string getModel() const;

    /**
     * @brief Повертає об'єм оперативної пам'яті.
     * @return Кількість оперативної пам'яті в МБ.
     */
    int getRamMb() const;

    /**
     * @brief Повертає розмір вбудованого сховища.
     * @return Розмір сховища в МБ.
     */
    int getStorageMb() const;

    /**
     * @brief Повертає габарити екрану телефона.
     * @return Об'єкт структури ScreenSize.
     */
    ScreenSize getScreenSize() const;

    /**
     * @brief Повертає тип операційної системи як елемент переліку.
     * @return Значення типу OperatingSystem.
     */
    OperatingSystem getOs() const;

    /**
     * @brief Отримує текстове представлення операційної системи.
     * @return Рядок з назвою ОС (наприклад, "Android" або "iOS").
     */
    std::string getOsString() const;
    ///@}

    /** @name Сетери (Методи модифікації полів) */
    ///@{
    /**
     * @brief Встановлює прапорець водостійкості.
     * @param water Значення водостійкості (true/false).
     */
    void setIsWaterproof(bool water);

    /**
     * @brief Встановлює прапорець ударостійкості.
     * @param shock Значення ударостійкості (true/false).
     */
    void setIsShockproof(bool shock);

    /**
     * @brief Змінює модель телефона.
     * @param mod Рядок з новою назвою моделі.
     */
    void setModel(const std::string& mod);

    /**
     * @brief Встановлює об'єм RAM.
     * @param ram Кількість Мегабайт оперативної пам'яті.
     */
    void setRamMb(int ram);

    /**
     * @brief Встановлює розмір вбудованого сховища.
     * @param storage Кількість Мегабайт постійної пам'яті.
     */
    void setStorageMb(int storage);

    /**
     * @brief Змінює роздільну здатність екрану.
     * @param screen Структура з новими розмірами екрану.
     */
    void setScreenSize(ScreenSize screen);

    /**
     * @brief Змінює операційну систему пристрою.
     * @param osType Нове значення з переліку OperatingSystem.
     */
    void setOs(OperatingSystem osType);
    ///@}

    /**
     * @brief Генерує рядок з інформацією про об'єкт для подальшого виводу або збереження.
     * @return std::string Рядок, що містить усі серіалізовані поля об'єкта через розділювач.
     */
    std::string toString() const;

    /**
     * @brief Заповнює поля об'єкта на базі переданого рядка інформації (десеріалізація).
     * @param data Рядок із текстовими даними, розділеними крапкою з комою.
     */
    void fromString(const std::string& data);
};

#endif // ENTITY_H