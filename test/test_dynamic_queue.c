#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>

#include "dynamic_queue.h"

void print_int_queue(struct dynamic_queue* q)
{
	for (size_t i = 0; i < q->capacity; ++i) {
		printf("[%zu] ", i);
		if (q->data[i])
			printf("%d\n", *(int*)q->data[i]);
		else
			printf("NULL\n");
	}
}

static void test_dynamic_queue_init_free(void** state)
{
	(void) state;
	struct dynamic_queue q;

	assert_non_null(dynamic_queue_init(&q));
	assert_non_null(q.data);

	//const int dynamic_queue_base = q.capacity;	// hidden value

	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 0);
	assert_int_not_equal(q.capacity, 0);

	dynamic_queue_free(&q);
	assert_null(q.data);
}

static void test_dynamic_queue_push(void** state)
{
	(void) state;

	struct dynamic_queue q;
	assert_non_null(dynamic_queue_init(&q));

	//const int dynamic_queue_base = q.capacity;	// hidden value

	int x = 5;
	assert_non_null(dynamic_queue_push(&q, (void*)&x));
	assert_int_equal(q.size, 1);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 1);

	int y = 2;
	assert_non_null(dynamic_queue_push(&q, (void*)&y));
	assert_int_equal(q.size, 2);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 2);

	int z = 8;
	assert_non_null(dynamic_queue_push(&q, (void*)&z));
	assert_int_equal(q.size, 3);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 3);

	dynamic_queue_free(&q);
}

static void test_dynamic_queue_push_pop(void** state)
{
	(void) state;

	struct dynamic_queue q;
	assert_non_null(dynamic_queue_init(&q));

	//const int dynamic_queue_base = q.capacity;	// hidden value

	int a = 9;
	int b = 18;
	int c = 27;
	int d = 36;
	dynamic_queue_push(&q, (void*)&a);
	dynamic_queue_push(&q, (void*)&b);
	dynamic_queue_push(&q, (void*)&c);
	dynamic_queue_push(&q, (void*)&d);

	assert_int_equal(q.size, 4);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 4);

	int* p = (int*)dynamic_queue_pop(&q);
	assert_int_equal(*p, a);
	assert_int_equal(q.size, 3);
	assert_int_equal(q.head, 1);
	assert_int_equal(q.tail, 4);

	p = (int*)dynamic_queue_pop(&q);
	assert_int_equal(*p, b);
	assert_int_equal(q.size, 2);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 4);

	p = (int*)dynamic_queue_pop(&q);
	assert_int_equal(*p, c);
	assert_int_equal(q.size, 1);
	assert_int_equal(q.head, 3);
	assert_int_equal(q.tail, 4);

	p = (int*)dynamic_queue_pop(&q);
	assert_int_equal(*p, d);
	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 4);
	assert_int_equal(q.tail, 4);

	p = (int*)dynamic_queue_pop(&q);
	assert_null(p);
	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 4);
	assert_int_equal(q.tail, 4);

	dynamic_queue_free(&q);
}

static void test_dynamic_queue_wrap(void** state)
{
	(void) state;

	struct dynamic_queue q;
	dynamic_queue_init(&q);

	const int dynamic_queue_base = q.capacity;	// hidden value

	assert_int_equal(dynamic_queue_base, 8);

	int arr[7] = { 7, 14, 21, 28, 35, 42, 49 };
	for (int i = 0; i < 7; ++i)
		dynamic_queue_push(&q, (void*)&arr[i]);

	assert_int_equal(q.size, 7);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 7);

	int x = 56;
	assert_non_null(dynamic_queue_push(&q, (void*)&x));
	assert_int_equal(q.size, 8);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 0);

	int* p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 7);
	assert_int_equal(q.size, 7);
	assert_int_equal(q.head, 1);
	assert_int_equal(q.tail, 0);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 14);
	assert_int_equal(q.size, 6);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 0);

	int y = 63;
	assert_non_null(dynamic_queue_push(&q, (void*)&y));
	assert_int_equal(q.size, 7);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 1);

	int z = 70;
	assert_non_null(dynamic_queue_push(&q, (void*)&z));
	assert_int_equal(q.size, 8);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 21);
	assert_int_equal(q.size, 7);
	assert_int_equal(q.head, 3);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 28);
	assert_int_equal(q.size, 6);
	assert_int_equal(q.head, 4);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 35);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 42);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 49);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 56);
	assert_int_equal(q.size, 2);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 63);
	assert_int_equal(q.size, 1);
	assert_int_equal(q.head, 1);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_non_null(p);
	assert_int_equal(*p, 70);
	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 2);

	p = (int*)dynamic_queue_pop(&q);
	assert_null(p);
	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 2);
	assert_int_equal(q.tail, 2);

	dynamic_queue_free(&q);
}

static void test_dynamic_queue_dynamic(void** state)
{
	(void) state;

	struct dynamic_queue q;
	dynamic_queue_init(&q);

	const int dynamic_queue_base = q.capacity;	// hidden value

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	for (int i = 0; i < 12; ++i)
		dynamic_queue_push(&q, (void*)&arr[i]);
	assert_int_equal(q.size, 12);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 12);

	int* p = NULL;
	for (int i = 0; i < 12; ++i) {
		p = (int*)dynamic_queue_pop(&q);
		assert_non_null(p);
		assert_int_equal(*p, arr[i]);
	}

	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 12);
	assert_int_equal(q.tail, 12);
	assert_int_equal(q.capacity, 2 * dynamic_queue_base);

	p = (int*)dynamic_queue_pop(&q);
	assert_null(p);

	dynamic_queue_free(&q);
}

static void test_dynamic_queue_dyn_wrap(void** state)
{
	(void) state;

	struct dynamic_queue q;
	dynamic_queue_init(&q);

	// move head to middle then empty queue
	int x = 0;
	for (int i = 0; i < 4; ++i)
		dynamic_queue_push(&q, (void*)&x);

	for (int i = 0; i < 4; ++i)
		dynamic_queue_pop(&q);

	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 4);
	assert_int_equal(q.tail, 4);
	assert_int_equal(q.capacity, 8);

	// fill queue with a wrap
	int arr[] = { 12, 24, 36, 48, 60, 72, 84, 96, 108, 120 };
	for (int i = 0; i < 8; ++i)
		dynamic_queue_push(&q, (void*)&arr[i]);

	assert_int_equal(q.size, 8);
	assert_int_equal(q.head, 4);
	assert_int_equal(q.tail, 4);
	assert_int_equal(q.capacity, 8);

	//printf("Full & wrapped:\n");
	//print_int_queue(&q);

	// push one more, trigger resize
	dynamic_queue_push(&q, &arr[8]);
	assert_int_equal(q.size, 9);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 9);
	assert_int_equal(q.capacity, 16);

	//printf("Resized:\n");
	//print_int_queue(&q);

	dynamic_queue_push(&q, &arr[9]);
	assert_int_equal(q.size, 10);
	assert_int_equal(q.head, 0);
	assert_int_equal(q.tail, 10);
	assert_int_equal(q.capacity, 16);

	//printf("Resized +1:\n");
	//print_int_queue(&q);

	/* Need 'i' for arr[] access. Expected loop is:
	 * for (int* p; (p = (int*)dynamic_queue_pop(&q)) != NULL; )
	 */
	int* p = NULL;
	for (size_t i = 0; (p = (int*)dynamic_queue_pop(&q)) != NULL; ++i) {
		assert_int_equal(*p, arr[i]);
		//printf("Iter [%zu]: *p = %d, arr[i] = %d\n", i, *p, arr[i]);
	}
	assert_null(p);
	assert_int_equal(q.size, 0);
	assert_int_equal(q.head, 10);
	assert_int_equal(q.tail, 10);
	assert_int_equal(q.capacity, 16);

	dynamic_queue_free(&q);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_dynamic_queue_init_free),
		cmocka_unit_test(test_dynamic_queue_push),
		cmocka_unit_test(test_dynamic_queue_push_pop),
		cmocka_unit_test(test_dynamic_queue_wrap),
		cmocka_unit_test(test_dynamic_queue_dynamic),
		cmocka_unit_test(test_dynamic_queue_dyn_wrap),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

