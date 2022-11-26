#ifndef MEDIAN_FILTER
#define MEDIAN_FILTER

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
 
int median (uint8_t *p, int x, int y, int filter_size, int width)
{
    int lower = filter_size/2 * -1;
    int upper = filter_size/2;
    int temp[filter_size * filter_size];
    int tc = 0;
    int sum = 0, result;

    for (int k = lower; k <= upper; k++)
    {
        for (int l = lower; l <= upper; l++)
        {
            if ( (width * y + x + k * width + l) < 0 )
                temp[tc] = 0;
            else
                temp[tc] = *( p + (width * y + x + k * width + l) );
            tc++;
            // if ( (width * y + x + k * width + l) < 0 )
            //     sum += 0;
            // else
            //     sum += *( p + (width * y + x + k * width + l) );
        }
    }
    bubble_sort(temp, tc);
    result = temp[ tc/2 ];

    // result = sum/(filter_size*filter_size);
    return result;

}

void median_filter (Image *input_img, Image *output_img, int filter_size)
{
    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg; 
    int result;

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); 
        p += input_img->channels, pg += output_img->channels)
    {
        // limit++;
   		*pg = 0;
        // if (limit < 4)
        //     printf("%d\n\n", *p);
    } 

    p = input_img->data;
    pg = output_img->data;

    // printf("%d %d %d %d %d %d\n", *(p + input_img->width + 1), 
    // *(p + input_img->width + 2),
    // *(p + input_img->width + 3),
    // *(p + input_img->width*2 + 1),
    // *(p + input_img->width*2 + 2),
    // *(p + input_img->width*2 + 3));

    for (int i = 1; i < input_img->height - 1; i++)
    {
        for (int j = 1; j < input_img->width - 1; j++)
        {
            result = median(p, j, i, filter_size, input_img->width);
            *(pg + (output_img->width * i + j)) = result;

        }
    }

}

#endif