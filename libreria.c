
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libreria.h"// incluimos "libreria.h" para que en test.c podamos usarlo
#define SIZE 1024// guardamos el tamaño asi para saberlo antes de compilar

int head(int N){ //muestra las N primeras líneas
    char buffer[SIZE];//donde guardamos la línea, como escribimos nada mas leer no se necesita memoria dinámica
    int lineas = 0;//numero de líneas hasta ahora

    if (N <= 0){
        fprintf(stderr,"N debe ser mayor que 0\n");
        return -1;
    }
    while (lineas < N && fgets(buffer,SIZE,stdin) != NULL){// mientras haya menos líneas que las pedidas y haya entrada seguimos
        fputs(buffer,stdout);
        lineas = lineas + 1;
    }
    if (ferror(stdin)) {//comprobamos si el while acabo por un error de lectura
        fprintf(stderr,"Error de lectura: %s\n",strerror(errno));
        return -1;
    }
    return 0;// todo ha ido bien 
}

int tail (int N){ //muestra las N ultimas líneas
    char** lineas; //puntero que apuntará al array de N punteros
    char buffer[SIZE];
    int contador=0;
    int pos;
    int i;
    int ini;

    if (N <= 0){
        fprintf(stderr,"N debe ser mayor que 0\n");
        return -1;
    }
    lineas = (char**) calloc(N,sizeof(char*)); //reservamos la memoria para guardar las N lineas poniendolo a NULL
    if (lineas == NULL){
        fprintf(stderr,"No se ha podido reservar memoria: %s\n",strerror(errno));
        return -1;
    }
    while(fgets(buffer,SIZE,stdin) != NULL){ //leemos la entrada y guardamos las N ultimas
        pos = contador % N;
        free(lineas[pos]); //liberamos la linea antigua
        lineas[pos] = strdup(buffer); //copiamos la linea en memoria pq el buffer cambia cada iteracion
        if(lineas[pos] == NULL){
            fprintf(stderr,"Error de memoria: %s\n",strerror(errno));
            for(i = 0;i < N;i++){//liberamos toda la memoria reservada
                free(lineas[i]);
            }
            free(lineas);
            return -1;
        }
        contador = contador + 1;
    }
    if(ferror(stdin)){ //comprobamos si el while acabo por un error de lectura
        fprintf(stderr,"Error de lectura: %s\n",strerror(errno));
        for(i = 0;i < N;i++){//liberamos toda la memoria reservada
            free(lineas[i]);
        }
        free(lineas);
        return -1;
    }
    // ha acabado pq no hay mas lineas
    if(contador < N){ //hay menos lineas que las pedidas
        for(i = 0;i < contador;i++){
            fputs(lineas[i],stdout);
        }
    }
    else{
        ini = contador % N; //la linea mas antigua esta aqui
        for(i = 0;i < N;i++){
            fputs(lineas[(ini + i) % N],stdout);
        }
    }
    for(i = 0;i < N;i++){//liberamos toda la memoria reservada
        free(lineas[i]);
    }
    free(lineas);
    return 0;
}

int longlines(int N){//muestra las N líneas más largas de mayor a menor longitud
    typedef struct{ //registro para guardar el texto y la longitud de cada linea
        char* texto;
        size_t longitud;
    } Tlinea;
    int contador = 0;
    int i;
    int j;
    int min;
    int max;
    char buffer[SIZE];
    Tlinea* lineas;//puntero a un array de registros
    Tlinea aux;// registro auxiliar, necesario al ordenar para no perder valores
    size_t len;//número de carácteres de la línea
    
    if (N <= 0){
        fprintf(stderr,"N debe ser mayor que 0\n");
        return -1;
    }
    //convertimos el puntero de memoria dinámica que hemos asignado a el puntero Tlinea 
    lineas = (Tlinea*) calloc(N,sizeof(Tlinea));
    if (lineas == NULL){//confirmamos que se ha reservado correctamente, si no se sale de la función con un return
        fprintf(stderr,"No se ha podido reservar memoria: %s\n",strerror(errno));
        return -1;
    }
    //recibe todas las lineas y cuenta la longitud de los carácteres 
    while (fgets(buffer,SIZE,stdin) != NULL) {
        len=strlen(buffer);//cuenta los carácteres de la línea que hemos recibido por medio de fgets 
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1]='\0';
            len=len - 1;
        }
        if (contador < N) {//todavia queda hueco para más líneas
            lineas[contador].texto = (char*) malloc(strlen(buffer) + 1);//sumamos 1 pq strlen no cuenta "\0"
            if (lineas[contador].texto == NULL){
                fprintf(stderr, "Error de memoria: %s\n",strerror(errno));
                for(i = 0;i < contador;i++){ //liberamos toda la memoria reservada
                    free(lineas[i].texto);
                }
                free(lineas);
                return -1;
            }
            strcpy(lineas[contador].texto,buffer);// guardamos la línea leída
            lineas[contador].longitud = len;//guardamos su longitud
            contador = contador + 1;
        }
        else{//no hay hueco para mas líneas, toca sustituir la más corta
            min = 0;
            for(i = 1;i < N;i++){// buscamos la más corta
                if(lineas[i].longitud < lineas[min].longitud){
                    min= i;
                }
            }
            if (len > lineas[min].longitud){//comprobamos si la nueva es más larga que la corta
                free(lineas[min].texto); //liberamos la línea mas corta
                lineas[min].texto = (char *) malloc(strlen(buffer) + 1);
                if (lineas[min].texto == NULL){
                    fprintf(stderr, "Error de memoria: %s\n",strerror(errno));
                    for (i=0;i<contador;i++){//liberamos toda la memoria reservada
                        free(lineas[i].texto);
                    }
                    free(lineas);
                    return -1;
                }
                strcpy(lineas[min].texto,buffer);//guardamos la nueva línea
                lineas[min].longitud = len;
            }
        }
    }
    if (ferror(stdin)){ // miramos si salimos del while por un error
        fprintf(stderr,"Error de lectura: %s\n",strerror(errno));
        for(i = 0;i < contador;i++){  //liberamos toda la memoria reservada
            free(lineas[i].texto);
        }
        free(lineas);
        return -1;
    }
    // hemos salido pq no quedan líneas
    for(i = 0;i < contador - 1;i++){// ordenamos de mayor a menor longitud
        max = i;
        for (j = i + 1;j < contador;j++){
            if (lineas[j].longitud > lineas[max].longitud){
                max = j;
            }
        }
        if (max != i){ //si encuentra una más larga intercambiamos posiciones,necesitamos un registro auxiliar
            aux = lineas[i];
            lineas[i] = lineas[max];
            lineas[max] = aux;
        }
    }
    for(i = 0; i < contador; i++){ //mostramos las líneas
        fputs(lineas[i].texto, stdout);
            fputc('\n', stdout);
    }
    for (i = 0; i < contador; i++){ //liberamos toda la memoria reservada
        free(lineas[i].texto);
    }
    free(lineas);
    return 0;
}  