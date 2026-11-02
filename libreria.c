
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libreria.h"

int longlines(int N)
{
    // es un registro para guardar el texto y la longitud de cada linea
    typedef struct {
        char *texto;
        size_t longitud;
    } Tlinea;
    int count = 0;
    int i;
    int j;
    int min;
    int max;
    char buffer[SIZE];
    Tlinea *lines;// crea la variable, es un array de registros
    Tlinea aux;// número de carácteres de la línea 
    size_t len;

    if (N <= 0) {//comprobamos que N sea mas que 0, para hacer calloc
        fprintf(stderr, "N no puede ser 0 ni menor\n");
        return -1;
    }
    //convertimos el puntero de memoria dinámica que hemos asignado a el puntero Tlinea 
    lines = (Tlinea *) calloc(N, sizeof(Tlinea));
    if (lines == 0) {//confirmamos que se ha reservado correctamente, si no se sale del programa con un return
        fprintf(stderr, " No ha se podido reservar memoria\n");
        return -1;
    }
    //recibe todas las lineas y cuenta la longitud de los carácteres 
    while (fgets(buffer, SIZE, stdin) != 0) {
        len = strlen(buffer);//cuenta los carácteres de la línea que hemos recibido por medio de fgets 
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len=len-1;
        }//comprobación de que 
        if (count < N) {
            lines[count].texto = (char*) malloc(strlen(buffer) + 1);
            if (lines[count].texto == 0) {
                fprintf(stderr, "Ha habido un error de memoria\n");
                for (i = 0; i < count; i++) {
                    free(lines[i].texto);
                }
                free(lines);
                return -1;
            }
            strcpy(lines[count].texto, buffer);
            lines[count].longitud = len;
            count=count+1;
        }
        else {
            min = 0;
            for (i = 1; i < N; i++) {
                if (lines[i].longitud < lines[min].longitud) {
                    min = i;
                }
            }
            if (len > lines[min].longitud) {
                free(lines[min].texto);
                lines[min].texto = (char *) malloc(strlen(buffer) + 1);
                if (lines[min].texto == NULL) {
                    fprintf(stderr, "Error de memoria: %s\n", strerror(errno));
                    for (i = 0; i < count; i++) {
                        free(lines[i].texto);
                    }
                    free(lines);
                    return -1;
                }
                strcpy(lines[min].texto, buffer);
                lines[min].longitud = len;
            }
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Error de lectura: %s\n", strerror(errno));
        for (i = 0; i < count; i++) {
            free(lines[i].texto);
        }
        free(lines);
        return -1;
    }

    for (i = 0; i < count - 1; i++) {
        max = i;
        for (j = i + 1; j < count; j++) {
            if (lines[j].longitud > lines[max].longitud) {
                max = j;
            }
        }
        if (max != i) {
            aux = lines[i];
            lines[i] = lines[max];
            lines[max] = aux;
        }
    }

    for (i = 0; i < count; i++) {
        fputs(lines[i].texto, stdout);
            fputc('\n', stdout);
        
    }

    for (i = 0; i < count; i++) {
        free(lines[i].texto);
    }
    free(lines);
    return 0;
}
       