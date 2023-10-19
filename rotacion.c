#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <stdio.h>
#include <png.h>

// Esta función se encarga del manejo de errores del programa.

void error_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

// Esta función es la encargada de rotar imagenes JPEG.

void rotarJPEG(const char *input, const char *output, int degrees) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_compress_struct output_cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    FILE *input_image = fopen(input, "rb");
    FILE *output_image = fopen(output, "wb");

    if (!input_image || !output_image) {
        error_exit("Error al abrir archivos de entrada o salida");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    output_cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&output_cinfo);

    jpeg_stdio_src(&cinfo, input_image);             // Establece el archivo de entrada
    jpeg_stdio_dest(&output_cinfo, output_image);    // Establece el archivo de salida

    jpeg_read_header(&cinfo, TRUE);
    cinfo.dct_method = JDCT_ISLOW;
    jpeg_start_decompress(&cinfo);

    output_cinfo.image_width = cinfo.output_height;
    output_cinfo.image_height = cinfo.output_width;
    output_cinfo.input_components = cinfo.output_components;
    output_cinfo.in_color_space = cinfo.out_color_space;
    jpeg_set_defaults(&output_cinfo);
    jpeg_start_compress(&output_cinfo, TRUE);

    row_pointer[0] = (JSAMPROW)malloc(cinfo.output_width * cinfo.output_components); // Reserva una espacio en memoria para almacenar los pixeles.

    // Esta estructura es la encargada de leer y rotar las filas de píxeles.
    while (cinfo.output_scanline < cinfo.output_height) {
        int i;
        int offset = cinfo.output_scanline - 1;
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        for (i = 0; i < cinfo.output_width; i++) {
            int row = i * cinfo.output_components;
            int col = offset * cinfo.output_width * cinfo.output_components;
            jpeg_write_scanlines(&output_cinfo, &row_pointer[0], 1);
        }
    }

    jpeg_finish_compress(&output_cinfo);  // Finaliza el proceso de compresion de la imagen.

    // Libera los recursos empleados en el programa.
    jpeg_destroy_decompress(&cinfo);
    jpeg_destroy_compress(&output_cinfo);
    free(row_pointer[0]);
    fclose(input_image);
    fclose(output_image);

}

void rotarPNG(const char *input, const char *output) {
    // Código para rotar imágenes PNG


}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida> <grados>\n", argv[0]); // Muestra un mensaje de uso al usuario.
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    const char *output = argv[2];
    int degrees = atoi(argv[3]);

    rotarJPEG(input, output, degrees); // Llama a la funcion.
    printf("Imagen rotada y guardada como %s\n", output);

    return EXIT_SUCCESS;
}

