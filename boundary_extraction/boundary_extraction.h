#ifndef BOUNDARY_EXTRACTION
#define BOUNDARU_EXTRACTION

uint8_t erosion (uint8_t *pg, uint8_t str_ele[], int y, int x, int str_ele_size, int width, int height)
{
    int s, t;
    int n = str_ele_size * str_ele_size;
    int lower = str_ele_size/2 * -1;
    int upper = str_ele_size/2;
    uint8_t f;

    for (s = lower; s <= upper; s++)
    {
        for (t = lower; t <= upper; t++)
        {
            if ( (width * y + x + s * width + t) < 0 )
            {
                f = 0;
            }
            else
            {
                f = *( pg + (width * y + x + s * width + t) );
            }

            if ( str_ele[ n/2 + str_ele_size*s + t ] != f )
            {
                return 0;
            }
        }
    }
    return 255;
}

void boundary_extraction (Image *input_img, Image *output_img, int str_ele_size)
{

    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg, t = 128;
    int L = 256; 

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

    p = input_img->data;
    pg = output_img->data;

    int n = str_ele_size * str_ele_size;
    uint8_t str_ele[n];

    for (int i = 0; i < n; i++)
    {
        str_ele[i] = 255;
    }

    int row, col, result;
    for (row = 0; row < output_img->height; row++)
    {
        for (col = 0; col < output_img->width; col++)
        {
            result = erosion(pg, str_ele, row, col, str_ele_size, output_img->width, output_img->height);
            *(p + (output_img->width * row + col)) = result;

        }
    }

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); 
        p += input_img->channels, pg += output_img->channels)
    {
        *pg = *pg - *p;
    } 

}


#endif