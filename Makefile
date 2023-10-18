#Variables

CC = gcc

CDFLAGS = -Wall

#Target

TARGET: rotar

#Reglas

rotar: ManipulacionImagenes.c
	$(CC) $(CDFLAGS) -o $@ ManipulacionImagenes.c
	echo "Se ha compilado el programa de manera exitosa"
