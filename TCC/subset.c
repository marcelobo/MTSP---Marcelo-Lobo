/* 
 * File:   subset.c
 * Author: marcelolobo
 *
 * Created on 07 de Outubro de 2014, 15:20
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "subset.h"

#define DEBUG

//Copy a set into another pointer
void copy_sets(set *dest, set *src, int add_element){
    set *aux_dest, *aux_src;
    
    if(src != NULL){
        dest->count_elements = src->count_elements;
        if(add_element != 0){ //Adding an element to the set
            dest->elements = (int*) malloc(sizeof(int) * (src->count_elements + 1));
            memcpy(dest->elements, src->elements, sizeof(int) * src->count_elements);
            dest->count_elements++;
            *(dest->elements + dest->count_elements - 1) = add_element;
        }else{
            dest->elements = (int*) malloc(sizeof(int) * (src->count_elements));
            memcpy(dest->elements, src->elements, sizeof(int) * src->count_elements);
        }
        aux_dest = dest;
        aux_src = src->next;
        
        while (aux_src != NULL) {
            aux_dest->next = (set*) malloc(sizeof(set));
            aux_dest = aux_dest->next;
            aux_dest->count_elements = aux_src->count_elements;
            if(add_element != 0){
                aux_dest->elements = (int*) malloc(sizeof(int) * (aux_src->count_elements + 1));
                memcpy(aux_dest->elements, aux_src->elements, sizeof(int) * aux_src->count_elements);
                aux_dest->count_elements++;
                *(aux_dest->elements + aux_dest->count_elements - 1) = add_element;
            }else{
                aux_dest->elements = (int*) malloc(sizeof(int) * (aux_src->count_elements));
                memcpy(aux_dest->elements, aux_src->elements, sizeof(int) * aux_src->count_elements);
            }
            aux_src = aux_src->next;
        }
        
        aux_dest->next = NULL;

    }
}
//Remove sets from "list" where count_elements are different from "count"
set* remove_sets(set *list, int count){
    set *previous_set, *curr_set;
    
    previous_set = curr_set = list;
    while (curr_set != NULL) {
        if(curr_set->count_elements != count){//Removing se t
            if(curr_set == list){//First set
                list = list->next;
                previous_set = curr_set = list;
            }else{
                previous_set->next = curr_set->next;
                curr_set = curr_set->next;
            }
        }else{
            previous_set = curr_set;
            curr_set = curr_set->next;
        }        
    }
    
    return list;
}

//Find all subsets from set "arr" that sums equal "sum"
set* subset( int min, int max, int limit, int sum){
    int i, j, with_aj, without_aj, aux, interval = (max - min) + 1;
    set *set_with_aj, *set_without_aj, *set_aux, *set_aux2, *resp_set;
    
    //counts solutions for a subproblem with sum equal the row and column equal the numbers of elements from set
    int count_table[sum+1][interval];
    
    //table that stores solutions
    set *sets_table[sum+1][interval];
    
    //With sum equals 0, we have 1 solution, the empty subset  
    for (j = 0; j < interval; j++){
        count_table[0][j] = 1;
        sets_table[0][j] = malloc(sizeof(set));
        sets_table[0][j]->count_elements = 0;
        sets_table[0][j]->elements = NULL;
        sets_table[0][j]->next = NULL;
    }
 
    for (i = 1; i < sum + 1; i++){
        for (j = 0; j < interval; j++){
            with_aj = without_aj = 0;
            set_without_aj = set_with_aj = NULL;
            // Count of solutions including arr[j]
            //i - arr[j] . valor da solucao menos o valor da moeda j
            //Se for maior que zero, vejo quantas solucoes para esse problema
            if(i - (min + j) >= 0){
                with_aj = count_table[i - (min + j)][j];
                set_with_aj = (set*) malloc(sizeof(set));
                if(i - (min + j) == 0){
                    set_with_aj->count_elements = 1;
                    set_with_aj->elements = (int*) malloc(sizeof(int));
                    *set_with_aj->elements = (min + j);
                }else{
                    set_aux = sets_table[i - (min + j)][j];
                    copy_sets(set_with_aj, set_aux, (min + j));
                }
            }else{
                with_aj = 0;
                set_with_aj = NULL;
            }
            
            // Count of solutions excluding S[j]
            //Se j <= 0 (nao tenho mais moeda). sem solucao 
            if(j >= 1){
                without_aj = count_table[i][j - 1];
                
                set_without_aj = (set*) malloc(sizeof(set));
                set_aux = sets_table[i][j - 1];
                if(set_aux != NULL){
                    copy_sets(set_without_aj, set_aux, 0);
                }
            }else{
                without_aj = 0;
                set_without_aj = NULL;
            }
            
            // total count
            count_table[i][j] = with_aj + without_aj;
            
            //total sets
            if(set_with_aj != NULL){
                sets_table[i][j] = set_with_aj;

                if(set_without_aj != NULL){
                    set_aux = sets_table[i][j];
                    while (set_aux->next != NULL) {
                        set_aux = set_aux->next;
                    }
                    
                    set_aux->next = set_without_aj;
                }
            }else{
                if(set_without_aj != NULL){
                    sets_table[i][j] = set_without_aj;
                }else{
                    sets_table[i][j] = (set*) malloc(sizeof(set));
                    sets_table[i][j]->count_elements = 0;
                    sets_table[i][j]->elements = NULL;
                    sets_table[i][j]->next = NULL;
                }
            }           
        }
    }
    
    #ifdef DEBUG
        printf("Count Table:\n");
        for(i = 0; i <= sum; i++){
            for(j = 0; j < interval; j++){
                printf("%4d", count_table[i][j]);
            }
            printf("\n");
        }
        
        printf("\nSets Table:\n");
        int k;
        for(i = 0; i <= sum; i++){
            printf("Soma = %d\n",i);
            for(j = 0; j < interval; j++){
                set_aux = sets_table[i][j];
                aux = 1;
                if(set_aux != NULL){
                    printf("i: %d\t j: %d\n", i, j);

                    printf("Set %d\t Elements: %d\n", aux, set_aux->count_elements);
                    for(k = 0; k < set_aux->count_elements; k++){
                        printf("%4d",*(set_aux->elements + k));
                    }
                    aux++;
                    printf("\n");
                    while(set_aux->next != NULL){
                        set_aux = set_aux->next;
                        printf("Set %d:d\t Elements: %d\n", aux, set_aux->count_elements);
                        for(k = 0; k < set_aux->count_elements; k++){
                            printf("%4d",*(set_aux->elements +k));
                        }
                        aux++;
                        printf("\n");
                    }
                    printf("\n");
                }

            }
            printf("\n\n");
        }
    #endif    
    
    //Removing sets
    resp_set = remove_sets(sets_table[sum][interval - 1], limit);
    
    #ifdef DEBUG
        printf("Conjuntos possiveis:\n");
        set_aux = resp_set;
        k = 1;
        if(set_aux != NULL){
            while (set_aux != NULL){
                printf("Set %d:\n", k);
                for (i = 0; i < set_aux->count_elements; i++) {
                   printf("%4d",*(set_aux->elements + i));

                }
                set_aux = set_aux->next;
                k++;
                printf("\n");
            }
        }else{
            printf("Nenhum conjunto encontrado.\n");
        }
    #endif
    
    return resp_set;
}