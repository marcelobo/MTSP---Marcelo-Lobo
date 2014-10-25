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
    int alpha = 2, beta = 8, elements = 5, sum = 15;
    
    set *sets = subset(alpha, beta, elements, sum);
    
    return (EXIT_SUCCESS);
}

