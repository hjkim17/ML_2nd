#include "feed_fowarder.h"

void feed_foward(double *vecs) {
	int i, j, k;
	if (LEVEL_COUNT < 1) {
		printf("NO LEVEL OCCUR\n");
		exit(1);
	}
	// load vecs as input
	i = 0;
	while (i < size_per_level[0]) {
		LEVEL[0][i] = vecs[i];
		i++;
	}
	// calculate each level except input level
	i = 1;
	while (i < LEVEL_COUNT - 1) {
		j = 0;
		while (j < size_per_level[i]) {
			LEVEL[i][j] = LEVEL_BASE_EDGE[i-1][j];
			k = 0;
			while (k < size_per_level[i - 1]) {
				LEVEL[i][j] += LEVEL[i - 1][k] * LEVEL_EDGE[i - 1][j][k];
				k++;
			}
			LEVEL[i][j] = 1 / (1 + exp(-LEVEL[i][j]));
			j++;
		}
		i++;
	}
	// output node calculation
	i = LEVEL_COUNT - 1;
	j = 0;
	while (j < size_per_level[i]) {
		LEVEL[i][j] = LEVEL_BASE_EDGE[i-1][j];
		k = 0;
		while (k < size_per_level[i - 1]) {
			LEVEL[i][j] += LEVEL[i - 1][k] * LEVEL_EDGE[i - 1][j][k];
			k++;
		}
		j++;
	}
	return;
}