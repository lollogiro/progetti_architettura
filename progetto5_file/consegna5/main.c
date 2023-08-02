#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "table.h"


int main(int narg,char* argv[]) {
    char *input_file ;
    if(narg<2){
        printf("Passare il file come parametro a riga di comando!!");
        return -1;
    }
    printf("PRECONDITION: Il codice non supporta spazi tra istruzioni\n");
    input_file=argv[1];

    int var_address = 16;
    char *label = malloc(sizeof(char)*100);
    int cont = 0;
    p_sym p = initializeSymbolTable();
    FILE *f_label = fopen(input_file, "r");
    if(f_label == NULL){
        printf("File non trovato\n");
        return 0;
    }
    fgets(label, 100, f_label);
    while(!feof(f_label)){
        if(label[0] != '/' && label[1] != '/' && strlen(label) > 2) {
            if (label[0] == '(') {
                L_Instruction_Write(label, p, cont);
                cont--;
            }
            cont++;
        }
        fgets(label, 100, f_label);
    }
    fclose(f_label);

    char *a;
    a = malloc(sizeof(char)*100);
    FILE *f = fopen(input_file, "r");
    int c = 0;
    while(input_file[c] != '.'){
        c++;
    }
    char *input_hack = malloc(sizeof(char)*60);
    strncpy(input_hack, input_file, c);
    strcat(input_hack, ".hack");

    FILE *f_write = fopen(input_hack, "w");
    fgets(a, 100, f);
    while(!feof(f)){
        int i = 0;
        while(a[i] == ' '){
            i++;
        }
        char* tmp=malloc(sizeof(char)*(strlen(a)+1));
        strcpy(tmp,a);
        strcpy(a,tmp+i);
        if((a[0] != '/' && a[1] != '/') && strlen(a) > 2){
            switch(a[0]){
                case('@'):

                    var_address = A_Instruction(a, f_write, p, var_address);
                    break;
                default:
                    if(a[0] == 'D' || a[0] == 'M' || a[0] == 'A' || a[0] == '0' || a[0] == '1'){
                        C_Instruction(a, f_write);
                    }else if(a[0] != '('){
                        printf("Unexpected assembly instruction\n");
                    }
                    break;
            }
        }
        fgets(a, 100, f);
    }
    fclose(f);

    return 0;
}
