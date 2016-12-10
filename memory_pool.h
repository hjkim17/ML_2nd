/*
	silly memory pool implementation in c
	cannot free element inside of that one by one,
	so when one loop of usage is done, just clear and get another loop of elements
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef __memory_pool_ir2__
#define __memory_pool_ir2__

#include <cstdio>
#include <cstdlib>

#define POOL_TRUE			1
#define POOL_FALSE			0

#define POOL_ITEM_SPACE		1

typedef struct pool {
	char * next;
	char * end;
	size_t pool_size;
}pool;

pool *pool_create(size_t size);
void pool_free(pool * p);
void pool_clear(pool * p);
int pool_acceptable(pool *p, size_t size);
void * pool_alloc(pool * p, size_t size);

#endif