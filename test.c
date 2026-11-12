#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc,char* argv[]){
    int N = 10;// el enunciado especifíca que en caso de no introducir valor a N, valga 10
    int i = 0;// con i recorremos lo que nos introduzca el usuario
    int valor;// variable en la cual guardamos si ha ejecutado bien la función o no

    //Como indica las funciones tienes 1 o máximo 2(la función y N)
    if (argc < 2 || argc > 3){
        fprintf(stderr,"Uso incorrecto: ./test\n");
        return 1;
    }//queremos comprobar que el string que haya introducido el usuario es un número
    if(argc == 3){
        for(; argv[2][i] != '\0'; i++){//recorremos N viendo si es un numero, si no lo es manda por pantalla un mensaje de error
            if(argv[2][i] < '0' || argv[2][i] > '9'){
                fprintf(stderr,"Lo que ha introducido no es un numero\n");
                return 1;
            }
        }
        N = atoi(argv[2]);//atoi convierte los string a entero 
    }
    //No pueden haber líneas negativas ni tampoco 0
    if (N <= 0){ 
        fprintf(stderr,"N debe ser mayor que 0\n");
        return 1;
    }
    if(strcmp(argv[1],"-head") == 0){//busca con strcmp, el string que ha intoducido el usuario con que función concuerda. Con -tail
        valor = head(N);//saber si ha ejecutado bien la función  
    }
    else if(strcmp(argv[1],"-tail") == 0){//con -tail 
        valor = tail(N);//saber si ha ejecutado bien la función  
    }
    else if(strcmp(argv[1],"-longlines") == 0){//con -longlines 
        valor = longlines(N);//saber si ha corrido bien la función  
    }
    else{
        fprintf(stderr,"No hay una función en la librería con ese nombre\n");//o con ninguna 
        return 1;
    }
    if(valor<0){// si el valor devuelto por la función es <0(ha fallado), terminar el problema con error
        return 1;
    }
    return 0;
}