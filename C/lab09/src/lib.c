#include "lib.h"
int myfunction(int list[SIZE]) { 
    int sum = 0;
    for (int i = 0; i < SIZE; i++){
        sum = sum + list[i];
    }
    printf("сума масива : %d \n", sum);
    return sum;
}

void randgen(long min, long max, int number[SIZE]){
    int i = 0;
    for (i = 0; i < SIZE; i++ ){
        number[i] = (int)(rand() % (max - min + 1) + min);
    }
}

void print(int number[SIZE]){
    for (int i = 0; i < SIZE; i++){
        printf("масив[%d] %d   ", i, number[i]);
    }
    printf("\n");
}
int myfunction1(int list[SIZE]){
	int sum = 0;
	for (int i= 0; i<3; i++){
		sum = sum + list[i];
	}
	return sum;
}