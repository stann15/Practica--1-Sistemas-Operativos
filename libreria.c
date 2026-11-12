
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libreria.h"// definimos "libreria.h" para que en test.c podamos usarlo
#define SIZE 1024// guardamos el tamaño asi para saberlo antes de compilar

//muestra las N primeras entradas
int head(int N){
    char buffer[SIZE];//donde guardamos la línea, como sons seguidas y no hay que hacer nada no se necesita memoria dinámica
    int lineas = 0;//numero de líneas hasta ahora
    while (lineas < N && fgets(buffer,SIZE,stdin) != NULL){// mientras no haya <N y haya entrada seguimos, escribimos la línea y sumamos 1
        fputs(buffer,stdout);
        lineas = lineas + 1;
    }
    if (ferror(stdin)) {// si ha devuelto NULL escribimos mensaje de error
        fprintf(stderr,"Error de lectura: %s",strerror(errno));
        return -1;
    }
    return 0;// todo ha ido bien 
}

int tail (int N){
    char** lineas;
    char buffer[SIZE];
    int contador=0;
    int pos;
    int i;
    int ini;

    if (N <= 0){
        fprintf(stderr,"N debe ser mayor que 0");
        return -1;
    }
    lineas = (char**) calloc(N,sizeof(char*)); //reservamos la memoria para guardar las N lineas poniendolo a NULL
    if (lineas == NULL){
        fprintf(stderr,"No se ha podido reservar memoria: %s",strerror(errno));
        return -1;
    }
    while(fgets(buffer,SIZE,stdin) != NULL){ //leemos la entrada y guardamos las N ultimas
        pos = contador % N;
        free(lineas[pos]); //liberamos la linea antigua
        lineas[pos] = strdup(buffer); //copiamos la linea en memoria pq buffer cambia cada iteracion
        if(lineas[pos] == NULL){
            fprintf(stderr,"Error de memoria: %s",strerror(errno));
            for(i = 0;i < N;i++){
                free(lineas[i]);
            }
            free(lineas);
            return -1;
        }
        contador = contador + 1;
    }
    if(ferror(stdin)){ //comprobamos si el while acabo por un error de lectura
        fprintf(stderr,"Error de lectura: %s",strerror(errno));
        for(i = 0;i < N;i++){
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
    for(i = 0;i < N;i++){
        free(lineas[i]);
    }
    free(lineas);
    return 0;
}

int longlines(int N){
    // es un registro para guardar el texto y la longitud de cada linea
    typedef struct{
        char* texto;
        size_t longitud;
    } Tlinea;
    int contador = 0;
    int i;
    int j;
    int min;
    int max;
    char buffer[SIZE];
    Tlinea* lineas;// crea la variable, es un array de registros
    Tlinea aux;// número de carácteres de la línea 
    size_t len;
    
    if (N <= 0){
        fprintf(stderr,"N debe ser mayor que 0");
        return -1;
    }
    //convertimos el puntero de memoria dinámica que hemos asignado a el puntero Tlinea 
    lineas = (Tlinea*) calloc(N,sizeof(Tlinea));
    if (lineas == 0){//confirmamos que se ha reservado correctamente, si no se sale del programa con un return
        fprintf(stderr,"No se ha podido reservar memoria: %s",strerror(errno));
        return -1;
    }
    //recibe todas las lineas y cuenta la longitud de los carácteres 
    while (fgets(buffer,SIZE,stdin) != NULL) {
        len=strlen(buffer);//cuenta los carácteres de la línea que hemos recibido por medio de fgets 
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1]='\0';
            len=len - 1;
        }//comprobación de que 
        if (contador < N) {
            lineas[contador].texto = (char*) malloc(strlen(buffer) + 1);
            if (lineas[contador].texto == NULL){
                fprintf(stderr,"Ha habido un error de memoria");
                for(i = 0;i < contador;i++){
                    free(lineas[i].texto);
                }
                free(lineas);
                return -1;
            }
            strcpy(lineas[contador].texto,buffer);
            lineas[contador].longitud = len;
            contador = contador + 1;
        }
        else{
            min = 0;
            for(i = 1;i < N;i++){
                if(lineas[i].longitud < lineas[min].longitud){
                    min= i;
                }
            }
            if (len > lineas[min].longitud){
                free(lineas[min].texto);
                lineas[min].texto = (char *) malloc(strlen(buffer) + 1);
                if (lineas[min].texto == NULL){
                    fprintf(stderr, "Error de memoria: %s",strerror(errno));
                    for (i=0;i<contador;i++){
                        free(lineas[i].texto);
                    }
                    free(lineas);
                    return -1;
                }
                strcpy(lineas[min].texto,buffer);
                lineas[min].longitud = len;
            }
        }
    }
    if (ferror(stdin)){
        fprintf(stderr,"Error de lectura: %s",strerror(errno));
        for(i = 0;i < contador;i++){
            free(lineas[i].texto);
        }
        free(lineas);
        return -1;
    }
    for(i = 0;i < contador - 1;i++){
        max = i;
        for (j = i + 1;j < contador;j++){
            if (lineas[j].longitud > lineas[max].longitud){
                max = j;
            }
        }
        if (max != i){
            aux = lineas[i];
            lineas[i] = lineas[max];
            lineas[max] = aux;
        }
    }
    for(i = 0; i < contador; i++){
        fputs(lineas[i].texto, stdout);
            fputc('\n', stdout);
    }
    for (i = 0; i < contador; i++){
        free(lineas[i].texto);
    }
    free(lineas);
    return 0;
}  