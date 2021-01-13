#pragma once

struct point_2d {
	int x;
	int y;
};

void point_2d_move(struct point_2d* pt, int dx, int dy);
void point_2d_move_to(struct point_2d* pt, int new_x, int new_y);
int  point_2d_cmp(struct point_2d* a, struct point_2d* b);
