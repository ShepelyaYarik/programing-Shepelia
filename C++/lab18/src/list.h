/**
 * @file list.h
 * @brief Оголошення класу-колекції PhoneList для керування масивом вказівників на телефони.
 */

#ifndef LIST_H
#define LIST_H

#include "entity.h"
#include <cstddef>
#include <string>

/**
 * @class PhoneList
 * @brief Колекція поліморфних об'єктів типу MobilePhone, реалізована через динамічний масив вказівників.
 */
class PhoneList {
private:
    MobilePhone** phones; ///< Динамічний масив вказівників на об'єкти MobilePhone.
    size_t count;         ///< Кількість елементів, що зараз знаходяться в масиві.
    size_t capacity;      ///< Максимальна виділена пам'ять під масив (ємність).

    /**
     * @brief Приватний метод для автоматичного збільшення ємності масиву вдвічі.
     */
    void resize();

public:
    /**
     * @brief Конструктор за замовчуванням. Створює початковий масив.
     */
    PhoneList();

    /**
     * @brief Деструктор. Повністю звільняє пам'ять під всіма об'єктами колекції та сам масив.
     */
    ~PhoneList();

    /**
     * @brief Додає вказівник на новий телефон у колекцію.
     * @param phone Вказівник на об'єкт телефону створений через new.
     * @param pos Індекс позиції вставки (за замовчуванням 0 — початок списку).
     */
    void addPhone(MobilePhone* phone, size_t pos = 0);

    /**
     * @brief Видаляє телефон із колекції за індексом та звільняє під ним пам'ять.
     * @param index Індекс елемента для видалення.
     * @note Викидає std::out_of_range, якщо індекс невірний.
     */
    void removePhone(size_t index);

    /**
     * @brief Повністю очищує список від елементів із коректним видаленням пам'яті.
     */
    void clear();
    
    /**
     * @brief Виводить у консоль серіалізований стан усіх елементів списку.
     */
    void printAll() const;

    /**
     * @brief Обчислює сумарний об'єм RAM усіх пристроїв у списку.
     * @return Загальна кількість мегабайт RAM.
     */
    int calculateTotalRAM() const;

    /**
     * @brief Знаходить і виводить у консоль усі кнопкові телефони, які НЕ є "бабусяфонами".
     */
    void printNonBabushkaButtonPhones() const;

    /**
     * @brief Знаходить і виводить у консоль усі моделі типу FoldablePhone.
     */
    void printFoldablePhones() const;

    /**
     * @brief Зчитує дані телефонів із текстового файлу. Попередньо список очищується.
     * @param fileName Шлях до файлу (рядок).
     * @note Викидає std::runtime_error, якщо файл не вдалося відкрити.
     */
    void readFromFile(std::string& fileName);

    /**
     * @brief Записує серіалізовані дані списку у текстовий файл.
     * @param fileName Шлях до файлу для запису.
     * @note Викидає std::runtime_error, якщо виникла помилка створення/відкриття файлу.
     */
    void writeToFile(std::string& fileName);
    
    /**
     * @brief Повертає поточну кількість телефонів у списку.
     * @return Поточний розмір (size_t).
     */
    size_t getCount() const { return count; }
};

#endif // LIST_H