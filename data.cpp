#include "data.h"

TRH trh;
TSH tsh;
int tr_cnt;
int ts_cnt;

void init_data() {
	trh.head = NULL;
	trh.tail = NULL;
	tsh.head = NULL;
	tsh.tail = NULL;
	tr_cnt = 0;
	ts_cnt = 0;
	return;
}

void end_data() {
	D_PTR current;
	current = trh.head;
	while (current != NULL) {
		D_PTR temp = current;
		current = current->next;
		free(temp);
	}
	current = tsh.head;
	while (current != NULL) {
		D_PTR temp = current;
		current = current->next;
		free(temp);
	}
	return;
}

void load_data() {
	double v[DIMENSION];
	int r;
	FILE * trn = fopen("trn.txt", "r");
	if (trn == 0) {
		fprintf(stderr, "trn.txt not found.\n");
		exit(1);
	}
	while (!feof(trn)) {
		int first = fscanf(trn, "%lf", &v[0]);
		if (first != 1)
			continue;
		if (v[0] < 0.00000001 && v[0] > -0.00000001)
			continue;
		int second = fscanf(trn, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d", &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7], &v[8], &v[9], &v[10], &v[11], &v[12], &r);
		if (second != 13)
			continue;
		D_PTR temp = create_VE(v, r);
		insert_TRN(temp);
	}
	fclose(trn);

	FILE * tst = fopen("tst.txt", "r");
	if (tst == 0) {
		fprintf(stderr, "tst.txt not found.\n");
		exit(1);
	}
	while (!feof(tst)) {
		int first = fscanf(tst, "%lf", &v[0]);
		if (first != 1)
			continue;
		if (v[0] < 0.00000001 && v[0] > -0.00000001)
			continue;
		int second = fscanf(tst, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d", &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7], &v[8], &v[9], &v[10], &v[11], &v[12], &r);
		if (second != 13)
			continue;
		D_PTR temp = create_VE(v, r);
		insert_TST(temp);
	}
	fclose(tst);

	printf("trn tst data load done.\n");
}

D_PTR create_VE(const double * vec, int class_value) {
	D_PTR temp = (D_PTR)malloc(sizeof(D));
	for (int i = 0; i < DIMENSION; i++) {
		(temp->x)[i] = vec[i];
	}
	if (MAX_CLASS_NO == (1)) {
		temp->real_result[0] = (double)class_value;
	}
	else {
		temp->real_result[class_value] = 1.0;
	}
	temp->next = NULL;
	return temp;
}

void insert_TRN(D_PTR temp) {
	if (tr_cnt == 0) {
		trh.head = temp;
		trh.tail = temp;
	}
	else {
		trh.tail->next = temp;
		trh.tail = temp;
	}
	tr_cnt++;
	return;
}

void insert_TST(D_PTR temp) {
	if (ts_cnt == 0) {
		tsh.head = temp;
		tsh.tail = temp;
	}
	else {
		tsh.tail->next = temp;
		tsh.tail = temp;
	}
	ts_cnt++;
	return;
}