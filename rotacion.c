#include <stdio.h>
#include <string.h>
#include <jpeglib.h>
#include <png.h>

void rotarJPEG(const char *input, const char *output) {
    // Código para rotar imágenes JPEG 
   


}

void rotarPNG(const char *input, const char *output) {
    // Código para rotar imágenes PNG
    
    

}

int main(int argc, char *argv[]) {
 
    int flag_rotacion_png = 0;
    int flag_rotacion_jpg = 0;
    int flag_convolucion_jpg = 0;
    int flag_convolucion_png = 0;

    const char *input = "input.png";
    const char *output = "output.png";


    if ((flag_rotacion_png == 1) && (flag_convolucion_png == 1)){
        rotarPNG(input, output);

    } if ((flag_rotacion_jpg == 1) && (flag_convolucion_jpg == 1)){
        rotarJPEG(input, output);
    } else {
        fprintf(stderr, "Formato no compatible. Utilice 'jpeg' o 'png'.\n");
        return 1;
    }

    return 0;
}
