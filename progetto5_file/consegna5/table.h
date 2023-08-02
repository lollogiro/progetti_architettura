//
// Created by lollo on 25/11/2021.
//

#ifndef PROGETTO5_TABLE_H
#define PROGETTO5_TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 23

struct symbolpair{
    char* s_name;
    int s_address;
};

struct symbol{
    struct symbolpair s_pair;
    struct symbol *next;
};

typedef struct symbol *p_sym;

p_sym initializeSymbolTable();

p_sym queueInsert(p_sym, struct symbolpair s);

void print_symboltable(p_sym p);

int getSymbolAddress(p_sym p, char * label);

//istanziare poi 2 array diversi per A = 0 o A = 1, 6 bit
struct instrC{
    char *str;
    char *address;
};

char *returnCompAddressA0(char *compToCmp);

char *returnCompAddressA1(char *compToCmp);

char *returnDestAddress(char *destToCmp);

char *returnJmpAddress(char *jmpToCmp);

#endif //PROGETTO5_TABLE_H
