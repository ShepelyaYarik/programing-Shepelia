/**
 * @file entity.h
 * @brief Оголошення сутностей предметної галузі "Мобільний телефон" та їхніх методів.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

/**
 * @struct ScreenSize
 * @brief Структура для представлення роздільної здатності екрану.
 */
struct ScreenSize {
    int width;  ///< Ширина екрану в пікселях.
    int height; ///< Висота екрану в пікселях.
};

/**
 * @enum OS
 * @brief Перелік операційних систем мобільних телефонів.
 */
enum class OS { 
    Android,      ///< Операційна система Android.
    iOS,          ///< Операційна система iOS.
    Symbian,      ///< Операційна система Symbian.
    WindowsPhone, ///< Операційна система Windows Phone.
    None          ///< Операційна система відсутня.
};

/**
 * @brief Перетворює значення переліку OS у рядкове представлення.
 * @param os Значення операційної системи типу OS.
 * @return Рядок (std::string) з назвою ОС.
 */
std::string osToString(OS os);

/**
 * @brief Перетворює рядок із назвою ОС у відповідне значення переліку OS.
 * @param str Рядок із назвою операційної системи.
 * @return Відповідний елемент переліку OS.
 */
OS stringToOS(const std::string& str);

/**
 * @class MobilePhone
 * @brief Базовий клас для представлення загальних характеристик мобільного телефону.
 */
class MobilePhone {
protected:
    bool waterproof;       ///< Чи є телефон водонепроникним.
    bool shockproof;       ///< Чи є телефон ударостійким.
    std::string model;     ///< Назва моделі телефону.
    int ramMB;             ///< Об'єм оперативної пам'яті в мегабайтах (MB).
    int storageMB;         ///< Об'єм внутрішньої пам'яті в мегабайтах (MB).
    ScreenSize screenSize; ///< Роздільна здатність екрану.
    OS os;                 ///< Операційна система пристрою.

public:
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує поля стандартними або нульовими значеннями.
     */
    MobilePhone();

    /**
     * @brief Конструктор з параметрами.
     * @param wp Водонепроникність.
     * @param sp Ударостійкість.
     * @param mod Модель телефону.
     * @param ram Об'єм RAM (МБ).
     * @param storage Об'єм внутрішньої пам'яті (МБ).
     * @param ss Роздільна здатність екрану.
     * @param os_val Операційка система.
     */
    MobilePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, ScreenSize ss, OS os_val);

    /**
     * @brief Віртуальний деструктор класу.
     */
    virtual ~MobilePhone();

    /** @return true, якщо телефон водонепроникний, інакше false. */
    bool isWaterproof() const;

    /** @return true, якщо телефон ударостійкий, інакше false. */
    bool isShockproof() const;

    /** @return Назва моделі пристрою. */
    std::string getModel() const;

    /** @return Об'єм оперативної пам'яті в МБ. */
    int getRamMB() const;

    /** @return Об'єм внутрішньої пам'яті в МБ. */
    int getStorageMB() const;

    /** @return Структура із розмірами екрану. */
    ScreenSize getScreenSize() const;

    /** @return Значення переліку OS. */
    OS getOS() const;

    /**
     * @brief Серіалізація об'єкта в рядок.
     * @return Рядок із даними об'єкта, де поля розділені символом '|'.
     */
    virtual std::string toString() const;

    /**
     * @brief Десеріалізація об'єкта з рядка.
     * @param data Рядок із записаними через роздільник даними об'єкта.
     */
    virtual void fromString(const std::string& data);
};

/**
 * @class ButtonPhone
 * @brief Клас для представлення кнопкового мобільного телефону.
 * Наслідує клас MobilePhone.
 */
class ButtonPhone : public MobilePhone {
private:
    bool babushkaPhone; ///< Чи класифікується телефон як "бабусяфон" (великі кнопки, SOS).
    int buttonCount;    ///< Кількість фізичних кнопок на корпусі.

public:
    /**
     * @brief Конструктор за замовчуванням.
     */
    ButtonPhone();

    /**
     * @brief Конструктор з параметрами.
     * @param wp Водонепроникність.
     * @param sp Ударостійкість.
     * @param mod Модель телефону.
     * @param ram Об'єм RAM (МБ).
     * @param storage Об'єм внутрішньої пам'яті (МБ).
     * @param ss Роздільна здатність екрану.
     * @param os_val Операційна система.
     * @param isBabushka Флаг "бабусяфона".
     * @param btnCount Кількість кнопок.
     */
    ButtonPhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                ScreenSize ss, OS os_val, bool isBabushka, int btnCount);

    /**
     * @brief Деструктор кнопкового телефону.
     */
    ~ButtonPhone() override;

    /** @return true, якщо це бабусяфон, інакше false. */
    bool isBabushkaPhone() const;

    /** @return Кількість фізичних кнопок. */
    int getButtonCount() const;

    /**
     * @brief Серіалізація кнопкового телефону в рядок з урахуванням специфічних полей.
     * @return Рядок формату "ButtonPhone|...базові поля...|babushkaPhone|buttonCount".
     */
    std::string toString() const override;

    /**
     * @brief Десеріалізація даних кнопкового телефону з рядка.
     * @param data Рядок із роздільниками.
     */
    void fromString(const std::string& data) override;
};

/**
 * @class FoldablePhone
 * @brief Клас для представлення складаного смартфона (Foldable).
 * Наслідує клас MobilePhone.
 */
class FoldablePhone : public MobilePhone {
private:
    bool foldsInHalf;            ///< Чи складається гнучкий екран навпіл.
    ScreenSize foldedScreenSize; ///< Роздільна здатність додаткового зовнішнього екрану.

public:
    /**
     * @brief Конструктор за замовчуванням.
     */
    FoldablePhone();

    /**
     * @brief Конструктор з параметрами.
     * @param wp Водонепроникність.
     * @param sp Ударостійкість.
     * @param mod Модель телефону.
     * @param ram Об'єм RAM (МБ).
     * @param storage Об'єм внутрішньої пам'яті (МБ).
     * @param ss Роздільна здатність основного екрану.
     * @param os_val Операційна система.
     * @param folds Здатність складатися навпіл.
     * @param fss Роздільна здатність зовнішнього екрану у складеному стані.
     */
    FoldablePhone(bool wp, bool sp, const std::string& mod, int ram, int storage, 
                  ScreenSize ss, OS os_val, bool folds, ScreenSize fss);

    /**
     * @brief Деструктор складаного телефону.
     */
    ~FoldablePhone() override;

    /** @return true, якщо екран складається навпіл. */
    bool getFoldsInHalf() const;

    /** @return Роздільна здатність додаткового зовнішнього екрану. */
    ScreenSize getFoldedScreenSize() const;

    /**
     * @brief Серіалізація складаного телефону в рядок з урахуванням специфічних полей.
     * @return Рядок формату "FoldablePhone|...базові поля...|foldsInHalf|width|height".
     */
    std::string toString() const override;

    /**
     * @brief Десеріалізація даних складаного телефону з рядка.
     * @param data Рядок із роздільниками.
     */
    void fromString(const std::string& data) override;
};

#endif