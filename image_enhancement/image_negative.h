#ifndef IMAGE_NEGATIVE
#define IMAGE_NEGATIVE

void image_negatives (Image *input_img, Image *output_img, int L)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);

    uint8_t *p, *pg; 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		*pg = L - 1 - (*p);
    } 
}

#endif