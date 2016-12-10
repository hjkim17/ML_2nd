/*
STRUCT NEURAL STRUCTURE
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __STRUCTURE_SET_ML2__
#define __STRUCTURE_SET_ML2__

#include <cstdio>
#include <cstdlib>
#include "memory_pool.h"

#define _COUNT_3_
#ifdef _COUNT_S_
#define LEVEL_COUNT	(3)
#define INPUT_SIZE	(13)
#define LEVEL_1_SIZE	(4)
#define OUTPUT_SIZE	(1)
#define SIZE_ARRAY		{INPUT_SIZE, LEVEL_1_SIZE, OUTPUT_SIZE}
#endif
#ifdef _COUNT_3_
#define LEVEL_COUNT	(3)
#define INPUT_SIZE	(13)
#define LEVEL_1_SIZE	(30)
#define OUTPUT_SIZE	(1)
#define SIZE_ARRAY		{INPUT_SIZE, LEVEL_1_SIZE, OUTPUT_SIZE}
#endif
#ifdef _COUNT_4_
#define LEVEL_COUNT	(4)
#define INPUT_SIZE	(13)
#define LEVEL_1_SIZE	(11)
#define LEVEL_2_SIZE	(9)
#define OUTPUT_SIZE	(1)
#define SIZE_ARRAY		{INPUT_SIZE, LEVEL_1_SIZE, LEVEL_2_SIZE, OUTPUT_SIZE}
#endif
#ifdef _COUNT_5_
#define LEVEL_COUNT	(5)
#define INPUT_SIZE	(13)
#define LEVEL_1_SIZE	(13)
#define LEVEL_2_SIZE	(13)
#define LEVEL_3_SIZE	(13)
#define OUTPUT_SIZE	(1)
#define SIZE_ARRAY		{INPUT_SIZE, LEVEL_1_SIZE, LEVEL_2_SIZE, LEVEL_3_SIZE, OUTPUT_SIZE}
#endif
#define EPOCH_COUNT (1000)
extern double * LEVEL[LEVEL_COUNT];
extern double ** LEVEL_EDGE[LEVEL_COUNT - 1];
extern double * LEVEL_BASE_EDGE[LEVEL_COUNT - 1];
extern int size_per_level[LEVEL_COUNT];

void create();
void destroy();

#endif