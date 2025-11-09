/**
 * @file main.c
 * @brief Демонстрація роботи з масивами та функціями
 *
 * Ця програма генерує масив випадкових чисел у заданому діапазоні,
 * виводить його на екран та обчислює суму його елементів.
 * Діапазон генерації (min, max) можна задати через аргументи командного рядка.
 *
 * @author Шепеля Я. М.
 * @date 09-11-2025
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define SIZE 10
/**
 * @brief Обчислює суму елементів масиву.
 *
 * Функція проходить по всім елементам масиву та додає їх.
 * Також виводить розраховану суму в консоль.
 \code
	int sum= 0;
	for (int i=0; i<SIZE; i++){
		sum = sum + list[i] ;
}
printf("сума масива : %d ", sum);
return sum;
 \endcode
 *
 * @param list[SIZE] Вхідний масив цілих чисел.
 * @return Загальна сума елементів масиву (int).
 */
int myfunction(int list[SIZE]) { 
	int sum= 0;
	for (int i=0; i<SIZE; i++){
		sum = sum + list[i] ;
}
printf("сума масива : %d ", sum);
return sum;
}
/**
 * @brief Заповнює масив випадковими числами.
 *
 * Генерує цілі числа в діапазоні [min, max] (включно)
 * та записує їх у наданий масив.
 \code
 	for (i=0; i<SIZE; i++ ){
		number[i] = (int)(rand() % (max-min + 1) + min);
 \endcode
 *
 * @param min Нижня межа діапазону (включно).
 * @param max Верхня межа діапазону (включно).
 * @param number[out] Масив, який буде заповнено випадковими числами.
 */
void randgen(long min, long max, int number[SIZE]){
	int i = 0;
	for (i=0; i<SIZE; i++ ){
		number[i] = (int)(rand() % (max-min + 1) + min);
	}
}
/**
 * @brief Виводить вміст масиву в консоль.
 *
 * Друкує кожен елемент масиву разом з його індексом.
 \code
 for (int i = 0; i<SIZE; i++){
	printf("масив[%d] %d   ", i, number[i]);
 \endcode
 *
 * @param number[SIZE] Масив, елементи якого потрібно надрукувати.
 */
void print(int number[SIZE]){
	for (int i = 0; i<SIZE; i++){
	printf("масив[%d] %d   ", i, number[i]);
	}
}
/**
 * @brief Головна функція програми.
 *
 * Ініціалізує генератор випадкових чисел.
 * Обробляє аргументи командного рядка (argc, argv) для встановлення 
 * мінімального (min) та максимального (max) значень для генератора.
 * * Логіка аргументів:
 * - 0 аргументів (argc == 1): Використовуються значення за замовчуванням (min=1, max=100).
 * - 1 аргумент (argc == 2): Встановлює min або max.
 * - 2 аргументи (argc == 3): Встановлює min та max.
 * - 3+ аргументи (argc > 3): Помилка, програма завершується.
 \code
 if (argc > 3){
		printf("помилка занадто багато аргументів");
		return 1;
	}
	else if (argc == 3){
		min= strtol(argv[1], NULL, 10);
		max= strtol(argv[2], NULL, 10);
		if (min>max){
			long temp = min;
			min = max;
			max = temp;
		}
	}
	else if (argc == 2){
		if (strtol(argv[1], NULL, 10) > max){
		max = strtol(argv[1], NULL, 10);}
		else if (strtol(argv[1], NULL, 10) == max){
		max = strtol(argv[1], NULL, 10);}
		else {
			min = strtol(argv[1], NULL, 10);
		}
		}
 \endcode
 * Послідовно викликає randgen(), print() та myfunction().
 *
 * @param argc Кількість аргументів командного рядка.
 * @param argv Масив рядків (аргументи командного рядка).
 * @return 0 у разі успішного виконання.
 * @return 1 у разі помилки (надано забагато аргументів).
 */
int main(int argc, char *argv[]){
	srand((unsigned int)time(NULL));// для роботи рандому
	long min= 1;
	long max= 100;
	if (argc > 3){// перевірка кількості аргументів в разі якого буде помилка бо забагато
		printf("помилка занадто багато аргументів");
		return 1;
	}
	else if (argc == 3){// перевірка кількості аргументів яка нам підходить з кодом всередині для присваювання значень в min та max
		min= strtol(argv[1], NULL, 10);//strtol- функція для переведення string to long як альтернатива atoi
		max= strtol(argv[2], NULL, 10);
		if (min>max){//перевірка якщо перший аргумент більше ніж другий вносимо то в той
			long temp = min;
			min = max;
			max = temp;
		}
	}
	else if (argc == 2){ //перевірка для 2 аргументів з кодом внесення якщо аргумент більше ніж максимальне значення вносимо його в мінімальне , а якщо ні то в максимальне
		if (strtol(argv[1], NULL, 10) > max){
		max = strtol(argv[1], NULL, 10);}
		else if (strtol(argv[1], NULL, 10) == max){
		max = strtol(argv[1], NULL, 10);}
		else {
			min = strtol(argv[1], NULL, 10);
		}
		}
	int number[SIZE];//наший масив
	int i = 0;
	randgen(min, max, number);
	print(number);
	long totalsum = myfunction(number);
	return 0;
}