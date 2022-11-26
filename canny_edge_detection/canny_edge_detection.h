#ifndef CANNY_EDGE_DETECTION
#define CANNY_EDGE_DETECTION


void get_gaussian_filter (int kernel_size, float gaussian[])
{
    int n = kernel_size * kernel_size;
    // float gaussian[n];
    int lower = kernel_size/2 * -1;
    int upper = kernel_size/2;
    int x, y;

    for (x = lower; x <= upper; x++)
    {
        for (y = lower; y <= upper; y++)
        {
            gaussian[ n/2 + kernel_size*x + y ] = exp( (pow(x, 2) + pow(y, 2))/(-2) ) / (2 * PI);
        }
    }

}

int gaussian_filtering (uint8_t *p, int kernel_size, float gaussian[], int y, int x, int width)
{
    float conv_sum = 0;
    int n = kernel_size * kernel_size;
    int lower = kernel_size/2 * -1;
    int upper = kernel_size/2;
    int f;
    int s, t;

    for (s = lower; s <= upper; s++)
    {
        for (t = lower; t <= upper; t++)
        {
            if ( (width * y + x - s * width - t) < 0 )
            {
                f = 0;
            }
            else
            {
                f = *( p + (width * y + x - s * width - t) );
            }
            conv_sum += gaussian[ n/2 + kernel_size*s + t ] * (float)(f) ;
        }
    }

    return (int)(conv_sum);

}

int sobel_convolve_x (uint8_t *pg, int width, int y, int x)
{
    int Kx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    // uint8_t Ky[] = [1, 2, 1, 0, 0, 0, -1, -2, -1]; 
    int conv_sum = 0;
    int kernel_size = 3;
    int n = kernel_size * kernel_size;
    int lower = -1;
    int upper = 1;
    int f;
    int s, t;

    for (s = lower; s <= upper; s++)
    {
        for (t = lower; t <= upper; t++)
        {
            if ( (width * y + x - s * width - t) < 0 )
            {
                f = 0;
            }
            else
            {
                f = *( pg + (width * y + x - s * width - t) );
            }
            conv_sum += Kx[ n/2 + kernel_size*s + t ] * f ;
        }
    }
    if ( conv_sum < 0 )
            conv_sum = 0;
    return conv_sum;

}

int sobel_convolve_y (uint8_t *pg, int width, int y, int x)
{
    // uint8_t Kx[] = [-1, 0, 1, -2, 0, 2, -1, 0, 1];
    int Ky[] = {1, 2, 1, 0, 0, 0, -1, -2, -1}; 
    int conv_sum = 0;
    int kernel_size = 3;
    int n = kernel_size * kernel_size;
    int lower = -1;
    int upper = 1;
    int f;
    int s, t;

    for (s = lower; s <= upper; s++)
    {
        for (t = lower; t <= upper; t++)
        {
            if ( (width * y + x - s * width - t) < 0 )
            {
                f = 0;
            }
            else
            {
                f = *( pg + (width * y + x - s * width - t) );
            }
            conv_sum += Ky[ n/2 + kernel_size*s + t ] * f ;
        }
    }
    if ( conv_sum < 0 )
            conv_sum = 0;

    return conv_sum;

}

void apply_sobel (uint8_t *pg, float theta[], int width, int height, int size)
{
    
    uint8_t Ix[size], Iy[size];

    // apply sobel operator in both directions
    // find Ix
    int row, col, result;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            result = sobel_convolve_x(pg, width, row, col);
            *(Ix + (width * row + col)) = result;

        }
    }

    //find Iy
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            result = sobel_convolve_y(pg, width, row, col);
            *(Iy + (width * row + col)) = result;

        }
    }


    // //find G
    int h1, h2;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            h1 = *(Ix + (width * row + col));
            h2 = *(Iy + (width * row + col));

            *(pg + (width * row + col)) = (uint8_t)(sqrt( pow(h1, 2) + pow(h2, 2) ));

        }
    }

    // int h1, h2;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            h1 = *(Ix + (width * row + col));
            h2 = *(Iy + (width * row + col));

            *(theta + (width * row + col)) = (float)(atan((h2) / (float)(h1)));

        }
    }

}


void alter_angles (float theta[], int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        theta[i] = (theta[i] * 180) / PI;
        if ( theta[i] < 0 )
        {
            theta[i] += 180;
        }
    }
}

bool isSafe (int i, int j, int width)
{
    if ( (width * i + j) < 0  )
        return false;
    return true;
}

void canny_edge_detection (Image *input_img, Image *output_img, int filter_size, int t1, int t2)
{

    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg;
    int row, col; 
    int result;
    

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); 
        p += input_img->channels, pg += output_img->channels)
    {
        *pg = 0;
    } 

    
    p = input_img->data;
    pg = output_img->data;

    // apply gaussian filtering
    float gaussian[filter_size * filter_size];
    get_gaussian_filter(filter_size, gaussian);


    for (row = 0; row < input_img->height; row++)
    {
        for (col = 0; col < input_img->width; col++)
        {
            result = gaussian_filtering(p, filter_size, gaussian, row, col, input_img->width);
            *(pg + (output_img->width * row + col)) = result;

        }
    }



    uint8_t I[input_img->size];
    int h1;
    float theta[input_img->size];

    // sobel
    apply_sobel(pg, theta, output_img->width, output_img->height, input_img->size);


    //non-maximum supression
    //alter angles
    alter_angles(theta, input_img->size);
    int q = 0, r = 0;
    float angle;
    
    for (row = 1; row < output_img->height - 1; row++)
    {
        for (col = 1; col < output_img->width - 1; col++)
        {
            q = 255;
            r = 255;

            angle = *(theta + (output_img->width * row + col));

            if ( (angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180) )
            {
                if ( isSafe(row, col+1, output_img->width) )
                {
                    q = *(pg + (output_img->width * row + (col + 1)));

                }
                if ( isSafe(row, col-1, output_img->width) )
                {
                    r = *(pg + (output_img->width * row + (col - 1)));

                }
            }

            else if ( angle >= 22.5 && angle < 67.5 )
            {
                if ( isSafe(row+1, col-1, output_img->width) )
                {
                    q = *(pg + (output_img->width * (row + 1) + (col - 1)));

                }
                if ( isSafe(row-1, col+1, output_img->width) )
                {
                    r = *(pg + (output_img->width * (row - 1) + (col + 1)));

                }
            }

            else if ( angle >= 67.5 && angle < 112.5 )
            {
                if ( isSafe(row+1, col, output_img->width) )
                {
                    q = *(pg + (output_img->width * (row + 1) + col));

                }
                if ( isSafe(row-1, col, output_img->width) )
                {
                    r = *(pg + (output_img->width * (row - 1) + col));

                }
            }

            else if ( angle >= 112.5 && angle < 157.5 )
            {
                if ( isSafe(row-1, col-1, output_img->width) )
                {
                    q = *(pg + (output_img->width * (row - 1) + (col - 1)));

                }
                if ( isSafe(row+1, col+1, output_img->width) )
                {
                    r = *(pg + (output_img->width * (row + 1) + (col + 1)));

                }
            }

            h1 = *(pg + (output_img->width * row + col));
            if ( h1 >= q && h1 >= r )
            {
                *(I + (output_img->width * row + col)) = h1;
            }
            else
            {
                *(I + (output_img->width * row + col)) = 0;
            }

        }
    }

    for (row = 0; row < output_img->height; row++)
    {
        for (col = 0; col < output_img->width; col++)
        {
            h1 = *(I + (output_img->width * row + col));

            *(pg + (output_img->width * row + col)) = h1;

        }
    }

    // double thresholding
    for(p = input_img->data; p != (input_img->data + input_img->size); 
        p += input_img->channels)
    {
        *p = 0;
    } 

    
    p = input_img->data;    

    uint8_t weak = 70, strong = 255;
    for (q = 0; q < input_img->size; q++)
    {
        if ( *(pg + q) >= t2 )
        {
            *(p + q) = strong;
        }
        else if ( (*(pg + q) <= t2) && (*(pg + q) >= t1) )
        {
            *(p + q) = weak;
        }

    }

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); 
        p += input_img->channels, pg += output_img->channels)
    {
        *pg = *p;
    } 


    // edge tracking hysteresis
    pg = output_img->data;  
    for (row = 1; row < output_img->height - 1; row++)
    {
        for (col = 1; col < output_img->width - 1; col++)
        {
            h1 = *(pg + (output_img->width * row + col));

            if ( h1 == weak )
            {
                if ( isSafe(row-1, col-1, output_img->width) ||
                     isSafe(row-1, col, output_img->width) ||
                     isSafe(row-1, col+1, output_img->width) ||
                     isSafe(row, col-1, output_img->width) ||
                     isSafe(row, col+1, output_img->width) ||
                     isSafe(row+1, col-1, output_img->width) ||
                     isSafe(row+1, col, output_img->width) ||
                     isSafe(row+1, col+1, output_img->width))

                {
                    if ( (*(pg + ((row - 1) * output_img->width + (col - 1))) == strong) ||
                         (*(pg + ((row - 1) * output_img->width + col)) == strong) ||
                         (*(pg + ((row - 1) * output_img->width + (col + 1))) == strong) ||
                         (*(pg + (row * output_img->width + (col - 1))) == strong) ||
                         (*(pg + (row * output_img->width + (col + 1))) == strong) || 
                         (*(pg + ((row + 1) * output_img->width + (col - 1))) == strong) ||
                         (*(pg + ((row + 1) * output_img->width + col)) == strong) ||
                         (*(pg + ((row + 1) * output_img->width + (col + 1))) == strong))
                    {
                        *(pg + (output_img->width * row + col)) = strong;
                    }
                    else
                    {
                        *(pg + (output_img->width * row + col)) = 0;
                    }
                }


            }
            

        }
    }

}



#endif