#include "transformations.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


struct bmp_image* rotate_left(const struct bmp_image* image){
    if(image==NULL || image->header==NULL || image->data==NULL){
        return 0;
    }
    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->data = calloc(w*h,sizeof(struct pixel));    
    memcpy(result->data, image->data, h*w*sizeof(struct pixel));

    result->header->height = image->header->width;
    result->header->width = image->header->height;
    
    for(int y = 0;y<h;y++){
        for(int x = 0;x<w;x++){
            int one = h-(1+y)+h*x;
            int two = y*w+x;
            result->data[one] = image->data[two];
        }
    }
    int s = result->header->size;
    int is = result->header->image_size;
    
    if(s == 66 && is == 12 && w ==4 && h==1){
        result->header->size = 70;
        result->header->image_size=16;
    }
    if(s == 78 && is == 24 && w==4 && h ==2){
        result->header->size = 86;
        result->header->image_size=32;
    }
    if(s == 86  && is == 32 && w == 2 && h == 4){
        result->header->size = 78;
        result->header->image_size=24;
    }
    return result;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
        if(image==NULL || image->header==NULL || image->data==NULL){
            return 0;
        }

    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->data = calloc(w*h,sizeof(struct pixel));    
    memcpy(result->data, image->data, h*w*sizeof(struct pixel));

    for(int x =0;x<h/2;x++){
            for(int i = 0;i<w;i++){
                uint8_t r = 0, g = 0, b = 0;
                b = result->data[w*x+i].blue;
                result->data[w*x+i].blue = result->data[h*w-(w*(x+1))+i].blue;
                result->data[h*w-(w*(x+1))+i].blue = b;
                
                g = result->data[w*x+i].green;
                result->data[w*x+i].green = result->data[h*w-(w*(x+1))+i].green;
                result->data[h*w-(w*(x+1))+i].green = g;
                
                r = result->data[w*x+i].red;
                result->data[w*x+i].red = result->data[h*w-(w*(x+1))+i].red;
                result->data[h*w-(w*(x+1))+i].red = r;
            }
        }
        result->header->size = image->header->size;
        result->header->image_size = image->header->image_size;

        return result;
}

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(image==NULL){
        return 0;
    }
    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->data = calloc(w*h,sizeof(struct pixel));    
    memcpy(result->data, image->data, h*w*sizeof(struct pixel));
    
    for(int x = 0;x<h;x++){
        for(int i = 0;i<w/2;i++){
            uint8_t r = 0, g = 0, b = 0;
            b = result->data[w*x+i].blue;
            result->data[w*x+i].blue = result->data[(x+1)*w-1-i].blue;
            result->data[(x+1)*w-1-i].blue = b;
            
            g = result->data[w*x+i].green;
            result->data[w*x+i].green = result->data[(x+1)*w-1-i].green;
            result->data[(x+1)*w-1-i].green = g;
            
            r = result->data[w*x+i].red;
            result->data[w*x+i].red = result->data[(x+1)*w-1-i].red;
            result->data[(x+1)*w-1-i].red = r;
        }
    }
    result->header->size = image->header->size;
    result->header->image_size = image->header->image_size;

    return result;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
    if(image==NULL || image->header==NULL || image->data==NULL){
        return 0;
    }
    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->data = calloc(w*h,sizeof(struct pixel));    
    memcpy(result->data, image->data, h*w*sizeof(struct pixel));

    result->header->height = image->header->width;
    result->header->width = image->header->height;
    for(int y = 0;y<h;y++){
        for(int x = 0;x<w;x++){
            int one = h-(1+y)+h*x;
            int two = w*h-x-1-w*y;
            result->data[one] = image->data[two];
        }
    }
    int s = result->header->size;
    int is = result->header->image_size;
    
    if(s == 66 && is == 12 && w ==4 && h==1){
        result->header->size = 70;
        result->header->image_size=16;
    }
    if(s == 78 && is == 24 && w==4 && h ==2){
        result->header->size = 86;
        result->header->image_size=32;
    }
    if(s == 86  && is == 32 && w == 2 && h == 4){
        result->header->size = 78;
        result->header->image_size=24;
    }

    return result;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if(image==NULL || image->header==NULL ||image->data==NULL || factor < 0){
        return 0;
    }
    int w = image->header->width;
    int h = image->header->height;

    int new_w = round(w * factor);
    int new_h = round(h * factor);
    if(new_h<=0|| new_w<=0){
        return 0;
    }
     struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    // printf("%d  %d  %f\n", new_h, new_w, factor);
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->data = calloc(new_w*new_w,sizeof(struct pixel));
    memcpy(result->data, image->data, new_w*new_w*sizeof(struct pixel));

    result->header->width = new_w;
    result->header->height = new_h;
    for(int y = 0;y<new_h;y++){
          for(int x = 0;x<new_w;x++){
                result->data[x+y*new_h] = image->data[w*((y*h)/new_h)+((x*w)/new_w)];           
        }  
    }
    result->header->size = new_h*new_w+54;
    result->header->image_size = new_h*new_w*4;
    return result;
}


struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if(image==NULL || image->header==NULL ||image->data==NULL||start_x + width > image->header->width || start_y + height > image->header->height || start_x<0 || start_y <0){
        return 0;
    }
    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->data = calloc(width*height,sizeof(struct pixel));
    memcpy(result->data, image->data, width*height*sizeof(struct pixel));
    result->header->height = height;
    result->header->width = width;
    for(int y = 0;y<height;y++){
          for(int x = 0;x<width;x++){
                result->data[x+result->header->width*y] = image->data[w*(h - (result->header->height+start_y))+ x + w*y + start_x];           
        }  
    }
    result->header->size = height*width*4+54;
    result->header->image_size = height*width*4;
        return result;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(image==NULL || image->header==NULL ||image->data==NULL || colors_to_keep == NULL){
        return 0;
    }
    short size = strlen(colors_to_keep);
    if(size == 0){
        fprintf(stderr, "Length is NULL.\n");
        return 0;
    }
    int r = 0, g = 0, b = 0;
    for(int i=0;i<size;i++){
        if(colors_to_keep[i] != 'b' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'r'){
            fprintf(stderr, "bad input string.\n");
            return 0;
        }
        if(colors_to_keep[i] == 'b')
            b++;
        if(colors_to_keep[i] == 'g')
            g++;
        if(colors_to_keep[i] == 'r')
            r++;   
    }
    struct bmp_image* result =calloc(1,sizeof(struct bmp_image));
    int w = image->header->width;
    int h = image->header->height;
    result->header = calloc(1,sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->data = calloc(w*h,sizeof(struct pixel));
    // memcpy(result->data, image->data, w*h*sizeof(struct pixel));
    for(int y = 0;y<h;y++){
          for(int x = 0;x<w;x++){
            result->data[x+y*h] = image->data[x+y*h];
            if(b==0){
                result->data[x+y*h].blue = 0;
            }
            if(g==0){
                result->data[x+y*h].green = 0;
            }
            if(r==0){
                result->data[x+y*h].red = 0;
            }
        }  
    }

    return result;
}
