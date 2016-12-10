/*
LOAD AND STRUCT INPUT/TESTING DATA FROM FILES
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __DATA_ML2__
#define __DATA_ML2__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "structure_set.h"

#define DIMENSION	(INPUT_SIZE)
#define MAX_CLASS_NO	(OUTPUT_SIZE)

typedef struct D {
	double x[DIMENSION];
	double real_result[MAX_CLASS_NO];
	struct D * next;
}D;
typedef struct D* D_PTR;

typedef struct TRAIN_HEAD {
	D_PTR head;
	D_PTR tail;
}TRH;

typedef struct TEST_HEAD {
	D_PTR head;
	D_PTR tail;
}TSH;

extern TRH trh;
extern TSH tsh;

void init_data();
void end_data();
void load_data();
D_PTR create_VE(const double * vec, int class_value);
void insert_TRN(D_PTR temp);
void insert_TST(D_PTR temp);

#endif