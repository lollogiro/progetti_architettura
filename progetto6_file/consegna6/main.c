#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main(int narg,char* argv[]) {
    char *input_file;
    if(narg<2){
        printf("Passare il file come parametro a riga di comando!!");
        return -1;
    }
    input_file=argv[1];

    FILE *f = fopen(input_file, "r");
    if(f == NULL){
        printf("File non trovato\n");
        return 0;
    }

    char *a;
    a = malloc(sizeof(char)*100);
    int c = 0;
    while(input_file[c] != '.'){
        c++;
    }
    char *input_vm = malloc(sizeof(char)*60);
    strncpy(input_vm, input_file, c);
    strcat(input_vm, ".asm");

    FILE *f_write = fopen(input_vm, "w");

    //bootstrap translation
    bootstrap_translation(f_write);

    fgets(a, 100, f);
    int cont = 0, n_fun = 0;
    while(!feof(f)){
        int i = 0;
        while(a[i] == ' '){
            i++;
        }
        char* tmp=malloc(sizeof(char)*(strlen(a)+1));
        strcpy(tmp,a);
        strcpy(a,tmp+i);
        if((a[0] != '/' && a[1] != '/') && strlen(a) > 2){
            if(a[0] == 'p' && a[1] == 'u'){
                //push translation
                push_translation(a, f_write, input_vm);
            }else if(a[0] == 'p' && a[1] == 'o'){
                //pop translation
                pop_translation(a, f_write, input_vm);
            }else if(a[0] == 'l' && a[1] == 'a'){
                //label translation
                label_translation(a, f_write);
            }else if(a[0] == 'g' && a[1] == 'o'){
                //unconditioned jump translation
                unconditioned_jmp_translation(a, f_write);
            }else if(a[0] == 'i' && a[1] == 'f') {
                //conditioned jump translation
                conditioned_jmp_translation(a, f_write);
            }else if(a[0] == 'c' && a[1] == 'a'){
                //call translation
                n_fun = call_translation(a, f_write, n_fun);
            }else if(a[0] == 'f' && a[1] == 'u') {
                //function translation
                function_translation(a, f_write);
            }else if(a[0] == 'r' && a[1] == 'e'){
                //return translation
                return_translation(a, f_write);
            }else if(a[0] == 'a' && a[1] == 'd'){
                //add translation
                add_translation(f_write);
            }else if(a[0] == 's' && a[1] == 'u') {
                //sub translation
                sub_translation(f_write);
            }else if(a[0] == 'n' && a[1] == 'e') {
                //neg translation
                neg_translation(f_write);
            }else if(a[0] == 'e' && a[1] == 'q') {
                //eq translation
                n_fun = eq_translation(f_write, cont, n_fun);
            }else if(a[0] == 'g' && a[1] == 't') {
                //gt translation
                gt_translation(f_write, cont);
            }else if(a[0] == 'l' && a[1] == 't') {
                //lt translation
                lt_translation(f_write, cont);
            }else if(a[0] == 'a' && a[1] == 'n') {
                //and translation
                and_translation(f_write);
            }else if(a[0] == 'o' && a[1] == 'r') {
                //or translation
                or_translation(f_write);
            }else if(a[0] == 'n' && a[1] == 'o'){
                //not translation
                not_translation(f_write);
            }else{
                fprintf(f_write, "Instruction not recognized");
            }
        }
        fgets(a, 100, f);
        cont++;
    }
    fclose(f);
    fprintf(f_write,"(END)\r\n@END\r\n0;JMP\r\n");
    fclose(f_write);
    free(a);
    return 0;
}
