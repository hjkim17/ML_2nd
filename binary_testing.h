/*
TESTING BINARY OUTPUT
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __BINARY_TESTING_ML2__
#define __BINARY_TESTING_ML2__

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct BINARY_CONFUSION_TABLE {
	int table[2][2];
	double MAX_OUT;
	double MIN_OUT;
}B_CONF_TBL;

void binary_table_clear();
void binary_table_update(double aprox_result, double true_result, double THRESHOLD);
void set_OUT(double aprox_result);
void gap_derivation(double aprox_result);
void fprint_b_confusion_mat();

#endif