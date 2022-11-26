#include "libs.h"
#include "Image_create.h"

#include "contrast_stretching.h"
#include "histogram_equalisation.h"
#include "image_negative.h"
#include "log_transformation.h"
#include "power_law.h"
#include "binary_thresholding.h"
#include "gray_level_slicing.h"
#include "bit_plane_slicing.h"


void Image_load (Image *img, const char *fname)
{
    img->data =  stbi_load(fname, &img->width, &img->height, &img->channels, 0);
    if(img->data != NULL){
		img->size = img->width * img->height * img->channels;
		img->allocation = STB_ALLOCATED;
		printf("Width: %d\tHeight: %d\tChannels: %d\n", img->width, img->height, img->channels);
	}
}

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

    int choice;
    Image input_img, output_img;
    Image_load(&input_img, argv[1]);

    while (true)
    {
        printf("1. Image Negatives\n2. Power Law\n3. Log Transformation\n4. Contrast Stretching\n5. Histogram Equalisation"
               "\n6. Binary Thresholding\n7. Gray-Level Slicing\n8. Bit-Plane Slicing\n9. Exit\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        char output_file[20];

        if (choice == 1)
        {
            int L;
            printf("Enter output file name, total number of gray values: ");
            scanf("%s %d", output_file, &L);
            image_negatives(&input_img, &output_img, L);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying image negative is saved in %s*******\n\n", output_file);
            Image_free(&output_img);

        }

        else if (choice == 2)
        {
            float c, gamma;
            printf("Enter output file name, c value and gamma value: ");
            scanf("%s %f %f", output_file, &c, &gamma);
            power_law(&input_img, &output_img, c, gamma);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying power law is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 3)
        {
            float c;
            printf("Enter output file name, c value: ");
            scanf("%s %f", output_file, &c);
            log_transform(&input_img, &output_img, c);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying log transformation is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 4)
        {
            // float c;
            int a, b;
            printf("Enter output file name, a and b : ");
            scanf("%s %d %d", output_file, &a, &b);
            contrast_stretching(&input_img, &output_img, a, b);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying constrast stretching is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 5)
        {   
            int L;
            printf("Enter output file name, total number of gray values: ");
            scanf("%s %d", output_file, &L);
            histogram_equalisation(&input_img, &output_img, L);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying histogram equalisation is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 6)
        {   
            int t, L;
            printf("Enter output file name, total no. of gray values and threshold value: ");
            scanf("%s %d %d", output_file, &L, &t);
            binary_thresholding(&input_img, &output_img, L, t);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying binary thresholding is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 7)
        {   
            int A, B, t;
            printf("Enter output file name, A, B and intensity you want to set to: ");
            scanf("%s %d %d %d", output_file, &A, &B, &t);
            gray_level_slicing(&input_img, &output_img, A, B, t);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying gray-scale slicing is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 8)
        {   
            int bit, L;
            printf("Enter output file name, total no. of gray values and the bit whose image you want: ");
            scanf("%s %d %d", output_file, &L, &bit);
            bit_plane_slicing(&input_img, &output_img, L, bit);
            Image_save(&output_img, output_file);
            printf("*******Output image after applying bit-plane slicing is saved in %s*******\n\n", output_file);
            Image_free(&output_img);
        }

        else if (choice == 9) break;

        else printf("Invalid choice entered!\n");
    } 
    
    exit(0);
}