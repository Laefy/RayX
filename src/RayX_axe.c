#include "RayX_axe.h"

#define RAYX_AXE_GETNEXTPOINT(x, y, dx, dy, dz, a, b)	\
															\
						*e = *e - dy;						\
						if (*e < 0)							\
						{									\
							*e = *e + dx;					\
							*y = *y + a;					\
						}									\
															\
						*x = *x + b;						\


void RayX_RenderHorizontalLine(RayX_renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2)
{
	int dx, i;
	RayX_Point point;
	double iz;

	assert(pt1);
	assert(pt2);

	dx = pt2->x - pt1->x;

	if (dx < 0)
	{
		RayX_Point *tmp = pt1;
		pt1 = pt2;
		pt2 = tmp;
		dx *= -1
	}

	point.y = pt1->y;
	point.z = pt1->z;
	iz = (pt1->z - pt2->z) / dx;
	for (i = pt1->x, ; i <= pt2->x; i ++)
	{
		point.x = i;
		point.z = 


	}
}

/* dx > 0, dy > 0, dx >= dy */
static void RayX_GetNextPointI(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(x, y, dx, dy, 1, 1)
}

/* dx > 0, dy > 0, dx <= dy */
static void RayX_GetNextPointII(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(y, x, dy, dx, 1, 1)
}

/* dx < 0, dy > 0, -dx <= dy */
static void RayX_GetNextPointIII(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(y, x, dy, -dx, -1, 1)
}

/* dx < 0, dy > 0, -dx >= dy */
static void RayX_GetNextPointIV(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(x, y, -dx, dy, 1, -1)
}

/* dx < 0, dy < 0, -dx >= -dy */
static void RayX_GetNextPointV(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(x, y, -dx, -dy, -1, -1)
}

/* dx < 0, dy < 0, -dx <= -dy */
static void RayX_GetNextPointVI(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(y, x, -dy, -dx, -1, -1)
}

/* dx > 0, dy < 0, dx <= -dy */
static void RayX_GetNextPointVII(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(y, x, -dy, dx, 1, -1)
}

/* dx > 0, dy < 0, dx >= -dy */
static void RayX_GetNextPointVIII(int *x, int *y, int dx, int dy, int *e)
{	
	RAYX_AXE_GETNEXTPOINT(x, y, dx, -dy, -1, 1)
}

/* Return the first error associated with the line */
static int RayX_GetFirstAxeError(int dx, int dy)
{	
	if (dx < 0)
	{
		dx *= -1;
	}
	
	if (dy < 0)
	{
		dy *= -1;
	}
	
	if (dy < dx)
	{
		return dx / 2;
	}
	
	return dy / 2;
}






void RayX_Interpolation(RayX_Point *interpolation, RayX_Point const *pt1, RayX_Point const *pt2, int x, int y)
{
	int dx = pt2->x - pt1->x;
	int dy = pt2->y - pt1->y;
	double dz = pt2->z - pt1->z;
	int dr = pt2->c.r - pt1->c.r;			
	int db = pt2->c.g - pt1->c.g;	
	int dg = pt2->c.b - pt1->c.b;	
	int da = pt2->c.a - pt1->c.a;

	interpolation->x = x;
	interpolation->y = y;

	if (dx != dy)
	{
		interpolation->z = (dz * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->z;
		interpolation->c.r = (dr * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.r;
		interpolation->c.g = (dg * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.g;
		interpolation->c.b = (db * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.b;
		interpolation->c.a = (da * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.a;
	}

	else
	{
		if (dx != 0)
		{
			interpolation->z = (dz * ( (x - pt1->x) - (y - pt1->y) )) / (dx - dy) + pt1->z;
			interpolation->c.r = (dr * ( (x - pt1->x) - (y - pt1->y) )) / (dx - dy) + pt1->c.r;
			interpolation->c.g = (dg * ( (x - pt1->x) - (y - pt1->y) )) / (dx - dy) + pt1->c.g;
			interpolation->c.b = (db * ( (x - pt1->x) - (y - pt1->y) )) / (dx - dy) + pt1->c.a;
			interpolation->c.a = (da * ( (x - pt1->x) - (y - pt1->y) )) / (dx + dy) - pt1->c.a;
		}

		else
		{
			interpolation->z = (pt1->z + pt2->z) / 2;
			interpolation->c.r = (pt1->c.r + pt2->c.r) / 2;
			interpolation->c.g = (pt1->c.g + pt2->c.g) / 2;
			interpolation->c.b = (pt1->c.b + pt2->c.b) / 2;
			interpolation->c.a = (pt1->c.a + pt2->c.a) / 2;
		}
	}
}