#include "structure_set.h"

pool * structure_pool;

/*
-------------------------- usage --------------------------
LEVEL[LAYER LEVEL][NODE NO.]
LEVEL_EDGE[LEVEL AS INPUT][OUTPUT NODE NO.][INPUT NODE NO.]
LEVEL_BASE_EDGE[LEVEL AS OUTPUT - 1][OUTPUT NODE NO.]
-----------------------------------------------------------
*/
double * LEVEL[LEVEL_COUNT];
double ** LEVEL_EDGE[LEVEL_COUNT-1];
double * LEVEL_BASE_EDGE[LEVEL_COUNT-1];
int size_per_level[LEVEL_COUNT] = SIZE_ARRAY;

#define _MALLOC_CREATE_
#ifndef _MALLOC_CREATE_
void create() {
	size_t pool_size = 0;
	for (int i = 0; i < LEVEL_COUNT; i++) {
		pool_size += sizeof(double) * size_per_level[i];
	}
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		pool_size += (sizeof(double *) * size_per_level[i+1]) + (sizeof(double) * size_per_level[i + 1] * (size_per_level[i] + 1));
	}
	structure_pool = (pool*)pool_create(pool_size);
	for (int i = 0; i < LEVEL_COUNT; i++) {
		LEVEL[i] = (double *)pool_alloc(structure_pool, sizeof(double) * size_per_level[i]);
	}
	for (int i = 0; i < LEVEL_COUNT-1; i++) {
		LEVEL_EDGE[i] = (double **)pool_alloc(structure_pool, sizeof(double *) * size_per_level[i+1]);
		for (int j = 0; j < size_per_level[i + 1]; j++) {
			LEVEL_EDGE[i][j] = (double *)pool_alloc(structure_pool, sizeof(double) * size_per_level[i]);
		}
		LEVEL_BASE_EDGE[i] = (double *)pool_alloc(structure_pool, sizeof(double) * size_per_level[i+1]);
	}
	return;
}

void destroy() {
	pool_free(structure_pool);
	return;
}
#endif
#ifdef _MALLOC_CREATE_
void create() {
	for (int i = 0; i < LEVEL_COUNT; i++) {
		LEVEL[i] = (double *)malloc(sizeof(double) * size_per_level[i]);
		printf("size_per_level[%d] : %d",i, size_per_level[i]);
	}
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		LEVEL_EDGE[i] = (double **)malloc(sizeof(double *) * size_per_level[i + 1]);
		printf("size_per_level[%d] : %d", i+1, size_per_level[i+1]);
		for (int j = 0; j < size_per_level[i + 1]; j++) {
			LEVEL_EDGE[i][j] = (double *)malloc(sizeof(double) * size_per_level[i]);
			printf("size_per_level[%d] : %d", i, size_per_level[i]);
		}
		LEVEL_BASE_EDGE[i] = (double *)malloc(sizeof(double) * size_per_level[i + 1]);
		printf("size_per_level[%d] : %d", i+1, size_per_level[i+1]);
	}
	return;
}

void destroy() {
	for (int i = 0; i < LEVEL_COUNT; i++) {
		free(LEVEL[i]);
	}
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		for (int j = 0; j < size_per_level[i + 1]; j++) {
			free(LEVEL_EDGE[i][j]);
		}
		free(LEVEL_EDGE[i]);
		free(LEVEL_BASE_EDGE[i]);
	}
	return;
}
#endif

