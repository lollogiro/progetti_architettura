//
// Created by lollo on 23/11/2021.
//

#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "table.h"

int A_Instruction(char *a, FILE *f, p_sym p, int var_address){
    int toPrint[16];
    toPrint[0] = 0;
    char* strToPrint=malloc(sizeof(char)*17);
    if(a[1] >= 48 && a[1] <= 57){
        int n = returnAInt(a);
        decimal_binary(n, toPrint);
        for(int i=0;i<16;i++){
            strToPrint[i]=toPrint[i]+'0';
        }
        strToPrint[16]='\0';

    }else{
        char *tmp = malloc(sizeof(char)*100);
        int i = 1;
        int l = 0;
        if(strlen(a) < 4) l = strlen(a);
        else l = strlen(a)-2;
        while(i < l || a[i] == ' '){
            tmp[i-1] = a[i];
            i++;
        }
        tmp[i] = '\0';
        if(getSymbolAddress(p, tmp) == -1){
            struct symbolpair sp = {tmp, var_address};
            p = queueInsert(p, sp);
            var_address++;
        }
        decimal_binary(getSymbolAddress(p, tmp), toPrint);
        for(int i=0;i<16;i++){
            strToPrint[i]=toPrint[i]+'0';
        }
        strToPrint[16]='\0';
    }
    fprintf(f,"%s\r\n",strToPrint);
    return var_address;
}

int returnAInt(char *a){
    char *a_noat;
    a_noat = malloc(sizeof(char)*100);
    int i = 1;
    while(i != strlen(a)-2){
        a_noat[i-1] = a[i];
        i++;
    }
    return atoi(a_noat);
}

void decimal_binary(int n, int a[]){
    int i = 15;
    while(i >= 1){
        a[i] = n%2;
        n = n/2;
        i--;
    }
}

void C_Instruction(char *a, FILE *f){
    char* strToPrint=malloc(sizeof(char)*17);
    strToPrint[0] = '1';
    strToPrint[1] = '1';
    strToPrint[2] = '1';
    char *compToCmp = malloc(sizeof(char)*7);
    returnComp(a, compToCmp);
    if(checkCharPosition(compToCmp,'A') == -1 && checkCharPosition(compToCmp,'M') == -1){
        strToPrint[3] = '0';
        compToCmp = returnCompAddressA0(compToCmp);
        for(int i=4;i<=9;i++) strToPrint[i]=compToCmp[i-4];
    }else if(checkCharPosition(compToCmp,'A') != -1) {
        strToPrint[3] = '0';
        compToCmp = returnCompAddressA0(compToCmp);
        for (int i = 4; i <= 9; i++) strToPrint[i] = compToCmp[i - 4];
    }else{
        strToPrint[3] = '1';
        compToCmp = returnCompAddressA1(compToCmp);
        for (int i = 4; i <= 9; i++) strToPrint[i] = compToCmp[i - 4];
    }

    char *destToCmp = malloc(sizeof(char)*4);
    returnDest(a, destToCmp);
    destToCmp = returnDestAddress(destToCmp);
    for(int i=10;i<=12;i++) strToPrint[i]=destToCmp[i-10];

    char *jmpToCmp = malloc(sizeof(char)*4);
    returnJmp(a, jmpToCmp);
    jmpToCmp = returnJmpAddress(jmpToCmp);
    for(int i=13;i<=15;i++) strToPrint[i]=jmpToCmp[i-13];

    strToPrint[16]='\0';
    fprintf(f,"%s\r\n",strToPrint);
}

int checkCharPosition(char *a, char c){
    int i = 0;
    int l = 0;
    if(strlen(a) < 4) l = strlen(a);
    else l = strlen(a)-2;
    while(i < l && a[i] != '\0'){
        if(a[i] == c) return i;
        i++;
    }
    return -1;
}

void returnComp(char *a, char *compToCmp){
    int l = 0;
    if(strlen(a) < 4) l = strlen(a);
    else l = strlen(a)-2;
    int eq_pos = checkCharPosition(a, '=');
    int sc_pos = checkCharPosition(a, ';');
    if(eq_pos != -1){
        int i = eq_pos+1;
        while(i != sc_pos && i < l && a[i] != ' '){
            compToCmp[i-eq_pos-1] = a[i];
            i++;
        }
        compToCmp[i-eq_pos-1] = '\0';
    }else if(sc_pos != -1){
        int i = 0;
        while(i != sc_pos && i < l){
            compToCmp[i] = a[i];
            i++;
        }
        compToCmp[i] = '\0';
    }
}

void returnDest(char *a, char *destToCmp){
    int l = 0;
    if(strlen(a) < 4) l = strlen(a);
    else l = strlen(a)-2;
    int eq_pos = checkCharPosition(a, '=');
    if(eq_pos == -1) strcpy(destToCmp, "null");
    else{
        int i = 0;
        while(i != eq_pos && i < l){
            destToCmp[i] = a[i];
            i++;
        }
        destToCmp[i] = '\0';
    }
}

void returnJmp(char *a, char *jmpToCmp){
    int l = 0;
    if(strlen(a) < 6) l = strlen(a);
    else l = strlen(a)-2;
    int sc_pos = checkCharPosition(a, ';');
    if(sc_pos == -1) strcpy(jmpToCmp, "null");
    else{
        int i = sc_pos+1;
        while(i < l && a[i] != ' ' && a[i] != '\0'){
            jmpToCmp[i-sc_pos-1] = a[i];
            i++;
        }
        jmpToCmp[i-sc_pos-1] = '\0';
    }
}

void L_Instruction_Write(char *a, p_sym p, int cont){
    char *label = malloc(sizeof(char)*100);
    int b_start = checkCharPosition(a, '(');
    int b_end = checkCharPosition(a, ')');
    if(b_end != -1 && b_start < b_end){
        int i = 0;
        for (i = b_start+1; i < b_end; ++i) {
            label[i-b_start-1] = a[i];
        }
        label[i-b_start] = '\0';
        if(getSymbolAddress(p, label) == -1) {
            struct symbolpair s ={label, cont};
            p = queueInsert(p, s);
        }
    }else{
        printf("Errore nelle parentesi nella dichiarazione dell'etichetta\n");
    }
}