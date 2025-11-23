#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "lib.h"
int main(int argc, char *argv[]){
    srand((unsigned int)time(NULL));

    long min = 1;
    long max = 100;

    if (argc > 3){
        printf("помилка занадто багато аргументів\n");
        return 1;
    }
    else if (argc == 3){
        min = strtol(argv[1], NULL, 10);
        max = strtol(argv[2], NULL, 10);
        if (min > max){
            long temp = min;
            min = max;
            max = temp;
        }
    }
    else if (argc == 2){
        long val = strtol(argv[1], NULL, 10);
        if (val > max){
            max = val;
        } else if (val == max){
            max = val;
        } else {
            min = val;
        }
    }

    int number[SIZE];
    randgen(min, max, number);
    print(number);
    myfunction(number);

    return 0;
}