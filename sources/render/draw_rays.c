#include "../../includes/doomette.h"

static float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	draw_rays(t_game *game)
{
	int r,mx,my,mp,dof; float rx,ry,ra,xo,yo, disT;
	int tile_size = game->mini_map.tile;
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
		if (disV<disH) { rx=vx; ry=vy; disT=disV;}
		if (disH<disV) { rx=hx; ry=hy; disT=disH;}

		float start_x = game->player.x - game->mini_map.width/2;
		float start_y = game->player.y - game->mini_map.height/2;
		if (game->mini_map.map_focus)
			draw_vertex(&game->mini_map.img, game->player.x + game->player.size/2, game->player.y + game->player.size/2 , rx, ry);
		else
			draw_vertex(&game->mini_map.img, game->mini_map.width/2, game->mini_map.height/2, rx - start_x, ry - start_y);
		

		// draw 3D walls
		float ca = game->player.pa - ra;
		if (ca < 0) { ca += 2*PI; }
		if (ca > 2*PI) { ca -= 2*PI; }
		disT = disT * cos(ca); // fix fisheye
		float lineH = (tile_size*WIN1_SY) / disT;
		if (lineH > WIN1_SY) lineH = WIN1_SY;
		int color = 0x0000FF00;
		int x = r*(WIN1_SX/60);
		int y_top = WIN1_SY/2 - lineH/2;
		int y_bot = WIN1_SY/2 + lineH/2;

		// draw the rectangle from top to bottom
		for (int y = y_top; y < y_bot; y++)
		{
			for (int w = 0; w < 16; w++)
			{
				img_pix_put(&game->game_screen, x + w, y, color);
			}
		}

		// ra += DR; if (ra < 0) { ra += 2*PI; } if (ra > 2*PI) { ra -= 2*PI; }
		ra += DR;
		ra = fmod(ra, 2*PI);
		if (ra < 0) ra += 2*PI;
	}
	return (0);
}
