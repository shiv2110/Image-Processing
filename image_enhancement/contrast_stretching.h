#ifndef CONTRAST_STETCHING
#define CONTRAST_STETCHING

uint8_t max_grayval (Image *img)
{
    uint8_t *x;
    uint8_t max = *(img->data);
    for (x = img->data; x != img->data + img->size; x += img->channels)
    {
        if ( *x > max )
            max = *x;
    }
    printf("max = %d\n", max);
    return max;
}

uint8_t min_grayval (Image *img)
{
    uint8_t *x;
    uint8_t min = *(img->data);
    for (x = img->data; x != img->data + img->size; x += img->channels)
    {
        if ( *x < min )
            min = *x;
    }
    printf("min = %d\n", min);
    return min;
}

void contrast_stretching (Image *input_img, Image *output_img, int a, int b)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    // uint8_t b = 255, a = 0;

    uint8_t *p, *pg, c = min_grayval(input_img), d = max_grayval(input_img); 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		*pg = round( ((*p) - c) * ( (b - a)/(float)(d - c) ) + a );
    } 

}

#endif