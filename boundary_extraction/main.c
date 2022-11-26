#include "libs.h"
#include "Image_create.h"

#include "boundary_extraction.h"
// #include "median_filter.h"

void Image_load (Image *img, const char *fname)
{
    img->data =  stbi_load(fname, &img->width, &img->height, &img->channels, 0);
    if(img->data != NULL){
		img->size = img->width * img->height * img->channels;
		img->allocation = STB_ALLOCATED;
		printf("Width: %d\tHeight: %d\tChannels: %d\n", img->width, img->height, img->channels);
	}
}

// void test (Image *img)
// {
//     if(img->data != NULL){
// 		img->size = img->width * img->height * img->channels;
// 		img->allocation = STB_ALLOCATED;
// 		printf("Width: %d\tHeight: %d\tChannels: %d\n", img->width, img->height, img->channels);
// 	}
// }

// void Image_to_gray(const Image *orig, Image *gray)
// {
// 	int channels = (orig->channels == 4) ? 2: 1;
// 	Image_create(gray, orig->width, orig->height, channels, false);
// 	unsigned char *p, *pg; 
// 	// printf("\n\n%d\n\n", channels);
//     for(p = orig->data, pg = gray->data; p != (orig->data + orig->size); p += orig->channels, pg += gray->channels)
//     {
//    		*pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
//     	if(channels == 4)
//     	{
//     		*(pg + 1) = *(p + 3);
// 	    }	  
//    } 
  
// }

void Image_free(Image *img)
{
  if(img->allocation != NO_ALLOCATION && img->data != NULL)
	{
		if(img->allocation == STB_ALLOCATED)
		{
			stbi_image_free(img->data);

		}else
        {
		    free(img->data);
		}
		img->data = NULL;
		img->width = 0;
		img->height = 0;
		img->size = 0;
		img->allocation == NO_ALLOCATION;
	}	
}

void Image_save(const Image *img, const char *fname)
{
    stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
}

int main (int argc, char **argv)
{
    if ( argc != 2 )
    {
        printf("usage: ./main <input_image_file>\n");
        exit(1);
    }
    if (access(argv[1], F_OK) != 0) {
        printf("%s does not exist!\n", argv[1]);
        exit(2);
    }

    int str_ele_size;
    Image input_img, be_img;
    char output_file[20];

    Image_load(&input_img, argv[1]);

    printf("Enter output file name for boundary extracted image, structure element size: ");
    scanf("%s %d", output_file, &str_ele_size);
    boundary_extraction(&input_img, &be_img, str_ele_size);
    Image_save(&be_img, output_file);
    printf("*******Output image after boundary extraction is saved in %s*******\n\n", output_file);
 
    Image_free(&input_img);
    Image_free(&be_img);

    
    exit(0);
}