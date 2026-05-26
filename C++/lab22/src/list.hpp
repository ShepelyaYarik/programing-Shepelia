/**
 * @file list.hpp
 * @brief Оголошення та реалізація класу List для управління колекцією об'єктів Phone за допомогою std::vector.
 * @details Оскільки структура проєкту вимагає наявності лише заголовочного файла list.hpp,
 * уся логіка CRUD операцій, фільтрації за варіантом (РЗ), сортування функтором та серіалізації 
 * реалізована безпосередньо в цьому файлі з використанням STL-алгоритмів.
 * @author Ярослав Шепеля
 * @date 2026
 */

#ifndef LIST_HPP
#define LIST_HPP

#include "entity.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

/**
 * @struct CompareByRam
 * @brief Функтор для порівняння двох об'єктів Phone за об'ємом оперативної пам'яті.
 * @details Використовується в алгоритмах сортування STL (зокрема, std::sort) 
 * для впорядкування пристроїв у векторі від меншого об'єму RAM до більшого.
 */
struct CompareByRam {
    /**
     * @brief Перевантажений оператор "круглі дужки" для порівняння двох вказівників на Phone.
     * @param a Вказівник на перший телефон.
     * @param b Вказівник на другий телефон.
     * @return true, якщо RAM першого телефона менша за RAM другого, інакше — false.
     */
    bool operator()(const Phone* a, const Phone* b) const {
        if (!a || !b) return false;
        return a->getRamMb() < b->getRamMb();
    }
};

/**
 * @class List
 * @brief Клас-контейнер, що керує колекцією об'єктів ієрархії Phone на базі std::vector.
 * @details Забезпечує виконання CRUD операцій за допомогою методів динамічного масиву STL,
 * безпечну обробку винятків, глибоке копіювання елементів, роботу з файлами та автоматичне керування пам'яттю.
 */
class List {
private:
    std::vector<Phone*> phones; /**< Динамічний масив STL, що зберігає вказівники на об'єкти типу Phone */
    
    /**
     * @brief Внутрішній приватний метод для повного очищення вектора.
     * @details Проходить циклом по всьому контейнеру std::vector, викликає оператор delete 
     * для кожного динамічно створеного об'єкта Phone, після чого повністю очищує сам вектор.
     */
    void clear() {
        for (Phone* phone : phones) {
            delete phone;
        }
        phones.clear();
    }

public:
    /**
     * @brief Конструктор за замовчуванням. Створює порожній контейнер вектора.
     */
    List() = default;
    
    /**
     * @brief Конструктор копіювання.
     * @details Виконує глибоке копіювання поліморфної ієрархії об'єктів. Спочатку резервує 
     * необхідну пам'ять у векторі для уникнення зайвих перевиділений, після чого проходиться 
     * по оригінальному списку та копіює кожен телефон через віртуальний метод clone().
     * @param other Константне посилання на оригінальний об'єкт класу List для копіювання.
     */
    List(const List& other) {
        phones.reserve(other.phones.size());
        for (const Phone* phone : other.phones) {
            if (phone) {
                phones.push_back(phone->clone());
            }
        }
    }
    
    /**
     * @brief Operator присвоювання копіюванням.
     * @details Безпечно оновлює вміст поточного контейнера. Спочатку повністю звільняє 
     * виділену динамічну пам'ять за допомогою методу clear(), резервує об'єм під нові елементи 
     * та виконує глибоке копіювання з правого операнда. Реалізовано захист від самоприсвоювання.
     * @param other Константне посилання на об'єкт класу List, дані якого копіюються.
     * @return Посилання на поточний оновлений об'єкт List (*this).
     */
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            phones.reserve(other.phones.size());
            for (const Phone* phone : other.phones) {
                if (phone) {
                    phones.push_back(phone->clone());
                }
            }
        }
        return *this;
    }
    
    /**
     * @brief Деструктор класу List.
     * @details Автоматично викликає внутрішній метод clear() для безпечного очищення 
     * пам'яті в купі та запобігання витокам пам'яті (memory leaks).
     */
    ~List() {
        clear();
    }

    // CRUD операції на базі std::vector 
    
    /**
     * @brief Додає телефон у колекцію (Операція Create).
     * @details Якщо параметр pos дорівнює 0 (значення за замовчуванням), елемент вставляється 
     * на початок вектора за допомогою ітератора begin(). 
     * Якщо позиція вказана в кінці або за межами, застосовується швидкий push_back().
     * @param phone Вказівник на створений у динамічній пам'яті об'єкт телефону.
     * @param pos Порядковий індекс місця вставки в колекцію.
     */
    void addPhone(Phone* phone, size_t pos = 0) {
        if (!phone) return;
        if (pos == 0) {
            phones.insert(phones.begin(), phone); 
        } else if (pos >= phones.size()) {
            phones.push_back(phone); 
        } else {
            phones.insert(phones.begin() + static_cast<ptrdiff_t>(pos), phone);
        }
    }
    
    /**
     * @brief Видаляє телефон зі списку за його порядковим індексом (Операція Delete).
     * @details Звільняє динамічную пам'ять об'єкта в купі за прямим індексом, а потім 
     * видаляє сам елемент-вказівник з вектора за допомогою ітератора зсування.
     * @param index Порядковий номер елемента в масиві (від 0 до size - 1).
     * @throw std::out_of_range Якщо переданий індекс виходить за межі фактичного розміру вектора.
     */
    void removePhone(size_t index) {
        if (index >= phones.size()) {
            throw std::out_of_range("Індекс виходить за межі списку!");
        }
        delete phones[index]; 
        phones.erase(phones.begin() + static_cast<ptrdiff_t>(index)); 
    }
    
    /**
     * @brief Оновлює модель телефону за вказаним індексом (Операція Update).
     * @details Напряму звертається до об'єкта за індексом за час O(1) та модифікує його назву.
     * @param index Порядковий номер елемента для модифікації.
     * @param newModel Нова назва моделі або повна назва пристрою.
     * @throw std::out_of_range Якщо індекс перевищує або дорівнює розміру вектора.
     */
    void updateModel(size_t index, const std::string& newModel) {
        if (index >= phones.size()) {
            throw std::out_of_range("Індекс виходить за межі списку!");
        }
        phones[index]->setModel(newModel);
    }

    /**
     * @brief Отримує поточну кількість елементів у контейнері.
     * @return Кількість елементів у векторі типу size_t.
     */
    size_t getSize() const { return phones.size(); }

    /**
     * @brief Виводить відформатовану інформацію про всі елементи списку в консоль (Операція Read).
     * @details Реалізовано за допомогою стандартного алгоритму STL std::for_each та 
     * лямбда-виразу, який виконує захват лічильника для відображення індексів [i].
     */
    void print() const {
        if (phones.empty()) {
            std::cout << "Список порожній." << std::endl;
            return;
        }
        size_t i = 0;
        std::for_each(phones.begin(), phones.end(), [&i](const Phone* phone) {
            if (phone) {
                std::cout << "[" << i++ << "] " << *phone 
                          << " | Додатково: " << phone->toString() << std::endl;
            }
        });
    }

    // --- Індивідуальні методи розрахункового завдання (РЗ) ---
    
    /**
     * @brief [Індивідуальне завдання №1]: Обчислює сумарний об'єм оперативної пам'яті (RAM).
     * @details Обходить весь вектор за допомогою алгоритму std::for_each та накопичує 
     * значення гетера getRamMb() у локальну змінну.
     * @return Загальна кількість мегабайт оперативної пам'яті (int).
     */
    int getTotalRam() const {
        int totalRam = 0;
        std::for_each(phones.begin(), phones.end(), [&totalRam](const Phone* phone) {
            if (phone) totalRam += phone->getRamMb();
        });
        return totalRam;
    }

    /**
     * @brief Додатковий метод: Обчислює сумарну ємність вбудованого сховища (Storage) усіх пристроїв.
     * @details Працює аналогічно методу підрахунку RAM, акумулюючи дані з getStorageMb().
     * @return Загальна кількість мегабайт вбудованої пам'яті (int).
     */
    int getTotalStorage() const {
        int totalStorage = 0;
        std::for_each(phones.begin(), phones.end(), [&totalStorage](const Phone* phone) {
            if (phone) totalStorage += phone->getStorageMb();
        });
        return totalStorage;
    }

    /**
     * @brief [Індивідуальне завдання №2]: Знаходить кнопкові телефони, які НЕ є бабусяфонами.
     * @details Використовує механізм RTTI (dynamic_cast) для безпечного приведення типу базового 
     * вказівника до ButtonPhone*. Якщо приведення успішне і прапорець getIsGrandpaPhone() 
     * дорівнює false, створюється глибока копія об'єкта, яка додається у результуючий список.
     * @return Новий об'єкт класу List із копіями знайдених кнопкових пристроїв.
     */
    List getNonGrandpaButtonPhones() const {
        List result;
        std::for_each(phones.begin(), phones.end(), [&result](const Phone* phone) {
            auto* btnPhone = dynamic_cast<const ButtonPhone*>(phone);
            if (btnPhone && !btnPhone->getIsGrandpaPhone()) {
                result.addPhone(btnPhone->clone());
            }
        });
        return result;
    }

    /**
     * @brief [Індивідуальне завдання №3]: Знаходить усі складані телефони.
     * @details Застосовує dynamic_cast для фільтрації та відбору пристроїв типу FoldingPhone 
     * серед елементів поліморфного вектора std::vector.
     * @return Новий об'єкт класу List, заповнений копіями складаних телефонів.
     */
    List getFoldingPhones() const {
        List result;
        std::for_each(phones.begin(), phones.end(), [&result](const Phone* phone) {
            auto* foldPhone = dynamic_cast<const FoldingPhone*>(phone);
            if (foldPhone) {
                result.addPhone(foldPhone->clone());
            }
        });
        return result;
    }

    // --- Обов'язкові завдання ЛР №22 ---
    
    /**
     * @brief Сортує поточну колекцію за об'ємом RAM з використанням функтора.
     * @details Викликає глобальний алгоритм сортування std::sort, передаючи туди ітератори 
     * початку/кінця вектора та екземпляр структури-компаратора CompareByRam.
     */
    void sortByRam() {
        std::sort(phones.begin(), phones.end(), CompareByRam());
    }

    /**
     * @brief Функція об’єднання двох класів-списків (Копіювання та злиття векторів).
     * @details Оптимізує пам'ять через reserve(), після чого перебирає елементи переданого 
     * контейнера "other", створює їхні глибокі копії через clone() та додає їх у кінець поточного.
     * @param other Константне посилання на інший список-колекцію List.
     */
    void mergeWith(const List& other) {
        phones.reserve(phones.size() + other.phones.size());
        for (const Phone* phone : other.phones) {
            if (phone) {
                phones.push_back(phone->clone());
            }
        }
    }

    // --- Перевантажені оператори індексування ---
    
    /**
     * @brief Неконстантний оператор доступу за індексом.
     * @details Оскільки std::vector гарантує суцільне розміщення елементів у пам'яті, 
     * доступ до елемента за індексом відбувається миттєво за час O(1).
     * @param index Порядковий індекс шуканого елемента.
     * @return Посилання на базовий об'єкт класу Phone (&).
     * @throw std::out_of_range Якщо переданий індекс виходить за межі фактичного розміру вектора.
     */
    Phone& operator[](size_t index) {
        if (index >= phones.size()) { throw std::out_of_range("Індекс виходить за межі!"); }
        return *phones[index];
    }

    /**
     * @brief Константний оператор доступу за індексом для об'єктів типу read-only.
     * @details Забезпечує миттєвий доступ за час O(1) для константних об'єктів контейнера, 
     * гарантуючи незмінність елементів.
     * @param index Порядковий індекс шуканого елемента.
     * @return Константне посилання на базовий об'єкт класу Phone (const &).
     * @throw std::out_of_range Якщо індекс виходить за межі фактичного розміру вектора.
     */
    const Phone& operator[](size_t index) const {
        if (index >= phones.size()) { throw std::out_of_range("Індекс виходить за межі!"); }
        return *phones[index];
    }

    // --- Введення / Виведення (Робота з файлами) ---
    
    /**
     * @brief Записує поточний вміст колекції у текстовий файл.
     * @details Ініціалізує файловий потік std::ofstream та спрямовує туди дані за 
     * допомогою перевантаженого дружнього оператора виведення `<<`.
     * @param fileName Рядок-шлях на диску куди буде збережено базу даних.
     */
    void writeToFile(const std::string& fileName) {
        std::ofstream os(fileName);
        if (!os.is_open()) return;
        os << *this;
        os.close();
    }

    /**
     * @brief Зчитує та повністю відновлює базу даних телефонів із текстового файлу.
     * @details Відкриває потік std::ifstream та делегує зчитування рядків і побудову 
     * об'єктів ієрархії перевантаженому оператору введення `>>`.
     * @param fileName Рядок-шлях до існуючого структурованого файлу на диску.
     */
    void readFromFile(const std::string& fileName) {
        std::ifstream is(fileName);
        if (!is.is_open()) return;
        is >> *this;
        is.close();
    }

    /**
     * @brief Перевантажений дружній оператор виведення у потік (Серіалізація).
     * @details Циклічно проходить по вектору і поліморфно записує текстовий маркований 
     * рядок параметрів (отриманий через toString()) для кожного телефону з нового рядка.
     * @param os Потік виведення (std::ostream).
     * @param list Константне посилання на об'єкт списку, що підлягає збереженню.
     * @return Посилання на потік виведення (std::ostream&).
     */
    friend std::ostream& operator<<(std::ostream& os, const List& list) {
        for (const Phone* phone : list.phones) {
            if (phone) os << phone->toString() << "\n";
        }
        return os;
    }



const Phone* getMaxRamPhone() const {
	auto it = std::max_element(phones.begin(), phones.end(), [](const Phone* a, const Phone* b ){
		return a->getRamMb() < b->getRamMb();
	});
	return *it;
}
    /**
     * @brief Перевантажений дружній оператор введення з потоку (Десеріалізація / Фабрика об'єктів).
     * @details Спочатку повністю очищує поточну колекцію. Потім покроково зчитує файл по рядках, 
     * аналізує початковий маркер ("BUTTON", "FOLDING", "SMART"), динамічно створює відповідний 
     * об'єкт-нащадок і запускає його внутрішній метод розбору полів з рядка від символу-розділювача '|'.
     * @param is Вхідний текстовий потік даних (std::istream).
     * @param list Посилання на об'єкт списку, куди відновлюються зчитані дані.
     * @return Посилання на вхідний потік даних (std::istream&).
     */
    friend std::istream& operator>>(std::istream& is, List& list) {
        list.clear();
        std::string line;
        while (std::getline(is, line)) {
            if (line.empty()) continue;
            size_t pos = line.find('|');
            if (pos == std::string::npos) continue;
            std::string marker = line.substr(0, pos);

            Phone* current = nullptr;
            if (marker == "BUTTON") { current = new ButtonPhone(); } 
            else if (marker == "FOLDING") { current = new FoldingPhone(); } 
            else if (marker == "SMART") { current = new SmartPhone(); }

            if (current != nullptr) {
                current->fromString(line);
                list.addPhone(current, list.phones.size());
            }
        }
        return is;
    }
};

#endif // LIST_HPP