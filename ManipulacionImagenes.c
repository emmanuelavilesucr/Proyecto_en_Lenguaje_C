#include <stdio.h>
#include <jpeglib.h>
#include <png.h>
#include <string.h>
//argv es la variable que posee los argumentos enviados por el usuario//
int main(char argc, char *argv[]){
	
	//Flags para los algoritmos//
	int flag_rotacion_png = 0;
	int flag_rotacion_jpg = 0;
	int flag_convolucion_jpg = 0;	
	int flag_convolucion_png = 0;
	
	if (argc > 1){

		if (strcmp(argv[1], "-h") == 0) {
			
			printf("Pasos para manipular un archivo .png o .jpg:\n\n- Para elegir el archivo a manipular: '-i' 'nombre del archivo a manipular'.\n- Si desea agregar un nombre al nuevo archivo manipulado: '-i' 'nombre del archivo a manipular' '-o' 'nombre del archivo manipulado'.\n");

		}if (strcmp(argv[1], "-i") == 0 && (argv[2])){
			
			if (strstr(argv[2], ".png") != NULL) {
        		printf("El string termina en '.png'.\n");
    			} else if (strstr(argv[2], ".jpg") != NULL) {
        		printf("El string termina en '.jpg'.\n");
    			} else {
        		printf("El string no termina en '.png' ni en '.jpg'.\n");
    			}

		}else {
			
			printf("no");

		}
	}else{
		
		printf("Error: no se agregaron argumentos.\nUse la opcion '-h' si necesita ayuda.\n");
		return 1;

	}
	return 0;
}
