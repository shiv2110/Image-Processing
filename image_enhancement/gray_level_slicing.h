#ifndef GRAY_LEVEL_SLICING
#define GRAY_LEVEL_SLICING

void gray_level_slicing (Image *input_img, Image *output_img, int A, int B, int l)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);

    uint8_t *p, *pg; 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		if (*p <= B && *p >= A)
        {
            *pg = l;
        }
        else
        {
            *pg = *p;
        }
    } 
}

#endif