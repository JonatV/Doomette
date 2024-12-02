#include "../../includes/doomette.h"

int	rectangle(t_game *game, int w, int h, int x, int y)
{
	int i = 0, j = 0;

	game->shape1.mlx_img = mlx_new_image(game->mlx, w, h);
	game->shape1.addr = mlx_get_data_addr(game->shape1.mlx_img, &game->shape1.bpp, &game->shape1.line_len, &game->shape1.endian);
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			img_pix_put(&game->shape1, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win1, game->shape1.mlx_img, x, y);
	return (0);
}

int	fill_background(t_game *game)
{
	int i = 0;
	int j = 0;
	
	// fill background with fast display function
	game->bg.mlx_img = mlx_new_image(game->mlx, WIN1_SX, WIN1_SY);
	game->bg.addr = mlx_get_data_addr(game->bg.mlx_img, &game->bg.bpp, &game->bg.line_len, &game->bg.endian);
	
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			img_pix_put(&game->bg, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win1, game->bg.mlx_img, 0, 0);
	return (0);
}
