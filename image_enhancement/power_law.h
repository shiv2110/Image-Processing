#ifndef POWER_LAW
#define POWER_LAW

void power_law (Image *input_img, Image *output_img, float c, float gamma)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);

    uint8_t *p, *pg; 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		*pg = round(c * pow( (*p), gamma));
   		// *pg = round(c * pow( ((*p)/(float)255), gamma));
    } 
}

#endif