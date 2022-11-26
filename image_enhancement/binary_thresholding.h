#ifndef BINARY_THRESHOLDING
#define BINARY_THRESHOLDING

void binary_thresholding (Image *input_img, Image *output_img, int L, int t)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);

    uint8_t *p, *pg; 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		if (*p < t)
        {
            *pg = 0;
        }
        else
        {
            *pg = L - 1;
        }
    } 
}


#endif