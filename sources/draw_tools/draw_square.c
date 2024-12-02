#include "../../includes/doomette.h"

int	draw_square(t_game *game, int side, int x, int y)
{
	int i = 0, j = 0;

	game->shape1.mlx_img = mlx_new_image(game->mlx, side, side);
	game->shape1.addr = mlx_get_data_addr(game->shape1.mlx_img, &game->shape1.bpp, &game->shape1.line_len, &game->shape1.endian);

	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			img_pix_put(&game->shape1, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win1, game->shape1.mlx_img, x, y);
	return (0);
}
