#include "initializer.h"

/* TODO
Modify LEVEL_EDGE(weight) with some rule
*/
void initialize() {
	simple_initialize();	//just rand 천분의 일 -천분의 일
	return;
}

void simple_initialize() {
	int L;
	int IN_CNT;
	int OUT_CNT;
	int IN;
	int OUT;
	double init_res;
	srand(time(0));

	L = 0;
	while (L < LEVEL_COUNT - 1) {
		IN_CNT = size_per_level[L];
		OUT_CNT = size_per_level[L + 1];
		OUT = 0;
		while (OUT < OUT_CNT) {
			IN = 0;
			while (IN < IN_CNT) {
#ifdef _INIT_TYPE_R_
				init_res = rand_init();
#endif
#ifdef _INIT_TYPE_ONE_
				init_res = one_init();
#endif
				LEVEL_EDGE[L][OUT][IN] = init_res;
				IN++;
			}
#ifdef _INIT_TYPE_R_
			init_res = rand_init();
#endif
#ifdef _INIT_TYPE_ONE_
			init_res = one_init();
#endif
			LEVEL_BASE_EDGE[L][OUT] = init_res;
			OUT++;
		}
		L++;
	}
}

double rand_init() {
	int init_res = (rand() - 16383.5) / 16383500;
	if (init_res < -0.001)
		init_res = 0.001;
	if (init_res > 0.001)
		init_res = 0.001;
	return init_res;
}

double one_init() {
	return 0.001;
}