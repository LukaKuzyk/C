#include "transformations.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    FILE* input = fopen(argv[1], "rb");
    int index1 =0;
    struct bmp_header *file = read_bmp_header(input);
    if(file == 0)
        index1++;

    struct pixel *pixel =read_data(input, file);    
    if(pixel == 0)
        index1++;
        
    struct bmp_image *image = read_bmp(input);
    if(image == 0)
        index1++;
        
    FILE* output = fopen("output.bmp", "wb");
    index1++;
    flip_vertically(image);
    flip_horizontally(image);
    rotate_left(image);
    rotate_right(image);
    scale(image, 1);
    crop(image, 1, 1, 2, 2);
    char* g =calloc(1, sizeof(char*));
    extract(image, g);

    write_bmp(output, image);
    fclose(output);
    fclose(input);
    free_bmp_image(image);
    return 0;
}

