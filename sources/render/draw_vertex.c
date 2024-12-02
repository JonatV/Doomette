#include "../../includes/doomette.h"

int	draw_vertex(t_img *img, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1) {
		if (x0 >= 0 && x0 < img->line_len / (img->bpp / 8) && y0 >= 0 && y0 < img->line_len / (img->bpp / 8))
			img_pix_put(img, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
	return (0);
}
