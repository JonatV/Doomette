#include "../../includes/doomette.h"

static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	draw_map(t_game *game)
{
	int	i = 0;
	int	j = 0;
	int k = 0;
	int l = 0;
	
	if (game->mini_map.mlx_img)
	{
		mlx_destroy_image(game->mlx, game->mini_map.mlx_img);
		game->mini_map.mlx_img = NULL;
	}
	game->mini_map.mlx_img = mlx_new_image(game->mlx, WIN1_SX, WIN1_SY);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.mlx_img, &game->mini_map.bpp, &game->mini_map.line_len, &game->mini_map.endian);
	
	int tile_size = MAP_TILE + game->zoom;

	// draw map squares
	while (i < MAP_H)
	{
		j = 0;
		while (j < MAP_W)
		{
			if (game->map[i][j] == 1)
			{
				k = 0;
				while (k < tile_size)
				{
					l = 0;
					while (l < tile_size)
					{
						img_pix_put(&game->mini_map,  l+(j*tile_size), k+(i*tile_size),0xFF0000);
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	// draw the player on the map
	i = game->player.y * tile_size;
	j = game->player.x * tile_size;
	k = 0;
	while (k < tile_size)
	{
		l = 0;
		while (l < tile_size)
		{
			img_pix_put(&game->mini_map,  l+j, k+i,0x00FF00);
			l++;
		}
		k++;
	}
	// draw the edge on top of the map draw 
	for (i = 0; i < MAP_H; i++)
		for (int cur = 0; cur < MAP_W * tile_size; cur++) img_pix_put(&game->mini_map, cur, i * tile_size, 0xFFFFFF);
	for (i = 0; i < MAP_W; i++)
			for (int cur = 0; cur <= MAP_H * tile_size; cur++) img_pix_put(&game->mini_map, i * tile_size, cur, 0xFFFFFF);
	
	mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.mlx_img, 0,0);
	return (0);
}
