#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <png.h>
#include <string.h>

// Esta funcion esta encargada del manejo de errores del programa.

void error_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
 
// Funcion encargada del proceso de rotacion de imagenes de formato JPEG.

void rotarJPEG(const char *input, const char *output, int degrees) {
    if (degrees != 180) {
        error_exit("Angulo invalido. Este programa solo acepta una rotacion de 180 grados."); // Este mensaje se muestra en caso de ingresar un angulo diferente a 180 grados
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_compress_struct jinfo;
    struct jpeg_error_mgr jerr;

    FILE *input_image = fopen(input, "rb");
    if (!input_image) {                                          // Abrir archivo de entrada
        error_exit("Error al abrir la imagen de entrada");
    } 

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, input_image);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_components = cinfo.output_components;

    unsigned char *row = (unsigned char*)malloc(num_components *width);

    FILE *output_image = fopen(output, "wb");
    if (!output_image) {                       // Abrir archivo de salida
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(input_image);
        free(row);
        error_exit("Error al abrir las imagen de salida");
    }

    jinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&jinfo);
    jpeg_stdio_dest(&jinfo, output_image);

    // Configuracion de la estructura
    jinfo.image_width = width;
    jinfo.image_height = height;
    jinfo.input_components = num_components;
    jinfo.in_color_space = cinfo.out_color_space;
    jpeg_set_defaults(&jinfo);
    jpeg_set_quality(&jinfo, 100, TRUE);
    jpeg_start_compress(&jinfo, TRUE);

    // Algoritmo encargo de realizar la rotacion de 180 grados de la imagen.

    if (degrees == 180) {
        unsigned char *rotated_image = (unsigned char *)malloc(num_components * width * height);
        int row_size = num_components * width;
        int row_index = 0;

        while (cinfo.output_scanline < cinfo.output_height) {
            jpeg_read_scanlines(&cinfo, &row, 1);
            memcpy(rotated_image + row_index, row, row_size);
            row_index += row_size;
        }

        for (int i = 0; i < height; i++) {
            row_index = (height - i - 1) * row_size;
            row = rotated_image + row_index;
            jpeg_write_scanlines(&jinfo, &row, 1);
        }
    }

    // Finaliza el proceso de compresión de la imagen
    jpeg_finish_compress(&jinfo);
    jpeg_destroy_compress(&jinfo);
    jpeg_finish_decompress(&cinfo); 
    jpeg_destroy_decompress(&cinfo);

    // Libera la memoria utilizada
    fclose(input_image);
    fclose(output_image);
    free(row);
}

// Esta función es la encargada de rotar imagenes PNG

void rotarPNG(const char *input, const char *output) {
	/* Declarar punteros utilizados para el archivo de entrada */
	png_structp input_png_ptr; 
	png_infop input_info_ptr;
	
	/* Abrir archivo de entrada */
	FILE *input_image = fopen(input, "rb");
	if (!input_image) {
        return error_exit("Error al abrir archivos de entrada o salida");
    }

	/* Definir puntero a un png_struct para el archivo de entrada */
	input_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!input_png_ptr){
		fclose(input_image);
		return error_exit("Error al rotar la imagen.");
	}

	/* Definir puntero a un png_info para el archivo de entrada*/
	input_info_ptr = png_create_info_struct(input_png_ptr);
	if (!input_info_ptr){
		fclose(input_image);
		png_destroy_read_struct(&input_png_ptr, NULL, NULL);
		return error_exit("Error al rotar la imagen.");
	}
	
	/* Inicializacion I/O para el archivo de entrada */
	png_init_io(input_png_ptr, input_image);
	
	/* Leer informacion del archivo de entrada */
	png_read_info(input_png_ptr, input_info_ptr);
	
	/* Definicion de datos importantes acerca de la imagen */
    int ancho = png_get_image_width(input_png_ptr, input_info_ptr);
    int altura = png_get_image_height(input_png_ptr, input_info_ptr);
    int bit_depth = png_get_bit_depth(input_png_ptr, input_info_ptr);
    int tipo_color = png_get_color_type(input_png_ptr, input_info_ptr);
	
	/* libpng solo admite imagenes png con bith depth de 8 con color RGBA */
   if (bit_depth != 8 || tipo_color != PNG_COLOR_TYPE_RGBA) {
        fclose(input_image);
        png_destroy_read_struct(&input_png_ptr, &input_info_ptr, NULL);
        return error_exit("Error al rotar la imagen");
    }
	
   	/* Definir puntero para las líneas de pixeles en el png */
	png_bytep fila_ptr[altura];
    for (int y = 0; y < altura; y++) {
		/* Asignar espacio en memoria para el puntero fila_ptr */
       	fila_ptr[y] = (png_bytep) malloc(png_get_rowbytes(input_png_ptr, input_info_ptr));
    }

    for (int y = 0; y < altura; y++) {
        png_read_row(input_png_ptr, fila_ptr[y], NULL);
    }	
	
	/* Liberar el espacio en memoria utilizado por los structs de tipo
	 * png_struct y png_info para el archivo de entrada */
    png_destroy_read_struct(&input_png_ptr, &input_info_ptr, NULL);
	
	/* Declarar punteros utilizados para el archivo de salida */
	png_structp output_png_ptr;
	png_infop output_info_ptr;

	/* Abrir archivo de salida */
    FILE *output_image = fopen(output, "wb");
    if (!output_image) {
        fclose(input_image);
        return error_exit("Error al rotar la imagen.");
    }
	
	/* Definir puntero a un png_struct para el archivo de salida */
    output_png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!output_png_ptr) {
        fclose(input_image);
        fclose(output_image);
        return error_exit("Error al rotar la imagen.");
    }
	
	/* Definir puntero a un png_info para el archivo de salida */
    output_info_ptr = png_create_info_struct(output_png_ptr);
    if (!output_info_ptr) {
        fclose(input_image);
        fclose(output_image);
        png_destroy_write_struct(&output_png_ptr, NULL);
        return error_exit("Error al rotar la imagen");
    }
	
	/* Inicializacion I/O para el archivo de salida */
    png_init_io(output_png_ptr, output_image);
	/* invierte ancho y altura */
    png_set_IHDR(output_png_ptr, output_info_ptr, ancho, altura, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    
	// Algoritmo de rotacion
 	
	/* Escribir al archivo de salida */
	png_write_info(output_png_ptr, output_info_ptr);
	
	/* Iterar sobre los pixeles leidos del archivo de entrada e invertirlos 
	 * para el archivo de salida */
    for (int x = 0; x < ancho; x++) {
        for (int y = altura - 1; y >= 0; y--) {
            png_write_row(output_png_ptr, &(fila_ptr[y][x]));
        }
    }
	
	/* Detener escritura al archivo de salida */
    png_write_end(output_png_ptr, NULL);

	/* Cerrar archivo de salida */
    fclose(output_image);
	fclose(input_image);

	/* Liberar memoria almacenada en fila_ptr */
    for (int y = 0; y < altura; y++) {
        free(fila_ptr[y]);
    }
	
	/* Liberar el espacio en memoria utilizado por los structs de tipo
	 * png_struct y png_info para el archivo de salida */ 
    png_destroy_write_struct(&output_png_ptr, &output_info_ptr);	
}

// main
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida> <grados>\n", argv[0]); 		  // Muestra un mensaje de uso al usuario.
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    const char *output = argv[2];
    int degrees = atoi(argv[3]);

    //rotarJPEG(input, output, degrees); 
    rotarPNG(input, output);
    printf("La imagen fue rotada y guardada como %s\n", output);

    rotarJPEG(input, output, degrees);  // Llama a la funcion encargada de rotar el jpeg
    printf("La imagen fue rotada y guardada como %s\n", output);

    return EXIT_SUCCESS;
}


