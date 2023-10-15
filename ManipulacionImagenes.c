#include <stdio.h>
#include <jpeglib.h>
#include <png.h>
#include <string.h>
//argv es la variable que posee los argumentos enviados por el usuario//
int main(int argc, char *argv[]) {
// si se necesita ayuda
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Pasos para manipular un archivo .png o .jpg:\n\n");
        printf("- Para elegir el archivo a manipular: '-i' 'nombre del archivo a manipular'.\n");
        printf("- Si desea agregar un nombre al nuevo archivo manipulado: '-i' 'nombre del archivo a manipular' '-o' 'nombre del archivo manipulado'.\n");
        return 0; // Salir después de mostrar la ayuda.
    } 
//Flags para los algoritmos
    int flag_rotacion_png = 0;
    int flag_rotacion_jpg = 0;
    int flag_convolucion_jpg = 0;
    int flag_convolucion_png = 0;

//Nombre en defecto de la imagen manipulada
    char imagen_manipulada[] = "imagen_manipulada";

    if (argc > 2) {
        if (strcmp(argv[1], "-i") == 0) {
            if (strstr(argv[2], ".png") != NULL) {
                flag_rotacion_png = 1;
                flag_convolucion_png = 1;
            } else if (strstr(argv[2], ".jpg") != NULL) {
                flag_rotacion_jpg = 1;
                flag_convolucion_jpg = 1;
            } else {
                printf("El string no termina en '.png' ni en '.jpg'.\n");
            }
            if (argc > 4 && strcmp(argv[3], "-o") == 0 && (argv[4])) {
                strcpy(imagen_manipulada, argv[4]);
            }
        } else {
            printf("Error: Argumento '-i' faltante.\n");
        }
    } else {
        printf("Error: No se proporcionaron suficientes argumentos.\nUse la opción '-h' si necesita ayuda.\n");
        return 1;
    }

    if ((flag_rotacion_png == 1) && (flag_convolucion_png == 1)){
	// Invocar funciones para png
	//rotarPNG(argv[2], imagen_manipulada);
	//convolucionPNG(argv[2], imagen_manipulada);
    	printf("Realizando manipulaciones a la imagen PNG.\nEl nombre de la nueva imagen es: %s\n", imagen_manipulada);
   
    }if ((flag_rotacion_jpg == 1) && (flag_convolucion_jpg == 1)){

	//Invocar funciones para jpg
        //rotarJPG(argv[2], imagen_manipulada);
        //convolucionJPG(argv[2], imagen_manipulada);
        printf("Realizando manipulaciones a la imagen JPG.\nEl nombre de la nueva imagen es: %s\n", imagen_manipulada);
    }
    return 0;
}
