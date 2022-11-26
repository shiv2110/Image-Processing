#ifndef NOISE
#define NOISE


void noise (Image *input_img, Image *output_img)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg; 

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size);
        p += input_img->channels, pg += output_img->channels)
    {
   		*pg = *p;
    } 

    int n_pixels = (rand() % (input_img->size/16 - input_img->size/32 + 1)) + input_img->size/32;
    // int n_pixels = (rand() % (10000 - 5000 + 1)) + 3000;
    int x, y;


    pg = output_img->data;

    for (int i = 0; i < n_pixels; i++)
    {
        x = (rand() % (input_img->width - 1 - 0 + 1)) + 0;
        y = (rand() % (input_img->height - 1 - 0 + 1)) + 0;
        *(pg + input_img->width * y + x ) = 255;
        // pg[(x+1)*(y+1)] = 255;

    }

    n_pixels = (rand() % (input_img->size/16 - input_img->size/32 + 1)) + input_img->size/32;
    // n_pixels = (rand() % (10000 - 3000 + 1)) + 3000;


    pg = output_img->data;

    for (int i = 0; i < n_pixels; i++)
    {
        x = (rand() % (input_img->width - 1 - 0 + 1)) + 0;
        y = (rand() % (input_img->height - 1 - 0 + 1)) + 0;
        *(pg + input_img->width * y + x ) = 0;
        // pg[(x+1)*(y+1)] = 0;


    }
}

#endif