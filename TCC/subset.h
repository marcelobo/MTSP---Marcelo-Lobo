/* 
 * File:   subset.h
 * Author: marcelolobo
 *
 * Created on 07 de Outubro de 2014, 15:20
 */

//Struct that stores a subset with "count_elements" items
typedef struct set set;
struct set{
    int* elements;
    int count_elements;
    set* next;
};

void copy_sets(set *dest, set *src, int add_element);
set* subset( int min, int max, int limit, int sum);
