#include "dynamic_queue.h"

#include <stdio.h>

enum queue_sizes { dynamic_queue_base = 8 };

struct dynamic_queue* dynamic_queue_init(struct dynamic_queue* q)
{
	if (!(q->data = malloc(sizeof(void*) * dynamic_queue_base)))
		return NULL;

	q->head = 0;
	q->tail = 0;
	q->size = 0;
	q->capacity = dynamic_queue_base;
	return q;
}

void dynamic_queue_free(struct dynamic_queue* q)
{
	free(q->data);
	q->data = NULL;
}

static struct dynamic_queue* dynamic_queue_resize(struct dynamic_queue* q)
{
	size_t new_cap = q->capacity * 2;
	void** new_data = malloc(sizeof(void*) * new_cap);
	if (!new_data)
		return NULL;

	// i is linear, j may wrap. First iteration head == tail.
	for (size_t i = 0, j = q->head;
			i == 0 || (j != q->tail);	// ignore first iter
			++i, j = (j + 1) % q->size)
		new_data[i] = q->data[j];

	free(q->data);
	q->data = new_data;
	q->head = 0;
	q->tail = q->size;
	q->capacity = new_cap;
	return q;
}

void* dynamic_queue_push(struct dynamic_queue* q, void* d)
{
	if (q->size == q->capacity && !dynamic_queue_resize(q))
		return NULL;

	q->data[q->tail++] = d;
	q->tail %= q->capacity;
	++q->size;

	return d;
}

void* dynamic_queue_pop(struct dynamic_queue* q)
{
	if (q->size == 0)
		return NULL;

	void* popped = q->data[q->head];
	q->data[q->head++] = NULL;
	q->head %= q->capacity;
	--q->size;

	return popped;
}

