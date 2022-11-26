#ifndef BIT_PLANE_SLICING
#define BIT_PLANE_SLICING

void bit_plane_slicing (Image *input_img, Image *output_img, int L, int bit)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);

    uint8_t *p, *pg; 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
        *pg = (L - 1) * ( (uint8_t)( floor( (*p)/( pow(2, (bit - 1)) ) )) % 2 );
    } 
}

#endif