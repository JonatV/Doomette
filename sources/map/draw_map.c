#include "../../includes/doomette.h"

static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static int	draw_vertex(t_img *img, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1) {
		if (x0 >= 0 && x0 < WIN1_SX && y0 >= 0 && y0 < WIN1_SY)
			img_pix_put(img, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
	return (0);
}

static float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

static int	draw_rays(t_game *game)
{
	int r,mx,my,mp,dof; float rx,ry,ra,xo,yo;
	int tile_size = game->tile;
	// ra = game->player.pa-DR*30; if (ra < 0) { ra += 2*PI; } if (ra > 2*PI) { ra -= 2*PI; }
	ra = game->player.pa - DR * 30;
	ra = fmod(ra, 2*PI);	// Normalize angle
	if (ra < 0) ra += 2*PI;
	for (r=0; r<60; r++)
	{
		// horizontal lines
		dof = 0;
		float disH = 100000, hx=game->player.x, hy=game->player.y;
		float aTan = -1/tan(ra);
		if (ra > PI) { ry = (((int)game->player.y / tile_size) * tile_size) - 0.0001; rx = (game->player.y - ry) * aTan + game->player.x; yo = -tile_size; xo = -yo * aTan; }
		if (ra < PI) { ry = (((int)game->player.y / tile_size) * tile_size) + tile_size; rx = (game->player.y - ry) * aTan + game->player.x; yo = tile_size; xo = -yo * aTan; }
		if (fabs(ra - 0) < 0.00001 || fabs(ra - PI) < 0.00001) { rx = game->player.x; ry = game->player.y; dof = 10; }
		while (dof < 10)
		{
			mx = (int)(rx) / tile_size;
			my = (int)(ry) / tile_size;
			mp = my * MAP_W + mx;
			// if (mx >= 0 && mx < MAP_W && my >= 0 && my < MAP_H && game->map[my][mx] == 1)
			if (mp>0 && mp<MAP_W*MAP_H && game->map[mp/MAP_W][mp%MAP_W] == 1)
			{ dof = 10; hx=rx; hy=ry; disH=dist(game->player.x,game->player.y,hx,hy); }
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// vertical lines
		dof = 0;
		float disV = 100000, vx=game->player.x, vy=game->player.y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3) { rx = (((int)game->player.x / tile_size) * tile_size) - 0.0001; ry = (game->player.x - rx) * nTan + game->player.y; xo = -tile_size; yo = -xo * nTan; }
		if (ra < P2 || ra > P3) { rx = (((int)game->player.x / tile_size) * tile_size) + tile_size; ry = (game->player.x - rx) * nTan + game->player.y; xo = tile_size; yo = -xo * nTan; }
		if (fabs(ra - 0) < 0.00001 || fabs(ra - PI) < 0.00001) { rx = game->player.x; ry = game->player.y; dof = 10; }
		while (dof < 10)
		{
			mx = (int)(rx) / tile_size;
			my = (int)(ry) / tile_size;
			mp = my * MAP_W + mx;
			// if (mx >= 0 && mx < MAP_W && my >= 0 && my < MAP_H && game->map[my][mx] == 1)
			if (mp>0 && mp<MAP_W*MAP_H && game->map[mp/MAP_W][mp%MAP_W] == 1)
			{ vx=rx; vy=ry; disV=dist(game->player.x,game->player.y,vx,vy); dof = 10; }
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV<disH) { rx=vx; ry=vy; }
		if (disH<disV) { rx=hx; ry=hy; }
		draw_vertex(&game->mini_map, game->player.x+game->zoom + game->player.size/2, game->player.y+game->zoom + game->player.size/2, rx, ry);
		// ra += DR; if (ra < 0) { ra += 2*PI; } if (ra > 2*PI) { ra -= 2*PI; }
		ra += DR;
		ra = fmod(ra, 2*PI);
		if (ra < 0) ra += 2*PI;
	}
	return (0);
}

// void crop_img(t_img *img, int w, int h)
// {
// 	for (int y = 0; y < 600; y++)
// 	{
// 		for (int x = 0; x < WIN1_SX; x++)
// 		{
// 			if (x >= w || y >= h)
// 			{
// 				img_pix_put(img, x, y, 0x00FFFF);
// 			}
// 		}
// 	}
// }

int	draw_map(t_game *game)
{
	int	i = 0;
	int	j = 0;
	int k = 0;
	int l = 0;
	// fill the all windows with black
	if (game->udpate_win1)
	{
		mlx_clear_window(game->mlx, game->win1);
		game->udpate_win1 = false;
		return (0);
	}
	{
		mlx_destroy_image(game->mlx, game->mini_map.mlx_img);
		game->mini_map.mlx_img = NULL;
	}
	game->mini_map.mlx_img = mlx_new_image(game->mlx, WIN1_SX, WIN1_SY);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.mlx_img, &game->mini_map.bpp, &game->mini_map.line_len, &game->mini_map.endian);
	
	int tile_size;
	tile_size = game->tile;

	// draw map's tiles
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
			img_pix_put(&game->mini_map, start_x+l, start_y+k, 0x00FFFF);
	}
	
	// // draw player direction
	// int x0 = game->player.x + game->player.size/2;
	// int y0 = game->player.y + game->player.size/2;
	// int x1 = game->player.x + game->player.pdx * 20;
	// int y1 = game->player.y + game->player.pdy * 20;
	// draw_vertex(&game->mini_map, x0, y0, x1, y1);

	//draw the ray representing the player's view
	draw_rays(game);

	// crop_img(&game->mini_map, 100, 100);
	// draw the final image
	mlx_put_image_to_window(game->mlx, game->win1, game->mini_map.mlx_img, 0,0);
	return (0);
}

