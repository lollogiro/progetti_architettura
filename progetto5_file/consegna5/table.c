//
// Created by lollo on 25/11/2021.
//

#include <stdio.h>
#include "table.h"
#define TABLE_SIZE 23

struct symbolpair sp[TABLE_SIZE]=
        {
        {"R0",0},{"R1",1},{"R2",2},{"R3",3},{"R4",4},{"R5",5},
        {"R6",6},{"R7",7},{"R8",8},{"R9",9},{"R10",10},{"R11",11},
        {"R12",12},{"R13",13},{"R14",14},{"R15",15},{"SCREEN",16384},
        {"KBD",24576},{"SP",0},{"LCL",1},{"ARG",2},{"THIS",3},{"THAT",4}
        };

p_sym initializeSymbolTable(){
    p_sym p = NULL;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        p = queueInsert(p, sp[i]);
    }
    return p;
}

p_sym queueInsert(p_sym p, struct symbolpair s){
    if(p == NULL){
        p = malloc(sizeof(struct symbol));
        p->s_pair.s_name= malloc(sizeof(char)* (strlen(s.s_name)+2));
        strcpy(p->s_pair.s_name, s.s_name);
        p->s_pair.s_address = s.s_address;
        p->next = NULL;
    }else{
        p_sym tmp = p;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = malloc(sizeof(struct symbol));
        tmp = tmp->next;
        tmp->s_pair.s_name= malloc(sizeof(char)* (strlen(s.s_name)+2));
        strcpy(tmp->s_pair.s_name, s.s_name);
        tmp->s_pair.s_address = s.s_address;
        tmp->next = NULL;
    }
    return p;
}

//void print_symboltable(p_sym p){
//    while(p != NULL){
//        printf("%s:%d ",p->s_pair.s_name, p->s_pair.s_address);
//        p = p->next;
//    }
//}

int getSymbolAddress(p_sym p, char * label){
    while(p != NULL){
        if(strcmp(p->s_pair.s_name, label) == 0) return p->s_pair.s_address;
        p = p->next;
    }
    return -1;
}

struct instrC a0[18] =
        {
        {"0","101010"},{"1","111111"},{"-1","111010"},
        {"D","001100"},{"A","110000"},{"!D","001101"},
        {"!A","110001"},{"-D","001111"},{"-A","110011"},
        {"D+1","011111"},{"A+1","110111"},{"D-1","001110"},
        {"A-1","110010"},{"D+A","000010"},{"D-A","010011"},
        {"A-D","000111"},{"D&A","000000"},{"D|A","010101"}
        };

struct instrC a1[18] =
        {
        {"0","101010"},{"1","111111"},{"-1","111010"},
        {"D","001100"},{"M","110000"},{"!D","001101"},
        {"!M","110001"},{"-D","001111"},{"-M","110011"},
        {"D+1","011111"},{"M+1","110111"},{"D-1","001110"},
        {"M-1","110010"},{"D+M","000010"},{"D-M","010011"},
        {"M-D","000111"},{"D&M","000000"},{"D|M","010101"}
        };

struct instrC d[8] =
        {
        {"null","000"},{"M", "001"},
        {"D","010"},{"MD","011"},
        {"A","100"},{"AM","101"},
        {"AD","110"},{"AMD","111"}
        };

struct instrC jmp[8] =
        {
        {"null","000"},{"JGT","001"},
        {"JEQ","010"},{"JGE","011"},
        {"JLT","100"},{"JNE","101"},
        {"JLE","110"},{"JMP","111"}
        };

char *returnCompAddressA0(char *compToCmp){
    int i = 0;
    while(i < 18){
        if(strcmp(compToCmp, a0[i].str) == 0) return a0[i].address;
        i++;
    }
    return "err";
}

char *returnCompAddressA1(char *compToCmp){
    int i = 0;
    while(i < 18){
        if(strcmp(compToCmp, a1[i].str) == 0) return a1[i].address;
        i++;
    }
    return "err";
}

char *returnDestAddress(char *destToCmp){
    int i = 0;
    while(i < 8){
        if(strcmp(destToCmp, d[i].str) == 0) return d[i].address;
        i++;
    }
    return "err";
}

char *returnJmpAddress(char *jmpToCmp){
    int i = 0;
    while(i < 8){
        if(strcmp(jmpToCmp, jmp[i].str) == 0) return jmp[i].address;
        i++;
    }
    return "err";
}