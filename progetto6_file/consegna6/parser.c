//
// Created by lollo on 15/01/2022.
//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

//funziona
void bootstrap_translation(FILE *f_write){
    char *to_write = "@256\r\nD=A\r\n@SP\r\nM=D\r\n";
    fprintf(f_write,"%s",to_write);
}

//funziona
void push_translation(char *f_input, FILE *f_write, char* filename){
    char p = find_p_type(f_input);
    int n = find_const(f_input);
    switch(p){
        case 'c':
            fprintf(f_write, "@%d\r\nD=A\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",n);
        break;
        case 'l':
            fprintf(f_write, "@LCL\r\nD=M\r\n@%d\r\nA=D+A\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",n);
        break;
        case 'a':
            fprintf(f_write, "@ARG\r\nD=M\r\n@%d\r\nA=D+A\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",n);
        break;
        case 's':
            fprintf(f_write, "@%s.%d\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",filename,n);
        break;
        default:
            printf("Push error\r\n");
        break;
    }

}

//funziona
char find_p_type(char* f_input){
    int i = 4;
    bool found = false;
    while(f_input[i] != '\n' && !found){
        if(f_input[i] == 'c' || f_input[i] == 'l' || f_input[i] == 'a' || f_input[i] == 's'){
            found = true;
        }else{
            i++;
        }
    }
    if(found){
        return f_input[i];
    }else{
        return 'e';
    }
}

//funziona
int find_const(char* f_input){
    int i = 0;
    bool found = false;
    while(f_input[i] != '\n' && !found){
        if(f_input[i] >= 48 && f_input[i] <= 57){
            found = true;
        }else{
            i++;
        }
    }
    if(found){
        found = false;
        int j = i;
        int n = 0;
        int cont = 0;
        int arr[30];
        while(f_input[j] != '\n' && f_input[j] != '\r' && !found){
            if(f_input[j] < 48 || f_input[j] > 57){
                found = true;
            }else{
                arr[cont] = atoi(&f_input[j]);
                cont++;
                j++;
            }
        }
        return arr[0];
    }else{
        exit(EXIT_FAILURE);
    }
}

//funziona
void add_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=D+M\r\n@SP\r\nM=M-1\r\n@SP\r\nM=M+1\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
}

//funziona
void sub_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=M-D\r\n@SP\r\nM=M-1\r\n@SP\r\nM=M+1\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
}

//funziona
void neg_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nM=-M\r\n@SP\r\nM=M+1\r\n");
}

//funziona
int eq_translation(FILE* f_write, int i, int n_fun){
    fprintf(f_write, "@SP\r\nAM=M-1\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=M-D\r\n@%s%d\r\nD;JEQ\r\n@SP\r\nA=M\r\nM=0\r\n@%s%d\r\n0;JMP\r\n(%s%d)\r\n@SP\r\nA=M\r\nM=-1\r\n(%s%d)\r\n@SP\r\nM=M+1\r\n","TRUE",i,"END",i,"TRUE",i,"END",i);
    return n_fun+2;
}

//funziona
void gt_translation(FILE* f_write, int i){
    fprintf(f_write, "@SP\r\nAM=M-1\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=M-D\r\n@%s%d\r\nD;JGT\r\n@SP\r\nA=M\r\nM=0\r\n@%s%d\r\n0;JMP\r\n(%s%d)\r\n@SP\r\nA=M\r\nM=-1\r\n(%s%d)\r\n@SP\r\nM=M+1\r\n","TRUE",i,"END",i,"TRUE",i,"END",i);
}

//funziona
void lt_translation(FILE* f_write, int i){
    fprintf(f_write, "@SP\r\nAM=M-1\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=M-D\r\n@%s%d\r\nD;JLT\r\n@SP\r\nA=M\r\nM=0\r\n@%s%d\r\n0;JMP\r\n(%s%d)\r\n@SP\r\nA=M\r\nM=-1\r\n(%s%d)\r\n@SP\r\nM=M+1\r\n","TRUE",i,"END",i,"TRUE",i,"END",i);
}

//funziona
void and_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=D&M\r\n@SP\r\nM=M-1\r\n@SP\r\nM=M+1\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
}

//funziona
void or_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nD=M\r\n@SP\r\nM=M-1\r\n@SP\r\nA=M\r\nD=D|M\r\n@SP\r\nM=M-1\r\n@SP\r\nM=M+1\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
}

//funziona
void not_translation(FILE* f_write){
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nM=!M\r\n@SP\r\nM=M+1\r\n");
}

//funziona
void pop_translation(char* f_input, FILE* f_write, char* filename){
    char p = find_p_type(f_input);
    int n = find_const(f_input);
    switch(p){
        case 'l':
            fprintf(f_write,"@LCL\r\nD=M\r\n@%d\r\nD=D+A\r\n@R13\r\nM=D\r\n@SP\r\nAM=M-1\r\nD=M\r\n@R13\r\nA=M\r\nM=D\r\n",n);
            break;
        case 'a':
            fprintf(f_write, "@ARG\r\nD=M\r\n@%d\r\nD=D+A\r\n@R13\r\nM=D\r\n@SP\r\nAM=M-1\r\nD=M\r\n@R13\r\nA=M\r\nM=D\r\n",n);
            break;
        case 's':
            fprintf(f_write, "@%s.%d\r\nD=A\r\n@R13\r\nM=D\r\n@SP\r\nAM=M-1\r\nD=M\r\n@R13\r\nA=M\r\nM=D\r\n",filename,n);
            break;
        default:
            printf("Pop error\r\n");
            break;
    }
}

//funziona
void label_translation(char* f_input, FILE* f_write){
    char* l_name = take_l_name(f_input, 5);
    fprintf(f_write, "(%s)\r\n", l_name);
}

//funziona
void unconditioned_jmp_translation(char* f_input, FILE* f_write){
    char* l_name = take_l_name(f_input, 4);
    fprintf(f_write, "@%s\r\n0;JMP\r\n", l_name);
}

//funziona
void conditioned_jmp_translation(char* f_input, FILE* f_write){
    char* l_name = take_l_name(f_input, 7);
    fprintf(f_write, "@SP\r\nM=M-1\r\nA=M\r\nD=M\r\n@%s\r\nD;JNE\r\n", l_name);
}

//funziona
char* take_l_name(char* f_input, int n){
    char* l_name = malloc(sizeof(char)*30);
    int i=n;
    while(f_input[i] == ' '){
        i++;
    }
    int j = i;
    while(f_input[j] != ' ' && f_input[j] != '\0' && f_input[j] != '\n' && f_input[j] != '\r'){
        l_name[j-i] = f_input[j];
        j++;
    }
    return l_name;
}

//funziona
int call_translation(char* f_input, FILE* f_write, int n_fun){
    int n_arg = find_const(f_input);
    char* f_name = take_f_name(f_input);
    fprintf(f_write, "@$%d\r\nD=A\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",n_fun);
    fprintf(f_write, "@LCL\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
    fprintf(f_write, "@ARG\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
    fprintf(f_write, "@THIS\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
    fprintf(f_write, "@THAT\r\nD=M\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n");
    fprintf(f_write, "@SP\r\nD=M\r\n@%d\r\nD=D-A\r\n@ARG\r\nM=D\r\n@SP\r\nD=M\r\n@LCL\r\nM=D\r\n",n_arg+5);
    fprintf(f_write, "@%s\r\n0;JMP\r\n($%d)\r\n",f_name, n_fun);
    return n_fun+1;
}

//funziona
void function_translation(char* f_input, FILE* f_write){
    fprintf(f_write, "(%s)\r\n", take_f_name(f_input));
    int lcl = find_const(f_input);
    for(int i=0; i < lcl; ++i){
        fprintf(f_write, "@%d\r\nD=A\r\n@SP\r\nA=M\r\nM=D\r\n@SP\r\nM=M+1\r\n",i);
    }
}

//funziona
char* take_f_name(char* f_input){
    char* f_name = malloc(sizeof(char)*30);
    int i=4;
    while(f_input[i-1] != '.'){
        i++;
    }
    int j = i;
    while(f_input[j] != ' ' && f_input[j] != '\0' && f_input[j] != '\n' && f_input[j] != '\r'){
        f_name[j-i] = f_input[j];
        j++;
    }
    return f_name;
}

//funziona
void return_translation(char* f_input, FILE* f_write){
    fprintf(f_write, "@LCL\r\nD=M\r\n@R14\r\nM=D\r\n@5\r\nA=D-A\r\nD=M\r\n@R15\r\nM=D\r\n@ARG\r\nD=M\r\n");
    fprintf(f_write, "@R13\r\nM=D\r\n@SP\r\nAM=M-1\r\nD=M\r\n@R13\r\nA=M\r\nM=D\r\n@ARG\r\nD=M+1\r\n@SP\r\nM=D\r\n");
    fprintf(f_write, "@R14\r\nD=M\r\n@1\r\nA=D-A\r\nD=M\r\n@THAT\r\nM=D\r\n");
    fprintf(f_write, "@R14\r\nD=M\r\n@2\r\nA=D-A\r\nD=M\r\n@THIS\r\nM=D\r\n");
    fprintf(f_write, "@R14\r\nD=M\r\n@3\r\nA=D-A\r\nD=M\r\n@ARG\r\nM=D\r\n");
    fprintf(f_write, "@R14\r\nD=M\r\n@4\r\nA=D-A\r\nD=M\r\n@LCL\r\nM=D\r\n");
    fprintf(f_write, "@R15\r\nA=M\r\n0;JMP\r\n");
}