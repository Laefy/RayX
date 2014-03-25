#include "RayX_axe.h"
#include "RayX_status.h"

#define RAYX_AXE_GETNEXTPOINT(x, y, dx, dy, a, b)			\
															\
						*e = *e - dy;						\
						if (*e < 0)							\
						{									\
							*e = *e + dx;					\
							*y = *y + a;					\
						}									\
															\
						*x = *x + b;						\

#define RAYX_AXE_DRAWHVLINE(var)							\
															\
	if (pt2->var - pt1->var < 0)							\
	{														\
		RayX_Point const *tmp = pt1;								\
		pt1 = pt2;											\
		pt2 = tmp;											\
	}														\
															\
	for (x = pt1->x, y = pt1->y; var <= pt2->var; var ++)	\
	{														\
		RayX_Interpolation(&point, pt1, pt2, x, y);			\
		RayX_DrawPoint(renderer, &point);					\
	}														\

	static void RayX_DrawSpecificLine(RayX_Renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2, int dx, int dy, void (*RayX_GetNextPoint)(int*, int*, int, int, int*));
	static void RayX_GetNextPointI(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointII(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointIII(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointIV(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointV(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointVI(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointVII(int *x, int *y, int dx, int dy, int *e);
	static void RayX_GetNextPointVIII(int *x, int *y, int dx, int dy, int *e);
	static int RayX_GetAxeFirstError(int dx, int dy);


void RayX_DrawLine(RayX_Renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2)
{
	int dx, dy;

	assert(pt1);
	assert(pt2);

	dx = pt2->x - pt1->x;
	dy = pt2->y - pt1->y;

	if (dx == 0)
	{
		RayX_DrawVerticalLine(renderer, pt1, pt2);
	}

	else if (dy == 0)
	{
		RayX_DrawHorizontalLine(renderer, pt1, pt2);
	}

	else if (dy > 0)
	{
		if (dx > 0)
		{
			if (dx >= dy)
			{
				printf("a\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointI);
			}

			else
			{
				printf("b\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointII);
			}
		}

		else
		{
			if (-dx <= dy)
			{
				printf("c\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointIII);
			}

			else
			{
				printf("d\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointIV);
			}
		}
	}

	else
	{
		if (dx < 0)
		{
			if (-dx >= -dy)
			{
				printf("e\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointV);
			}

			else
			{
				printf("f\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointVI);
			}
		}

		else
		{
			if (dx <= -dy)
			{
				printf("g\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointVII);
			}

			else
			{
				printf("h\n");
				RayX_DrawSpecificLine(renderer, pt1, pt2, dx, dy, RayX_GetNextPointVIII);
			}
		}
	}
}

void RayX_DrawHorizontalLine(RayX_Renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2)
{
	int x, y;
	RayX_Point point;

	assert(pt1);
	assert(pt2);

	RAYX_AXE_DRAWHVLINE(x);
}


void RayX_DrawVerticalLine(RayX_Renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2)
{
	int x, y;
	RayX_Point point;

	assert(pt1);
	assert(pt2);

	RAYX_AXE_DRAWHVLINE(y);
}

static void RayX_DrawSpecificLine(RayX_Renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2, int dx, int dy, void (*RayX_GetNextPoint)(int*, int*, int, int, int*))
{
	int x, y;
	int e = RayX_GetAxeFirstError(dx, dy);
	RayX_Point point;

	for (x = pt1->x, y = pt1->y; x != pt2->x || y != pt2->y; RayX_GetNextPoint(&x, &y, dx, dy, &e))
	{
		RayX_Interpolation(&point, pt1, pt2, x, y);
		RayX_DrawPoint(renderer, &point);
	}

	RayX_DrawPoint(renderer, pt2);
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

static int RayX_GetAxeFirstError(int dx, int dy)
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





