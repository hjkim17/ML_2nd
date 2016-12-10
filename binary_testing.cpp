#include "binary_testing.h"

B_CONF_TBL b_conf_tbl;

void binary_table_clear() {
	b_conf_tbl.table[0][0] = 0;		//TN
	b_conf_tbl.table[0][1] = 0;		//FN
	b_conf_tbl.table[1][0] = 0;		//FP
	b_conf_tbl.table[1][1] = 0;		//TP
	return;
}

void binary_table_update(double aprox_result, double true_result, double THRESHOLD) {
	double thrs = THRESHOLD + 0.5;
	double side = (aprox_result - thrs)*(true_result - thrs);
	if ((true_result - thrs) > 0) {
		if (side > 0) {
			b_conf_tbl.table[1][1]++;
		}
		else {
			b_conf_tbl.table[0][1]++;
		}
	}
	else {
		if (side > 0) {
			b_conf_tbl.table[0][0]++;
		}
		else {
			b_conf_tbl.table[1][0]++;
		}
	}
}

void set_OUT(double aprox_result) {
	b_conf_tbl.MAX_OUT = aprox_result;
	b_conf_tbl.MIN_OUT = aprox_result;
}

void gap_derivation(double aprox_result) {
	if (aprox_result > b_conf_tbl.MAX_OUT)
		b_conf_tbl.MAX_OUT = aprox_result;
	if (aprox_result < b_conf_tbl.MIN_OUT)
		b_conf_tbl.MIN_OUT = aprox_result;
}

void fprint_b_confusion_mat() {
	FILE * f = fopen("confusion matrix.txt", "w");
	fprintf(f, "Confusion Matrix\n");
	fprintf(f, "           | ");
	for (int i = 0; i < 2; i++) {
		fprintf(f, "Pred = %d ", i);
	}
	fprintf(f, "\n___________|____________________\n");
	for (int i = 0; i < 2; i++) {
		fprintf(f, "Actual = %d | ", i);
		for (int j = 0; j < 2; j++) {
			fprintf(f, "%8d ", b_conf_tbl.table[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
	return;
}