/*
	silly memory pool implementation in c
	cannot free element inside of that one by one,
	so when one loop of usage is done, just clear and get another loop of elements
*/

#include "memory_pool.h"

pool *pool_create(size_t size) {
	pool * p = (pool *)malloc(size + sizeof(pool));
	if (p == NULL) {
		fprintf(stderr, "memory pool allocate error\n");
		exit(1);
	}
	p->next = (char *)&p[POOL_ITEM_SPACE];
	p->end = p->next + size;
	p->pool_size = size;
	return p;
}

void pool_free(pool * p) {
	free(p);
}

void pool_clear(pool * p) {
	p->next = (char *)&p[POOL_ITEM_SPACE];
	p->end = p->next + p->pool_size;
}

int pool_acceptable(pool *p, size_t size) {
	if ((int)(p->end) - (int)(p->next) < size) {
		return POOL_FALSE;
	}
	else
		return POOL_TRUE;
}

void * pool_alloc(pool * p, size_t size) {
	if (!pool_acceptable(p, size))
		return NULL;
	void * start = (void *)p->next;
	p->next += size;
	return start;
}