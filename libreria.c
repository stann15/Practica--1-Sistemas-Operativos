
#include <stdio.h>
#include <stdlib.h>
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

    

        
       