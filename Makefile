#Variables

CC = gcc

CDFLAGS = -Wall
LDFLAG1 = -lpng
LDFLAG2 = -ljpeg

#Target

TARGET: rotar

#Reglas

rotar: ManipulacionImagenes.c
	$(CC) $(CDFLAGS) -o $@ ManipulacionImagenes.c -I/usr/include/libjpeg -I/usr/include $(LDFLAG1) $(LDFLAG2) -lz
	@echo "Se ha compilado el programa de manera exitosa"

# Regla para limpiar (borrar) archivos generados
.PHONY: clean
clean:
	rm -rf rotar
