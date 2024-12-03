#include "../../includes/doomette.h"

//https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx
void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void img_fill_rect(t_img *img, int x, int y, int width, int height, int color)
{
	for (int i = 0; i < height; i++)
	{
		char *row = img->addr + ((y + i) * img->line_len + x * (img->bpp / 8));
		for (int j = 0; j < width; j++)
		{
			*(int *)(row + j * (img->bpp / 8)) = color;
		}
	}
}
