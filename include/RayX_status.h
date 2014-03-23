#ifndef RAYX_STATUS_H
#define RAYX_STATUS_H

	#define RAYX_STATUS_SIZE_STRING

typedef enum {
	RAYX_OK, RAYX_ERROR_ALLOC
} RayX_Status;

typedef struct _RayX_Error {
	RayX_Status status;
} RayX_Error;

#endif