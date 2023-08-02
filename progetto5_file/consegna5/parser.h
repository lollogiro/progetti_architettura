//
// Created by lollo on 23/11/2021.
//

#ifndef PROGETTO5_PARSER_H
#define PROGETTO5_PARSER_H

#include <stdio.h>
#include "table.h"

int A_Instruction(char *a, FILE *f, p_sym p, int var_address);

int returnAInt(char *a);

void decimal_binary(int n, int a[]);

void C_Instruction(char *a, FILE *f);

int checkCharPosition(char *a, char c);

void returnComp(char *a, char *compToCmp);

void returnDest(char *a, char *destToCmp);

void returnJmp(char *a, char *jmpToCmp);

void L_Instruction_Write(char *a, p_sym p, int cont);

void L_Instruction_Read(char *a, FILE *f, p_sym p);

#endif //PROGETTO5_PARSER_H
