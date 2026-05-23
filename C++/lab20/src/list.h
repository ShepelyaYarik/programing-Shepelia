/**
 * @file list.h
 * @brief Оголошення класу List для управління поліморфною колекцією об'єктів Phone.
 */

#ifndef LIST_H
#define LIST_H

#include "entity.h"
#include <cstddef>
#include <string>
#include <iostream>

/**
 * @class List
 * @brief Клас-контейнер, що керує єдиним масивом вказівників на базовий абстрактний клас Phone.
 */
class List {
private:
    Phone** data;  /**< Єдиний масив вказівників на об'єкти ієрархії */
    size_t size;   /**< Поточна кількість елементів у списку */
    
    void clear();

public:
    List();
    
    /**
     * @brief Конструктор копіювання (Правило трьох). Реалізує глибоке копіювання ієрархії через clone().
     */
    List(const List& other);
    
    /**
     * @brief Оператор присвоювання (Правило трьох).
     */
    List& operator=(const List& other);
    
    ~List();

    /**
     * @brief Додає телефон у колекцію (приймає володіння вказівником).
     */
    void addPhone(Phone* phone, size_t pos = 0);
    
    void removePhone(size_t index);
    size_t getSize() const;
    void print() const;

    /** @name Індивідуальні методи для роботи з колекцією */
    ///@{
    /**
     * @brief 1. Розрахувати загальний об’єм оперативної пам’яті всіх телефонів.
     */
    int getTotalRam() const;

    /**
     * @brief 2. Знайти кнопкові телефони, що НЕ є бабусяфонами.
     * @return Новий список-колекція з копіями знайдених об'єктів.
     */
    List getNonGrandpaButtonPhones() const;

    /**
     * @brief 3. Знайти всі складані телефони.
     * @return Новий список-колекція з копіями знайдених об'єктів.
     */
    List getFoldingPhones() const;
    ///@}
	int getTotalStorage() const;
    /** @name Перевантажені оператори індексування */
    ///@{
    Phone& operator[](size_t index);
    const Phone& operator[](size_t index) const;
    ///@}

    void readFromFile(const std::string& fileName);
    void writeToFile(const std::string& fileName);

    friend std::ostream& operator<<(std::ostream& os, const List& list);
    friend std::istream& operator>>(std::istream& is, List& list);
};

#endif // LIST_H