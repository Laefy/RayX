#ifndef RAYX_BASICS_H
#define RAYX_BASICS_H

typedef struct _RayX_Color {
	int r, g, b, a;
} RayX_Color;

typedef struct _RayX_Point {
	int x, y;
	double z;
	RayX_Color c;
} RayX_Point;

	/** Initialization for a point **/
	void RayX_InitializePoint(RayX_Point *point, int x, int y, double z, int r, int g, int b, int a);

	/** Interpolation for z, r, g, b and a members, depending on the position of the point **/
	void RayX_Interpolation(RayX_Point *interpolation, RayX_Point const *pt1, RayX_Point const *pt2, int x, int y);

#endif