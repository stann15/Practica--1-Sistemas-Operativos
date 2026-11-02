
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libreria.h"

#define SIZE 1024

int head(int N){
    char buffer[SIZE]; 
    int lines=0;

    while (lines < N && fgets(buffer,SIZE,stdin) !=0 ){
        fputs(buffer,stdout);
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
    int contador=0;
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
        contador=contador+1;
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

int longlines(int N){
    int count=0;
    int i=0;
    int j=0;
    char buffer[SIZE];
    char** lines= NULL;
    size_t* lineslength= NULL;
    size_t len;
    char* aux;
    size_t auxlen;
    int min=0;
    int max=0;

    if (N<=0){
        fprintf(stderr,"N no puede ser 0 o menos\n");
        return -1;
    }

    lines=(char**) calloc(N,sizeof(char*));
    if (lines==NULL){
        fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
        return -1;
    }
    lineslength=(size_t*) calloc(N,sizeof(size_t));
    if (lineslength==NULL){
        fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
        free(lines);
        return -1;
    }

    while(fgets(buffer,SIZE,stdin)!=NULL){
        len=strlen(buffer);

        if (count<N){ //hay hueco libre: se guarda directamente
            lines[count]=strdup(buffer);
            if (lines[count]==NULL){
                fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
                for(i=0;i<count;i++){
                    free(lines[i]);
                }
                free(lines);
                free(lineslength);
                return -1;
            }
            lineslength[count]=len;
            count++;
        }
        else{ 
            min=0;
            for(i=1;i<N;i++){
                if (lineslength[i]<lineslength[min]){
                    min=i;
                }
            }
            if (len>lineslength[min]){ 
                free(lines[min]);
                lines[min]=strdup(buffer);
                if (lines[min]==NULL){
                    fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
                    for(i=0;i<count;i++){
                        free(lines[i]);
                    }
                    free(lines);
                    free(lineslength);
                    return -1;
                }
                lineslength[min]=len;
            }
        }
    }

    if (ferror(stdin)){
        fprintf(stderr,"Error de lectura: %s\n",strerror(errno));
        for(i=0;i<count;i++){
            free(lines[i]);
        }
        free(lines);
        free(lineslength);
        return -1;
    }

    for(i=0;i<count-1;i++){
        max=i;
        for(j=i+1;j<count;j++){
            if (lineslength[j]>lineslength[max]){
                max=j;
            }
        }
        aux=lines[i];
        lines[i]=lines[max];
        lines[max]=aux;
        auxlen=lineslength[i];
        lineslength[i]=lineslength[max];
        lineslength[max]=auxlen;
    }

    for(i=0;i<count;i++){
        fputs(lines[i],stdout);
    }

    for(i=0;i<count;i++){
        free(lines[i]);
    }
    free(lines);
    free(lineslength);
    return 0;
}
       