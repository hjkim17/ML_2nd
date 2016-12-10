/*
SETUP INITIAL WEIGHT
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __INITIALIZER_ML2__
#define __INITIALIZER_ML2__

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "data.h"
#include "structure_set.h"

#define _INIT_TYPE_R_

void initialize();
void simple_initialize();
double rand_init();
double one_init();

#endif