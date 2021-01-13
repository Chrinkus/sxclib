#include "point.h"

void point_2d_move(struct point_2d* pt, int dx, int dy)
{
	pt->x += dx;
	pt->y += dy;
}

void point_2d_move_to(struct point_2d* pt, int new_x, int new_y)
{
	pt->x = new_x;
	pt->y = new_y;
}

int  point_2d_cmp(struct point_2d* a, struct point_2d* b)
{
	int cond = a->x - b->x;
	return cond == 0 ? a->y - b->y : cond;
}
