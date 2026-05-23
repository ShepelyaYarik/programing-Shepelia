/**
 * @file list.cpp
 * @brief Реалізація методів класу List, включно з індивідуальними розрахунковими методами.
 */

#include "list.h"
#include <fstream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::istream;

/**
 * @brief Конструктор за замовчуванням.
 * Ініціалізує порожній список без виділення динамічної пам'яті.
 */
List::List() : data(nullptr), size(0) {}

/**
 * @brief Конструктор копіювання (Глибоке копіювання).
 * Створює новий незалежний масив вказівників та поліморфно дублює кожен об'єкт телефону.
 * @param other Оригінальний об'єкт списку, з якого знімається копія.
 */
List::List(const List& other) : data(nullptr), size(0) {
    size = other.size;
    if (size > 0) {
        data = new Phone*[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i]->clone(); // Поліморфне глибоке копіювання
        }
    }
}

/**
 * @brief Перевантажений оператор присвоювання копіюванням.
 * Забезпечує безпечне перезаписування існуючого списку новими даними, уникаючи витоків пам'яті та самоприсвоювання.
 * @param other Список, дані якого копіюються.
 * @return Посилання на поточний оновлений об'єкт списку (*this).
 */
List& List::operator=(const List& other) {
    if (this != &other) {
        clear();
        size = other.size;
        if (size > 0) {
            data = new Phone*[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i]->clone();
            }
        }
    }
    return *this;
}

/**
 * @brief Деструктор класу List.
 * Автоматично запускає повне очищення пам'яті, виділеної під елементи списку та масив.
 */
List::~List() {
    clear();
}

/**
 * @brief Метод повного очищення списку.
 * Звільняє пам'ять в купі, виділену під кожен конкретний об'єкт телефону, видаляє масив вказівників та занулює параметри списку.
 */
void List::clear() {
    if (data != nullptr) {
        for (size_t i = 0; i < size; ++i) {
            delete data[i]; // Очищення об'єктів у масиві вказівників
        }
        delete[] data;      // Очищення самого масиву вказівників
        data = nullptr;
    }
    size = 0;
}

/**
 * @brief Додає вказівник на телефон у вказану позицію списку.
 * Створює новий розширений динамічний масив, копіює туди старі адреси та інтегрує новий елемент.
 * @param phone Вказівник на створений об'єкт телефону.
 * @param pos Індекс позиції куди вставити пристрій (якщо pos > size, вставляє в кінець).
 */
void List::addPhone(Phone* phone, size_t pos) {
    if (!phone) return;
    if (pos > size) {
        pos = size;
    }

    Phone** newData = new Phone*[size + 1];

    for (size_t i = 0; i < pos; ++i) {
        newData[i] = data[i];
    }

    newData[pos] = phone; // Записуємо переданий вказівник

    for (size_t i = pos; i < size; ++i) {
        newData[i + 1] = data[i];
    }

    delete[] data;
    data = newData;
    size++;
}

/**
 * @brief Видаляє телефон зі списку за заданим індексом.
 * Звільняє пам'ять об'єкта в купі, зсуває інші елементи для усунення дірок та зменшує розмір масиву.
 * @param index Порядковий номер (індекс) пристрою для видалення.
 * @throw std::out_of_range Якщо переданий індекс не існує в межах масиву.
 */
void List::removePhone(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Індекс виходить за межі списку!");
    }

    Phone** newData = nullptr;
    if (size - 1 > 0) {
        newData = new Phone*[size - 1];
        for (size_t i = 0, j = 0; i < size; ++i) {
            if (i == index) {
                delete data[i]; // Видаляємо сам об'єкт
                continue;
            }
            newData[j++] = data[i];
        }
    } else {
        delete data[index];
    }

    delete[] data;
    data = newData;
    size--;
}

/**
 * @brief Гетер поточної кількості елементів у списку.
 * @return Поточний розмір масиву (кількість телефонів) типу size_t.
 */
size_t List::getSize() const { return size; }

/**
 * @brief Виводить відформатований список пристроїв у консоль.
 * Використовує перевантажений оператор `<<` для базових полів та поліморфний метод `toString()` для унікальних полів нащадків.
 */
void List::print() const {
    if (size == 0) {
        cout << "Список порожній." << endl;
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        cout << "[" << i << "] " << *data[i] 
             << " | Додатково: " << data[i]->toString() << endl;
    }
}

// --- ІНДИВІДУАЛЬНІ МЕТОДИ ВАРІАНТА ---

/**
 * @brief Розраховує сумарний об'єм RAM для всіх пристроїв у списку.
 * @return Загальна кількість мегабайт оперативної пам'яті (int).
 */
int List::getTotalRam() const {
    int totalRam = 0;
    for (size_t i = 0; i < size; ++i) {
        totalRam += data[i]->getRamMb();
    }
    return totalRam;
}

/**
 * @brief Фільтрує список та відбирає кнопкові телефони, що не є бабусяфонами.
 * Використовує RTTI (`dynamic_cast`) для верифікації типу об'єкта.
 * @return Новий об'єкт класу List, що містить глибокі копії знайдених пристроїв.
 */
List List::getNonGrandpaButtonPhones() const {
    List result;
    for (size_t i = 0; i < size; ++i) {
        // Використовуємо dynamic_cast для перевірки типу в ієрархії
        ButtonPhone* btnPhone = dynamic_cast<ButtonPhone*>(data[i]);
        if (btnPhone != nullptr) {
            if (!btnPhone->getIsGrandpaPhone()) {
                result.addPhone(btnPhone->clone());
            }
        }
    }
    return result;
}

/**
 * @brief Фільтрує список та відбирає лише складані телефони (FoldingPhone).
 * Використовує `dynamic_cast` для динамічного кастингу та перевірки типу пристрою в пам'яті.
 * @return Новий об'єкт класу List, що містить незалежні копії складаних телефонів.
 */
List List::getFoldingPhones() const {
    List result;
    for (size_t i = 0; i < size; ++i) {
        FoldingPhone* foldPhone = dynamic_cast<FoldingPhone*>(data[i]);
        if (foldPhone != nullptr) {
            result.addPhone(foldPhone->clone());
        }
    }
    return result;
}

/**
 * @brief Перевантажений оператор доступу за індексом (неконстантний).
 * Дозволяє пряме звернення до об'єкта телефону за аналогією зі звичайним масивом.
 * @param index Шуканий порядковий номер елемента.
 * @return Посилання на об'єкт класу Phone (`Phone&`).
 * @throw std::out_of_range Якщо індекс виходить за фактичні межі поточної колекції.
 */
Phone& List::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Індекс виходить за межі!");
    return *data[index];
}

/**
 * @brief Перевантажений оператор доступу за індексом (константний).
 * Викликається, коли сам контейнер передано у функцію як read-only (`const List&`).
 * @param index Шуканий порядковий номер елемента.
 * @return Константне посилання на об'єкт класу Phone (`const Phone&`).
 * @throw std::out_of_range Якщо індекс перевищує або дорівнює розміру списку.
 */
const Phone& List::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Індекс виходить за межі!");
    return *data[index];
}

/**
 * @brief Зчитує базу даних телефонів зі структурованого текстового файлу.
 * Автоматично відкриває файловий потік та перенаправляє його у перевизначений оператор `>>`.
 * @param fileName Шлях до файлу на диску.
 */
void List::readFromFile(const string& fileName) {
    ifstream is(fileName);
    if (!is.is_open()) return;
    is >> *this;
    is.close();
}

/**
 * @brief Записує поточну базу даних пристроїв у текстовий файл.
 * Автоматично ініціалізує потік виведення та делегує роботу перевантаженому оператору `<<`.
 * @param fileName Шлях до файлу куди зберегти базу.
 */
void List::writeToFile(const string& fileName) {
    ofstream os(fileName);
    if (!os.is_open()) return;
    os << *this;
    os.close();
}

/**
 * @brief Дружній оператор виведення списку у потік (Серіалізація).
 * Проходить по всій колекції та поліморфно записує маркований рядок характеристик кожного телефону.
 * @param os Потік виведення (наприклад, файловий потік ofstream).
 * @param list Посилання на константний список, що підлягає збереженню.
 * @return Посилання на потік виведення (`ostream&`).
 */
ostream& operator<<(ostream& os, const List& list) {
    for (size_t i = 0; i < list.size; ++i) {
        os << list.data[i]->toString() << "\n"; // Поліморфний запис у рядок
    }
    return os;
}

int List::getTotalStorage() const {
	int totalStorage = 0;
	for (size_t i = 0; i < size; ++i){
		totalStorage += data[i]->getStorageMb();
	}
	return totalStorage;
}



/**
 * @brief Дружній оператор введення даних з потоку (Десеріалізація / Фабрика об'єктів).
 * Очищує старий вміст контейнера, зчитує файл по рядках, за текстовими маркерами ("BUTTON", "FOLDING", "SMART") 
 * ініціалізує відповідні класи-нащадки та заповнює їх поля методом `fromString()`.
 * @param is Вхідний текстовий потік (наприклад, ifstream).
 * @param list Посилання на об'єкт списку, куди відновлюються дані.
 * @return Посилання на вхідний потік (`istream&`).
 */
istream& operator>>(istream& is, List& list) {
    list.clear();
    string line;
    while (std::getline(is, line)) {
        if (line.empty()) continue;
        
        // Визначаємо тип об'єкта за маркером на початку рядка
        size_t pos = line.find('|');
        if (pos == string::npos) continue;
        string marker = line.substr(0, pos);

        Phone* current = nullptr;
        if (marker == "BUTTON") {
            current = new ButtonPhone();
        } else if (marker == "FOLDING") {
            current = new FoldingPhone();
        } else if (marker == "SMART") { 
            current = new SmartPhone();
        }

        if (current != nullptr) {
            current->fromString(line);
            list.addPhone(current, list.size); // Додаємо покажчик у список
        }
    }
    return is;
}