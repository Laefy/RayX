#include "RayX_renderer.h"

	/** Creation of the zBuffer **/
	static int RayX_CreateZbuffer(double ***zBuffer, int width, int height);

	/** Release of the zBuffer **/
	static void RayX_FreeZbuffer(double **zBuffer);

	/** Reinitialization of the zBuffer **/
	static void RayX_ClearZbuffer(double **zBuffer);

	/** Render a 3D point **/
	static void RayX_Render3DPoint(RayX_Renderer *renderer, RayX_Point const *point);


int RayX_Create2DRenderer(RayX_Renderer *renderer, SDL_Renderer *sdlRenderer, int width, int height)
{
	renderer->sdlRenderer = sdlRenderer;
	renderer->width = width;
	renderer->height = height;
	renderer->zBuffer = NULL;
	renderer->mode3D = 0;

	return RAYX_OK;
}

int RayX_CreateRenderer(RayX_Renderer *renderer, SDL_Renderer *sdlRenderer, int width, int height)
{
	RayX_Status status;

	status = RayX_CreateZbuffer(&renderer->zBuffer, width, height);

	if (status == RAYX_OK)
	{
		renderer->sdlRenderer = sdlRenderer;
		renderer->width = width;
		renderer->height = height;
		renderer->mode3D = 1;

		RayX_ClearZbuffer(renderer->zBuffer, width, height);

		return RAYX_OK;
	}

	return status;
}

void RayX_FreeRenderer(RayX_Renderer *renderer)
{
	if (renderer->mode3D)
	{
		RayX_FreeZbuffer(renderer->zBuffer);
	}
}

void RayX_RenderPoint(RayX_Renderer *renderer, RayX_Point const *point)
{
	if (renderer->mode3D)
	{
		RayX_Render3DPoint(renderer, point);
	}
	
	else
	{
		SDL_SetRenderDrawColor(renderer->sdlRenderer, point->c.r, point->c.g, point->c.b, point->c.a);
		SDL_RenderDrawPoint(renderer->sdlRenderer, point->x, point->y);
	}
}

int RayX_Is3DModeSet(RayX_Renderer const *renderer)
{
	return renderer->mode3D;
}

static int RayX_CreateZbuffer(double ***zBuffer, int width, int height)
{
	RayX_Status status;
	double *buffer;

	buffer = (double*)malloc(sizeof(double) * height * width);

	if (buffer)
	{
		*zBuffer = (double**)malloc(sizeof(double*) * height);

		if (*zBuffer)
		{
			int i;

			for (i = 0; i < height; i ++)
			{
				(*zBuffer)[i] = &buffer[i * width];
			}

			return RAYX_OK;

		}

		else
		{
			status = RAYX_ERROR_ALLOC;
		}
	}

	else
	{
		status = RAYX_ERROR_ALLOC;
	}

	return status;
}

static void RayX_FreeZbuffer(double **zBuffer)
{
	free(*zBuffer);
	free(zBuffer);
}

static void RayX_ClearZbuffer(double **zBuffer, int width, int height)
{
	int i, n;

	for (i = 0, n = width * height; i < n; i ++)
	{
		(*zBuffer)[i] = -1;
	}
}

static void RayX_Render3DPoint(RayX_Renderer *renderer, RayX_Point const *point)
{
	double *bz = &renderer->zBuffer[y][x];

	if (*bz != -1 && *bz < point->z)
		return;

	SDL_SetRenderDrawColor(renderer->sdlRenderer, point->c.r, point->c.g, point->c.b, point->c.a);
	SDL_RenderDrawPoint(renderer->sdlRenderer, x, y);

	*bz = point->z;
}