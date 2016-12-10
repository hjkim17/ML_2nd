#include "error_back_propagator.h"

pool * weight_pool;

/* TODO
EBP with DATA result and each STRUCTURE
*/
void EBP(double * r) {
	test(r);
	return;
}

double *R[LEVEL_COUNT - 1];
double ** PAST_LEVEL_EDGE[LEVEL_COUNT - 1];
double * PAST_LEVEL_BASE_EDGE[LEVEL_COUNT - 1];

void init_EBP() {
	size_t pool_size = 0;
	for (int i = 1; i < LEVEL_COUNT; i++) {
		pool_size += sizeof(double) * size_per_level[i];
	}
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		pool_size += (sizeof(double *) * size_per_level[i + 1]) + (sizeof(double) * size_per_level[i + 1] * (size_per_level[i] + 1));
	}
	weight_pool = (pool*)pool_create(pool_size);
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		R[i] = (double *)pool_alloc(weight_pool, sizeof(double) * size_per_level[i + 1]);
	}
	for (int i = 0; i < LEVEL_COUNT - 1; i++) {
		PAST_LEVEL_EDGE[i] = (double **)pool_alloc(weight_pool, sizeof(double *) * size_per_level[i + 1]);
		for (int j = 0; j < size_per_level[i + 1]; j++) {
			PAST_LEVEL_EDGE[i][j] = (double *)pool_alloc(weight_pool, sizeof(double) * size_per_level[i]);
		}
		PAST_LEVEL_BASE_EDGE[i] = (double *)pool_alloc(weight_pool, sizeof(double) * size_per_level[i + 1]);
	}
	return;
}

void clear_EBP() {
	int L;
	int IN_CNT;
	int OUT_CNT;
	int IN;
	int OUT;
	L = 0;
	while (L < LEVEL_COUNT - 1) {
		IN_CNT = size_per_level[L];
		OUT_CNT = size_per_level[L + 1];
		OUT = 0;
		while (OUT < OUT_CNT) {
			IN = 0;
			while (IN < IN_CNT) {
				PAST_LEVEL_EDGE[L][OUT][IN] = 0;		//save as past delta
				IN++;
			}
			PAST_LEVEL_BASE_EDGE[L][OUT] = 0;		//save as past delta
			OUT++;
		}
		L++;
	}
	return;
}

void destroy_EBP() {
	pool_free(weight_pool);
}

void test(double * REAL) {
	int N;
	int L;
	int LEV_CNT;
	int PN;
	int PLEV_CNT;
	// calc R
	N = 0;
	LEV_CNT = OUTPUT_SIZE;
	while (N < LEV_CNT) {
		R[LEVEL_COUNT - 2][N] = REAL[N] - LEVEL[LEVEL_COUNT - 1][N];
		//printf("R[%d][%d] : %lf\n", LEVEL_COUNT - 2, N, R[LEVEL_COUNT - 2][N]);
		N++;
	}
	
	L = LEVEL_COUNT - 3;
	while (L > -1) {
		N = 0;
		LEV_CNT = size_per_level[L + 1];
		PLEV_CNT = size_per_level[L + 2];
		while (N < LEV_CNT) {
			PN = 0;
			R[L][N] = 0;
			while (PN < PLEV_CNT) {
				R[L][N] += R[L + 1][PN]*LEVEL_EDGE[L+1][PN][N];
				PN++;
			}
			R[L][N] = R[L][N] * LEVEL[L  +1][N] * (1 - LEVEL[L + 1][N]);
			//printf("R[%d][%d] : %lf\n", L, N, R[L][N]);
			N++;
		}
		L--;
	}
	// calc weights
						//double BASE_EDGE_WEIGHT[100][100];
						//double EDGE_WEIGHT[100][100][100];
	int IN_CNT;
	int OUT_CNT;
	int IN;
	int OUT;
	double weight_temp;		// for efficient calculation
	L = 0;
	while (L < LEVEL_COUNT - 1) {
		IN_CNT = size_per_level[L];
		OUT_CNT = size_per_level[L + 1];
		OUT = 0;
		while (OUT < OUT_CNT) {
			IN = 0;
			while (IN < IN_CNT) {
				weight_temp = ETHA * R[L][OUT] * LEVEL[L][IN] + ALPHA * PAST_LEVEL_EDGE[L][OUT][IN];
				//EDGE_WEIGHT[L][IN][OUT] = R[L][OUT] * LEVEL[L][IN];
				LEVEL_EDGE[L][OUT][IN] = LEVEL_EDGE[L][OUT][IN] + weight_temp;
				PAST_LEVEL_EDGE[L][OUT][IN] = weight_temp;		//save as past delta
				IN++;
			}
			//BASE_EDGE_WEIGHT[L][OUT] = R[L][OUT];
			weight_temp = ETHA * R[L][OUT] + ALPHA * PAST_LEVEL_BASE_EDGE[L][OUT];
			LEVEL_BASE_EDGE[L][OUT] = LEVEL_BASE_EDGE[L][OUT] + weight_temp;
			PAST_LEVEL_BASE_EDGE[L][OUT] = weight_temp;		//save as past delta
			OUT++;
		}
		L++;
	}
	return;
}
