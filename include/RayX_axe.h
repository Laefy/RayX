#ifndef RAYX_AXE_H
#define RAYX_AXE_H

	#include "RayX_basics.h"
	#include "RayX_renderer.h"

	/** Render a line between two points **/
	void RayX_RenderLine(RayX_renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2);

	/** Render a horizontal line **/
	void RayX_RenderHorizontalLine(RayX_renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2);
	
	/** Render a vertical line **/
	void RayX_RenderVerticalLine(RayX_renderer *renderer, RayX_Point const *pt1, RayX_Point const *pt2);	

#endif