#include "data.h"
#include "structure_set.h"
#include "initializer.h"
#include "feed_fowarder.h"
#include "error_back_propagator.h"
#include "binary_testing.h"

void first_test();

int main() {
	D_PTR current;

	init_data();
	load_data();
	create();
	
	/* TRAINING */
	initialize();
	printf("LOOP_1st : %lf\n", LEVEL_EDGE[LEVEL_COUNT - 2][0][0]);
	init_EBP();
	int EP_LOOP = 0;
	int ccnt = 0;
	while (EP_LOOP < EPOCH_COUNT) {
		clear_EBP();
		current = trh.head;
		while (current != NULL) {
			feed_foward(current->x);
			//printf("LOOP_1st : %lf\n", LEVEL_EDGE[LEVEL_COUNT - 2][0][0]);
			EBP(current->real_result);
			ccnt++;
			current = current->next;
		}
		EP_LOOP++;
		printf("LOOP_%d : %lf\n",EP_LOOP, LEVEL[LEVEL_COUNT-1][0]);
	}
	destroy_EBP();

	/* TESTING */
	FILE * error_txt = fopen("error.txt", "w");
	FILE * EER_txt = fopen("EER.txt", "w");

	binary_table_clear();
	first_test();
	fprint_b_confusion_mat();			// print confusion matrix to file

	/*
	double THRESHOLD = THRESH_MIN;
	while (THRESHOLD < THRESH_MAX) {
		clear_confusion();
		test_once(THRESHOLD);
		error_derivation_with_EER_THRESH();
		fprintf_error(error_txt);
		THRESHOLD += THRESH_INTERVAL;
	}
	THRESHOLD = get_EER_THRESH();
	double THRESHOLD_LIMIT = THRESHOLD + THRESH_INTERVAL;
	while (THRESHOLD < THRESHOLD_LIMIT) {
		clear_confusion();
		test_once(THRESHOLD);
		error_derivation_with_EER_THRESH();
		THRESHOLD + THRESH_PRECISE_INTERVAL;
	}

	THRESHOLD = get_EER_THRESH();
	clear_confusion();
	test_once(THRESHOLD);
	fprintf_EER(EER_txt);
	*/
	fclose(error_txt);
	fclose(EER_txt);
	destroy();
	end_data();
	return 0;
}

void first_test() {
	D_PTR current;
	current = tsh.head;
	if (current != NULL) {
		feed_foward(current->x);
		binary_table_update(LEVEL[LEVEL_COUNT-1][0], current->real_result[0], 0);
		set_OUT(LEVEL[LEVEL_COUNT - 1][0]);
		current = current->next;
	}
	while (current != NULL) {
		feed_foward(current->x);
		binary_table_update(LEVEL[LEVEL_COUNT - 1][0], current->real_result[0], 0);
		gap_derivation(LEVEL[LEVEL_COUNT - 1][0]);
		current = current->next;
	}
	return;
}

/*
void test_once(double THRESHOLD) {
	D_PTR current;
	current = tsh.head;
	while (current != NULL) {
		feed_foward(current->x, THRESHOLD / not in this way);
		update_confusion(LEVEL[LEVEL_COUNT - 1]);
		current = current->next;
	}
	return;
}
*/