/* 
 * File:   main.c
 * Author: marcelolobo
 *
 * Created on 07 de Outubro de 2014, 15:20
 */

#include <stdio.h>
#include <stdlib.h>
#include"subset.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int alpha = 1, beta = 5, elements = 2, sum = 5;
    
    set *sets = subset(alpha, beta, elements, sum);
    
    return (EXIT_SUCCESS);
}

