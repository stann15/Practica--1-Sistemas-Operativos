#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
    int N = 10;
    int valor;
    if (argc < 2 || argc > 3){
        fprintf(stderr,"Uso incorrecto: ./test");
        return 1;
    }
    if(argc == 3){
        N = atoi(argv[2]);
    }
    if (N <= 0){ // tb lo comprobamos en tail y longlines en head no, habria q ver si hace falta quitarlo
        fprintf(stderr,"N debe ser mayor que 0");
        return 1;
    }
    if(strcmp(argv[1],"-head") == 0){
        valor = head(N);
    }
    else if(strcmp(argv[1],"-tail") == 0){
        valor = tail(N);
    }
    else if(strcmp(argv[1],"-longlines") == 0){
        valor = longlines(N);
    }
    else{
        fprintf(stderr,"No hay una función en la librería con ese nombre");
        return 1;
    }
    if(valor<0){
        return 1;
    }
    return 0;
}