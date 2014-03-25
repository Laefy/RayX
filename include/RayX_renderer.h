#ifndef RAYX_RENDERER_H
#define RAYX_RENDERER_H

	#include <SDL2/SDL.h>
	#include "RayX_basics.h"

typedef struct _RayX_Renderer {
	SDL_Renderer *sdlRenderer;
	int width, height;
	double **zBuffer;
	int mode3D;
} RayX_Renderer;

	/** Create a 2D renderer (polygons handling) **/
	int RayX_Create2DRenderer(RayX_Renderer *renderer, SDL_Renderer *sdlRenderer, int width, int height);

	/** Create a 3D renderer **/
	int RayX_CreateRenderer(RayX_Renderer *renderer, SDL_Renderer *sdlRenderer, int width, int height);

	/** Free the renderer **/
	void RayX_FreeRenderer(RayX_Renderer *renderer);

	/** Draw a point on the SDL_Renderer target **/
	void RayX_DrawPoint(RayX_Renderer *renderer, RayX_Point const *point);

	/** Render **/
	void RayX_Render(RayX_Renderer *renderer);

	/** Return 1 if the renderer as been set in 3D **/
	int RayX_Is3DModeSet(RayX_Renderer const *renderer);

#endif