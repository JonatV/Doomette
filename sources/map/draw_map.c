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
			k = 0;
			while (k < tile_size - 1)
			{
				l = 0;
				while (l < tile_size - 1)
				{
					if (game->map[i][j] == 1)
						img_pix_put(&game->mini_map, l+(j*tile_size), k+(i*tile_size),0xFF0000);
					else
						img_pix_put(&game->mini_map, l+(j*tile_size), k+(i*tile_size),0x202020);
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}
	// draw the player on the map
	int start_x = game->player.x * tile_size;
	int start_y = game->player.y * tile_size;
	k = -1;
	while (++k < tile_size)
	{
		l = -1;
		while (++l < tile_size)
			img_pix_put(&game->mini_map, start_x+l, start_y+k,0x00FF00);
	}	
	// draw player direction
	int x = start_x + (tile_size/2) - BORDER_W/2;
	int y = start_y + (tile_size/2) - BORDER_W/2;
	if (game->player.dir == NORTH)
		y = start_y-tile_size;
	else if (game->player.dir == SOUTH)
		y = start_y+tile_size;
	else if (game->player.dir == EAST)
		x = start_x+tile_size;
	else if (game->player.dir == WEST)
		x = start_x-tile_size;
	for(j = 0; j < BORDER_W; j++)
	{
		for (i = 0; i < tile_size; i++)
		{
			if (game->player.dir == NORTH || game->player.dir == SOUTH)
				img_pix_put(&game->mini_map, x+j, y+i, 0xFF0000);
			else
				img_pix_put(&game->mini_map, x+i, y+j, 0xFF0000);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.mlx_img, 0,0);
	return (0);
}
