#ifndef HISTOGRAM_EQUALISATION
#define HISTOGRAM_EQUALISATION

void histogram_equalisation (Image *input_img, Image *output_img, int L)
{
    int hist[M] = { 0 };
    float prob[M] = { 0 };
    uint8_t hist_new[M] = { 0 }; 
    float temp;

    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg; 

    for(p = input_img->data; p != (input_img->data + input_img->size); p += input_img->channels)
    {
   		hist[*p]++;
    } 
    for(p = input_img->data; p != (input_img->data + input_img->size); p += input_img->channels)
    {
   		prob[*p] = hist[*p]/(float)input_img->size;
    } 
    for(int i = 0; i < M; i++)
    {
        temp += prob[i];
        hist_new[i] = round( (L - 1) * temp );

    } 
    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		*pg = hist_new[*p];
    } 

}
#endif