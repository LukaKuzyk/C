#include "bmp.h"
#define konec return
#define freedom free
#include <string.h>
#include <stdlib.h>

struct bmp_image* read_bmp(FILE* stream){
    if(stream == NULL){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        konec 0;
    }
    
    if(ftell(stream) != EOF && ftell(stream) != 54 && ftell(stream)!= -1){
    fseek(stream, 0, SEEK_SET);
    }
    int type = 0;
    fread(&type, sizeof(char), 2, stream);
    if(type != 19778){
        fprintf(stderr,"Error: This is not a BMP file.\n");
        konec 0;
    }
    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    result->header = read_bmp_header(stream);
    result->data = read_data(stream, result->header);
    konec result;
}

void free_bmp_image(struct bmp_image* image){
    
    if(image){
    freedom(image->header);
    freedom(image->data);
    freedom(image);
    }
    
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
    if(stream == NULL || header == NULL){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        konec 0;
    }
    rewind(stream);
    int sizeon =sizeof(struct pixel);
    int h = header->height;
    int w = header->width;
    int off =54;
        if(ftell(stream) != EOF && ftell(stream) != off && ftell(stream)!= -1){
            fseek(stream, 54, SEEK_SET);
        }
        long y = 0;
    struct pixel * output = calloc(1, sizeon*h*w);
        while(y<h){
            int x = w;
            if(fread(&output[w*y], sizeon, x, stream)!=x){
                free(output);
                fprintf(stdout, "Error:fread != Width\n");
                konec 0;
            }else{
            if(y % 1==0 && w%4 !=0){
                fseek(stream,w % 4, SEEK_CUR);
            }
            y++;
           }
        }

    konec output;
}

struct bmp_header* read_bmp_header(FILE* stream){
    //check null
    if(stream == NULL || stream == stdin){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        return 0;
    }
    rewind(stream);
    // check TYPE
    struct bmp_header* result = calloc(1, sizeof(struct bmp_header));
    int type = 0;
    fseek (stream , 0, SEEK_SET);
    fread(&type, sizeof(char), 2, stream);
    result->type = type;
    rewind(stream);
    
    //find SIZE
    int size = 0;
    fseek (stream , 2, SEEK_SET);
    fread(&size, sizeof(char), 4, stream);
    result->size=size;
    rewind(stream);
    
    // find Offset
    int offset = 0;
    fseek(stream, 10, SEEK_SET);
    fread(&offset, sizeof(char), 4, stream);
    result->offset = offset;
    rewind(stream);

    //find width
    int width = 0;
    fseek(stream, 18, SEEK_SET);
    fread(&width, sizeof(char), 4, stream);
    result->width = width;
    rewind(stream);
    
    //find height
    int height = 0;
    fseek(stream, 22, SEEK_SET);
    fread(&height, sizeof(char), 4, stream);
    result->height = height;
    rewind(stream);

    //find planes
    int planes = 0;
    fseek(stream, 26, SEEK_SET);
    fread(&planes, sizeof(char), 2, stream);
    result->planes = planes;
    rewind(stream);

    //dib size find
    int dib = 0;
    fseek(stream, 14, SEEK_SET);
    fread(&dib, sizeof(char), 4, stream);
    result->dib_size = dib;
    rewind(stream);
    
    //find bpp
    int bpp = 0;
    fseek(stream, 28, SEEK_SET);
    fread(&bpp, sizeof(char), 2, stream);
    result->bpp = bpp;
    rewind(stream);
    
    //find compression
    int compression = 0;
    fseek(stream, 30, SEEK_SET);
    fread(&compression, sizeof(char), 4, stream);
    result->compression = compression;
    rewind(stream);
    
    
    //find image size
    int image_size = 0;
    fseek(stream, 34, SEEK_SET);
    fread(&image_size, sizeof(char), 4, stream);
    result->image_size = image_size;
    rewind(stream);
    
    //find x
    int x = 0;
    fseek(stream, 38, SEEK_SET);
    fread(&x, sizeof(char), 4, stream);
    result->x_ppm = x;
    rewind(stream);
    
    //find y
    int y = 0;
    fseek(stream, 42, SEEK_SET);
    fread(&y, sizeof(char), 4, stream);
    result->y_ppm = y;
    rewind(stream);
    
    //find y
    int numc = 0;
    fseek(stream, 46, SEEK_SET);
    fread(&numc, sizeof(char), 4, stream);
    result->num_colors = numc;
    rewind(stream);
    
    //find y
    int icolor = 0;
    fseek(stream, 50, SEEK_SET);
    fread(&icolor, sizeof(char), 4, stream);
    result->important_colors = icolor;

    konec result;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
    if(stream == NULL || image == NULL){
        return 0;
    }
    fseek (stream , 0, SEEK_SET);
    fwrite(&image->header->type, sizeof(char), 2, stream);

    fseek (stream , 2, SEEK_SET);
    fwrite(&image->header->size, sizeof(char), 4, stream);
    
    fseek(stream, 10, SEEK_SET);
    fwrite(&image->header->offset, sizeof(char), 4, stream);
    
    fseek(stream, 18, SEEK_SET);
    fwrite(&image->header->width, sizeof(char), 4, stream);
    
    fseek(stream, 22, SEEK_SET);
    fwrite(&image->header->height, sizeof(char), 4, stream);
    
    fseek(stream, 26, SEEK_SET);
    fwrite(&image->header->planes, sizeof(char), 2, stream);
    
    fseek(stream, 14, SEEK_SET);
    fwrite(&image->header->dib_size, sizeof(char), 4, stream);
    
    fseek(stream, 28, SEEK_SET);
    fwrite(&image->header->bpp, sizeof(char), 2, stream);
    
    fseek(stream, 30, SEEK_SET);
    fwrite(&image->header->compression, sizeof(char), 4, stream);
    
    fseek(stream, 34, SEEK_SET);
    fwrite(&image->header->image_size, sizeof(char), 4, stream);
    
    fseek(stream, 38, SEEK_SET);
    fwrite(&image->header->x_ppm, sizeof(char), 4, stream);
    
    fseek(stream, 42, SEEK_SET);
    fwrite(&image->header->y_ppm, sizeof(char), 4, stream);
    
    fseek(stream, 46, SEEK_SET);
    fwrite(&image->header->num_colors, sizeof(char), 4, stream);
    
    fseek(stream, 50, SEEK_SET);
    fwrite(&image->header->important_colors, sizeof(char), 4, stream);
    
    fseek(stream, image->header->offset, SEEK_SET);
    fwrite(&image->data->blue, image->header->image_size, 1, stream);
    
    konec true;
}

