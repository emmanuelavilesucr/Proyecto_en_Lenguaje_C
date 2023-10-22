#Variables

CC = gcc

CDFLAGS = -Wall
LDFLAG1 = -lpng
LDFLAG2 = -ljpeg

#Target

TARGET: rotar

#Reglas

rotar: ManipulacionImagenes.c
	$(CC) $(CDFLAGS) $(LDFLAG1) $(LDFLAG2) -o $@ ManipulacionImagenes.c
	echo "Se ha compilado el programa de manera exitosa"

# Regla para limpiar (borrar) archivos generados
.PHONY: clean
clean:
	rm -rf rotar
