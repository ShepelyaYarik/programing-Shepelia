#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define SIZE 10
int myfunction(int list[SIZE]) { //Функція для обрахунку суми масиву
	int sum= 0;
	for (int i=0; i<SIZE; i++){
		sum = sum + list[i] ;
}
printf("сума масива : %d ", sum);// для виведення суми
return sum;
}
void randgen(long min, long max, int number[SIZE]){
	int i = 0;
	for (i=0; i<SIZE; i++ ){ //цикл для внесення в масив рандомних значень
		number[i] = (int)(rand() % (max-min + 1) + min);// (max-min + 1)- наший розмір діапазону, а +min це зміщення діапазону до мінімального значення щоб він не починався з нуля
	}
}
void print(int number[SIZE]){
	for (int i = 0; i<SIZE; i++){
	printf("масив[%d] %d   ", i, number[i]);
	}
}
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