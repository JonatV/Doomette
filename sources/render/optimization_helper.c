#include "../../includes/doomette.h"

//https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx
void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
