#esto lo escribimos en bash, para no tener que compilar lo mismo una y otra vez
#!/bin/bash

# compilamos libreria.c en libreria.o
# gcc compilador de c
# -Wall avisos principales de errores
# -Wextra genera más avisos extra
# -c compila un fichero objeto con nombre libreria.c
# -o nombre del fichero generado en nuestro caso libreria.o
gcc -Wall -Wextra -c libreria.c -o libreria.o
if test $? -ne 0 #comprobamos que la acción se haya llevado correctamente
then 
    echo "Error al compilar la biblioteca" >&2
    exit 1
fi
# mete la libreria pasada a objeto a la biblioteca
# ar crea bibliotecas estáticas
# -r los ficheros objeto los mete en la biblioteca que hemos creado anteriormente 
# liblibreria.a es el nombre de la biblioteca 
# libreria.o los objetos que metemos en la biblioteca 
ar -r liblibreria.a libreria.o
if test $? -ne 0 #comprobamos que la acción se haya llevado correctamente 
then 
    echo "No se ha podido crear la biblioteca estática" >&2
    exit 1
fi
# Compilamos test.c y lo enlazamos con la biblioteca liblibreria.a para crear el ejecutable test
# gcc compilador de c
# -Wall avisos principales de errores
# -Wextra genera más avisos extra
# -L buscar bibliotecas en el directorio actual
# -llibreria enlaza con liblibreria.a
# -o nombre del fichero generado en nuestro caso test
gcc -Wall -Wextra test.c -L. -llibreria -o test
if test $? -ne 0 #comprobamos que la acción se haya llevado correctamente
then 
    echo "Error al enlazar" >&2
    exit 1
fi

echo "Se ha compilado correctamente" #damos la señal de que todo ha ido correctamente 


