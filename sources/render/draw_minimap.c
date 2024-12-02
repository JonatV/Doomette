#include "../../includes/doomette.h"

static int minimap_mode_fullscreen(t_game *game)
{
	int	i, j, k, l;
	int tile_size;

	tile_size = game->mini_map.tile;
	i = 0, j = 0, k = 0, l = 0;
	if (game->mini_map.map_focus)
	{
		game->mini_map.img.mlx_img = mlx_new_image(game->mlx, MAP_W * game->mini_map.tile, MAP_H * game->mini_map.tile);
		game->mini_map.img.addr = mlx_get_data_addr(game->mini_map.img.mlx_img, &game->mini_map.img.bpp, &game->mini_map.img.line_len, &game->mini_map.img.endian);
		// todo improvement to not count everything (because not everything will be displayed)
		while (i < MAP_H)
		{
			j = 0;
			while (j < MAP_W)
			{
				k = 0;
				while (k < tile_size)
				{
					l = 0;
					while (l < tile_size)
					{
						if (game->map[i][j] == 1)
							img_pix_put(&game->mini_map.img, l+(j*tile_size), k+(i*tile_size),0xFF0000);
						else
							img_pix_put(&game->mini_map.img, l+(j*tile_size), k+(i*tile_size),0x202020);
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
		// draw the player on the map
		k = -1;
		while (++k < game->player.size)
		{
			l = -1;
			while (++l < game->player.size)
				img_pix_put(&game->mini_map.img, game->player.x+l, game->player.y+k, 0x00FFFF);
		}
		//draw the ray representing the player's view
		draw_rays(game);
	}
	return (0);
}

static int minimap_mode_corner(t_game *game)
{
	int	i, j, k, l;
	float start_x, start_y;

	if (!(game->mini_map.map_focus))
	{
		game->mini_map.img.mlx_img = mlx_new_image(game->mlx, game->mini_map.width, game->mini_map.height);
		game->mini_map.img.addr = mlx_get_data_addr(game->mini_map.img.mlx_img, &game->mini_map.img.bpp, &game->mini_map.img.line_len, &game->mini_map.img.endian);

		// draw minimap left top corner (unfocused)
		start_x = game->player.x - game->mini_map.width/2;
		start_y = game->player.y - game->mini_map.height/2;
		i = 0;
		while (i < game->mini_map.height)
		{
			j = 0;
			while (j < game->mini_map.width)
			{
				// check if we are out of the map
				if ((start_y+i >= 0 && start_y+i < MAP_H * game->mini_map.tile) && (start_x+j >= 0 && start_x+j < MAP_W * game->mini_map.tile))
				{
					if (game->map[(int)(start_y+i) / game->mini_map.tile][(int)(start_x+j) / game->mini_map.tile] == 1)
						img_pix_put(&game->mini_map.img, j, i, 0xFF0000); // red
					else
						img_pix_put(&game->mini_map.img, j, i, 0x202020); // grey
				}
				else
					img_pix_put(&game->mini_map.img, j, i, 0x000000); // black
				j++;
			}
			i++;
		}
		// draw the player on the map in the center of the map
		start_x = game->mini_map.width/2 - game->player.size/2;
		start_y = game->mini_map.height/2 - game->player.size/2;
		k = -1;
		while (++k < game->player.size)
		{
			l = -1;
			while (++l < game->player.size)
				img_pix_put(&game->mini_map.img, start_x+l, start_y+k, 0x00FFFF);
		}
		//draw the ray representing the player's view
		draw_rays(game);
		// now i will replace points on the img with black to make it look like a circle
		for(i = 0; i < game->mini_map.height; i++)
		{
			for(j = 0; j < game->mini_map.width; j++)
			{
				if (sqrt(pow(j - game->mini_map.width/2, 2) + pow(i - game->mini_map.height/2, 2)) > game->mini_map.width/2)
					img_pix_put(&game->mini_map.img, j, i, 0x000000);
			}
		}
		// add white outline on the border now that the circle is done
		for (i = 0; i < game->mini_map.height; i++)
		{
			for (j = 0; j < game->mini_map.width; j++)
			{
				if (sqrt(pow(j - game->mini_map.width/2, 2) + pow(i - game->mini_map.height/2, 2)) > game->mini_map.width/2 - 1 &&
					sqrt(pow(j - game->mini_map.width/2, 2) + pow(i - game->mini_map.height/2, 2)) < game->mini_map.width/2)
					img_pix_put(&game->mini_map.img, j, i, 0xFFFFFF);
			}
		}
	}
	return (0);
}

int	draw_minimap(t_game *game)
{
	// Clean previous image if a change is detected
	if (!(game->udpate_win1))
		return (0);
	game->udpate_win1 = false;
	mlx_clear_window(game->mlx, game->win1);
	if (game->mini_map.img.mlx_img)
	{
		mlx_destroy_image(game->mlx, game->mini_map.img.mlx_img);
		game->mini_map.img.mlx_img = NULL;
	}
	// handle minimap modes
	minimap_mode_fullscreen(game);
	minimap_mode_corner(game);
	// draw the final image in the middle of the screen
	if (game->mini_map.map_focus)
		mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.img.mlx_img, (WIN1_SX/2) - (MAP_W * game->mini_map.tile)/2 ,(WIN1_SY/2) - (MAP_H * game->mini_map.tile)/2);
	else
		mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.img.mlx_img, 10, 10);
	return (0);
}

