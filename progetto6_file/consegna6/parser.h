//
// Created by lollo on 15/01/2022.
//

#include <stdio.h>
#include <math.h>

#ifndef PROGETTO6_PARSER_H
#define PROGETTO6_PARSER_H

void bootstrap_translation(FILE *f_write);

void push_translation(char* f_input, FILE* f_write, char* filename);

char find_p_type(char* f_input);

int find_const(char* f_input);

void add_translation(FILE* f_write);

void sub_translation(FILE* f_write);

void neg_translation(FILE* f_write);

int eq_translation(FILE* f_write, int i, int n_fun);

void gt_translation(FILE* f_write, int i);

void lt_translation(FILE* f_write, int i);

void and_translation(FILE* f_write);

void or_translation(FILE* f_write);

void not_translation(FILE* f_write);

void pop_translation(char* f_input, FILE* f_write, char* filename);

void label_translation(char* f_input, FILE* f_write);

void unconditioned_jmp_translation(char* f_input, FILE* f_write);

void conditioned_jmp_translation(char* f_input, FILE* f_write);

char* take_l_name(char* f_input, int n);

int call_translation(char* f_input, FILE* f_write, int n_fun);

void function_translation(char* f_input, FILE* f_write);

char* take_f_name(char* f_input);

void return_translation(char* f_input, FILE* f_write);

#endif //PROGETTO6_PARSER_H
