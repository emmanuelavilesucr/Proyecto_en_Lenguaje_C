#include <stdio.h>
#include <jpeglib.h>
#include <png.h>
#include <string.h>
//argv es la variable que posee los argumentos enviados por el usuario//
int main(char argc, char *argv[]){
	if (argc > 1){
		if (strcmp(argv[1], "-h") == 0) {
			printf("Pasos para manipular un archivo .png o .jpg:\n\n- Para elegir el archivo a manipular: '-i' 'nombre del archivo a manipular'.\n- Si desea agregar un nombre al nuevo archivo manipulado: '-i' 'nombre del archivo a manipular' '-o' 'nombre del archivo manipulado'.\n");
		}else
			printf("Casos no definidos");
	}else{
		printf("Error: no se agregaron argumentos.\nUse la opcion '-h' si necesita ayuda.\n");
	}
	return 0;
}
