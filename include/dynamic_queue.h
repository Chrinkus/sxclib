/*
 * struct dynamic_queue
 *
 * A FIFO queue that pushes into location indexed by tail and pops from the
 * location indexed by head. Will resize itself if needed.
 */
#pragma once

#include <stdlib.h>

struct dynamic_queue {
	void** data;
	size_t head;
	size_t tail;
	size_t size;
	size_t capacity;
};

struct dynamic_queue* dynamic_queue_init(struct dynamic_queue* q);

void dynamic_queue_free(struct dynamic_queue* q);

void* dynamic_queue_push(struct dynamic_queue* q, void* d);
void* dynamic_queue_pop(struct dynamic_queue* q);
