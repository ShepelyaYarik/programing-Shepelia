#ifndef LIST_H
#define LIST_H

#include "entity.h"
#include <cstddef>

/**
 * @class List
 * @brief Клас-контейнер, що керує динамічним масивом покажчиків на об'єкти Phone.
 */
class List {
private:
    Phone** data; /**< Масив покажчиків на Phone */
    size_t size;  /**< Поточна кількість елементів у списку */

public:
    /** @brief Конструктор за замовчуванням */
    List();

    /** @brief Деструктор з очищенням всієї виділеної пам'яті */
    ~List();

    /** @brief Додає телефон у масив на задану позицію pos */
    void addPhone(const Phone& phone, size_t pos = 0);

    /** @brief Видаляє телефон з колекції за його індексом */
    void removePhone(size_t index);

    /** @brief Отримує неконстантне посилання на телефон */
    Phone& getPhone(size_t index);

    /** @brief Отримує константне посилання на телефон */
    const Phone& getPhone(size_t index) const; 

    /** @brief Повертає кількість елементів у списку */
    size_t getSize() const;

    /** @brief Виводить увесь список телефонів у консоль */
    void print() const;

    /** @brief Підраховує сумарний об'єм ОЗУ (Індивідуальне завдання) */
    int getTotalRam() const;
};

#endif // LIST_H