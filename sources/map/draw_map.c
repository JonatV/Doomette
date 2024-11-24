#include "../../includes/doomette.h"

static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static	int draw_vertex(t_img *img, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1) {
		if (x0 >= 0 && x0 < WIN1_SX && y0 >= 0 && y0 < WIN1_SY)
			img_pix_put(img, x0, y0, 0xFF00FF);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
	return (0);
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
	// draw the player on the map ! player size
	int start_x = game->player.x;
	int start_y = game->player.y;
	k = -1;
	while (++k < game->player.size)
	{
		l = -1;
		while (++l < game->player.size)
			img_pix_put(&game->mini_map, start_x+l, start_y+k,0x00FFFF);
	}
	// draw player direction
	int x0 = game->player.x + game->player.size/2;
	int y0 = game->player.y + game->player.size/2;
	int x1 = game->player.x + game->player.pdx * 20;
	int y1 = game->player.y + game->player.pdy * 20;
	draw_vertex(&game->mini_map, x0, y0, x1, y1);
	mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.mlx_img, 0,0);
	return (0);
}
