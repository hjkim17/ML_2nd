/*
SUBPROBLEMS OF BACK PROPAGATION
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __ERROR_BACK_PROPAGATOR_ML2__
#define __ERROR_BACK_PROPAGATOR_ML2__

#include <cstdio>
#include <cstdlib>
#include "data.h"
#include "structure_set.h"

#define ETHA		(0.00001)
#define ALPHA		(0.001)

void EBP(double * r);
void init_EBP();
void clear_EBP();
void destroy_EBP();
void test(double * REAL);

#endif