/* 
 * File:   main.c
 * Author: marcelolobo
 *
 * Created on 07 de Outubro de 2014, 15:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"subset.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int alpha = 2, beta = 5, elements = 6, sum = 13;
    float time;
    clock_t start, finish;
    
    start = clock();
    set *sets = subset(alpha, beta, elements, sum);
    finish = clock();
    
    time = (double)(finish - start)*1000/ CLOCKS_PER_SEC;
    
    printf("Time spent: %.3f ms", time);
    return (EXIT_SUCCESS);
}

