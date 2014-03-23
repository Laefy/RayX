#include "RayX_basics.h"


void RayX_InitializePoint(RayX_Point *point, int x, int y, double z, int r, int g, int b, int a)
{
	point->x = x;
	point->y = y;
 	point->z = z;
	point->c.r = r;
	point->c.g = g;
	point->c.b = b;
	point->c.a = a;
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

	if (dx + dy != 0)
	{
		interpolation->z = (dz * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->z;
		interpolation->c.r = (dr * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.r;
		interpolation->c.g = (dg * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.g;
		interpolation->c.b = (db * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.b;
		interpolation->c.a = (da * ( (x - pt1->x) + (y - pt1->y) )) / (dx + dy) + pt1->c.a;
	}

	else if (dx != 0)
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