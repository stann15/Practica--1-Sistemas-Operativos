#!/bin/bash 

set -e

gcc -Wall -Wextra -c libreria.c -o libreria.o

ar -rv liblibreria.a libreria.o

gcc -Wall -Wextra test.c -L. -llibreria -o test

echo "Compilacion correcta: generados liblibreria.a y test"


