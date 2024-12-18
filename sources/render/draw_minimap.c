#include "../../includes/doomette.h"

static int minimap_shape_circle(t_game *game)
{
	if (game->mini_map.is_square)
		return (0);
	int i;
	int j;
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
	return (0);
}

static int minimap_shape_square(t_game *game)
{
	if (!(game->mini_map.is_square))
		return (0);
	int i, j;
	// draw the outline
	i = 0;
	while (i < game->mini_map.height)
	{
		j = 0;
		while (j < game->mini_map.width)
		{
			if (i == 0 || i == game->mini_map.height - 1 || j == 0 || j == game->mini_map.width - 1)
				img_pix_put(&game->mini_map.img, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
	return (0);
}

static int minimap_mode_fullscreen(t_game *game)
{
	int	i, j, k, l;
	i = 0, j = 0, k = 0, l = 0;
	if (game->mini_map.map_focus)
	{
		game->mini_map.tile = MAP_TILE;
		game->mini_map.img.mlx_img = mlx_new_image(game->mlx, MAP_W * game->mini_map.tile, MAP_H * game->mini_map.tile);
		game->mini_map.img.addr = mlx_get_data_addr(game->mini_map.img.mlx_img, &game->mini_map.img.bpp, &game->mini_map.img.line_len, &game->mini_map.img.endian);
		// todo improvement to not count everything (because not everything will be displayed)
		while (i < MAP_H)
		{
			j = 0;
			while (j < MAP_W)
			{
				k = 0;
				while (k < game->mini_map.tile)
				{
					l = 0;
					while (l < game->mini_map.tile)
					{
						if (game->map[i][j] == 1)
							img_pix_put(&game->mini_map.img, l+(j*game->mini_map.tile), k+(i*game->mini_map.tile),0xFF0000);
						else if (game->map[i][j] == 3)
							img_pix_put(&game->mini_map.img, l+(j*game->mini_map.tile), k+(i*game->mini_map.tile),0x0000FF);
						else
							img_pix_put(&game->mini_map.img, l+(j*game->mini_map.tile), k+(i*game->mini_map.tile),0x666666);
						l++;
					}
					k++;
				}
				j++;
			}
			i++;
		}
		// draw the player on the map
		int player_x = game->player.x;
		int player_y = game->player.y;
		k = -1;
		while (++k < game->player.size)
		{
			l = -1;
			while (++l < game->player.size)
				img_pix_put(&game->mini_map.img, player_x+l, player_y+k, 0x00FFFF);
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
		game->mini_map.tile = MAP_TILE;
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
					else if (game->map[(int)(start_y+i) / game->mini_map.tile][(int)(start_x+j) / game->mini_map.tile] == 3)
						img_pix_put(&game->mini_map.img, j, i, 0x0000FF); // blue
					else
						img_pix_put(&game->mini_map.img, j, i, 0x666666); // grey
				}
				else
					img_pix_put(&game->mini_map.img, j, i, 0x000000); // black
				j++;
			}
			i++;
		}
		// draw the player on the map in the center of the map
		int player_x = game->mini_map.width/2 - game->player.size/2;
		int player_y = game->mini_map.height/2 - game->player.size/2;
		k = -1;
		while (++k < game->player.size)
		{
			l = -1;
			while (++l < game->player.size)
				img_pix_put(&game->mini_map.img, player_x+l, player_y+k, 0x00FFFF);
		}
		//draw the ray representing the player's view
		draw_rays(game);
		minimap_shape_circle(game);
		minimap_shape_square(game);
	}
	return (0);
}

int	draw_minimap(t_game *game)
{
	// Clean previous image if a change is detected
	// if (!(game->update_win1))
	// 	return (0);
	// game->update_win1 = false;
	if (game->mini_map.img.mlx_img)
	{
		mlx_destroy_image(game->mlx, game->mini_map.img.mlx_img);
		game->mini_map.img.mlx_img = NULL;
	}
	if (game->game_screen.mlx_img)
	{
		mlx_destroy_image(game->mlx, game->game_screen.mlx_img);
		game->game_screen.mlx_img = NULL;
	}
	game->game_screen.mlx_img = mlx_new_image(game->mlx, WIN1_SX, WIN1_SY);
	game->game_screen.addr = mlx_get_data_addr(game->game_screen.mlx_img, &game->game_screen.bpp, &game->game_screen.line_len, &game->game_screen.endian);
	// draw the sky
	img_fill_rect(&game->game_screen, 0, 0, WIN1_SX, WIN1_SY/2, 0x000099);
	// draw the ground
	img_fill_rect(&game->game_screen, 0, WIN1_SY/2, WIN1_SX, WIN1_SY/2, 0x666666);
	// handle minimap modes
	minimap_mode_fullscreen(game);
	minimap_mode_corner(game);
	// draw the 3D view
	mlx_put_image_to_window(game->mlx, game->win1, game->game_screen.mlx_img, 0, 0);
	// draw the minimap
	if (game->mini_map.map_focus)
		mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.img.mlx_img, (WIN1_SX/2) - (MAP_W * game->mini_map.tile)/2 ,(WIN1_SY/2) - (MAP_H * game->mini_map.tile)/2);
	else
		mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.img.mlx_img, INNER_BORDER, INNER_BORDER);
	return (0);
}

