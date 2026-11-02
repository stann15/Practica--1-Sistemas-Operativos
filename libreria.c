
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libreria.h"

#define SIZE 1024

int head(int N){
    char line[SIZE]; 
    int lines=0;

    while (lines < N && fgets(line,SIZE,stdin) !=0 ){
        fputs(line,stdout);
        lines=lines+1;

    }
    
    if (ferror(stdin)) {
        fprintf(stderr, "...");
        return -1;
    }

    return 0;
}



int tail (int N){
    char** lineas;
    char buffer[SIZE];
    int contador;
    int pos;
    int i;
    int ini;

    if (N<=0){
        fprintf(stderr,"N debe ser mayor que 0\n");
        return -1;
    }
    lineas=(char**) calloc(N,sizeof(char*)); //reservamos la memoria para guardar las N lineas poniendolo a NULL
    if (lineas==NULL){
        fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
        return -1;
    }
    contador=0;
    while(fgets(buffer,SIZE,stdin)!=NULL){ //leemos la entrada y guardamos las N ultimas
        pos=contador % N;
        free(lineas[pos]); //liberamos la linea antigua
        lineas[pos]=strdup(buffer); //copiamos la linea en memoria pq buffer cambia cada iteracion
        if(lineas[pos]==NULL){
            fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
            for(i=0;i<N;i++){
                free(lineas[i]);
            }
            free(lineas);
            return -1;
        }
        contador++;
    }
    if(ferror(stdin)){ //comprobamos si el while acabo por un error de lectura
        fprintf(stderr,"Error de lectura: %s\n",strerror(errno));
        for(i=0;i<N;i++){
            free(lineas[i]);
        }
        free(lineas);
        return -1;
    }
    if(contador<N){ //hay menos lineas que las pedidas
        for(i=0;i<contador;i++){
            fputs(lineas[i],stdout);
        }
    }
    else{
        ini=contador % N; //la linea mas antigua esta aqui
        for(i=0;i<N;i++){
            fputs(lineas[(ini+i) % N],stdout);
        }
    }
    for(i=0;i<N;i++){
        free(lineas[i]);
    }
    free(lineas);
    return 0;

}

        
       