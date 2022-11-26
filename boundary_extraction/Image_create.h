#ifndef IMAGE_CREATE
#define IMAGE_CREATE

void Image_create(Image *img, int w, int h, int ch, bool zeroed)
{
	size_t size = w * h * ch;
	if(zeroed)
    {
		img->data = calloc(size, 1);
	}else
    {
		img->data = malloc(size);
	}
	if(img->data != NULL)
	{
		img->width = w;
		img->height = h;
		img->channels = ch;
		img->allocation = SELF_ALLOCATED;	
	}
}

#endif