#include "../../includes/doomette.h"

int	mouse_move_win1(int x, int y, void *p)
{
	(void)p;
	// update_win1 = true;
	printf("Mouse moving in Win1, at %dx%d.\n", x, y);
	return (0);
}

int	mouse_btn_win1(int key, void *p)
{
	(void)p;
	// update_win1 = true;
	printf("Mouse in Win1, button %d.\n", key);
	return (0);
}
