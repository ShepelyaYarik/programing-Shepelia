/**
 * @file list.h
 * @brief Оголошення класу List для керування колекцією об'єктів Phone.
 */

#ifndef LIST_H
#define LIST_H

#include "entity.h"
#include <cstddef>
#include <string>
#include <iostream>

/**
 * @class List
 * @brief Клас-контейнер, що керує динамічним масивом покажчиків на об'єкти Phone.
 */
class List {
private:
    Phone** data;  /**< Динамічний масив покажчиків на Phone */
    size_t size;   /**< Поточна кількість елементів у списку */
    
    void clear();

public:
    List();
    ~List();

    void addPhone(const Phone& phone, size_t pos = 0);
    void removePhone(size_t index);
    size_t getSize() const;
    void print() const;
    int getTotalRam() const;

    /** @name Перевантажені оператори */
    ///@{
    /**
     * @brief Оператори індексування [ ].
     */
    Phone& operator[](size_t index);
    const Phone& operator[](size_t index) const;
    ///}

    void readFromFile(const std::string& fileName);
    void writeToFile(const std::string& fileName);

    /** @name Дружні оператори введення / виведення для списку */
    ///@{
    friend std::ostream& operator<<(std::ostream& os, const List& list);
    friend std::istream& operator>>(std::istream& is, List& list);
    ///@}
};

#endif // LIST_H