#include "../../includes/doomette.h"

//https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx
static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
int	fill_background(t_game *game)
{
	int i = 0;
	int j = 0;

	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			img_pix_put(&game->bg, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win1, game->bg.mlx_img, 0, 0);
	return (0);
}
