#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "point.h"

static void test_point_2d_move(void** state)
{
	(void) state;

	struct point_2d pt = { 0, 0 };
	point_2d_move(&pt, 2, -3);

	assert_int_equal(pt.x, 2);
	assert_int_equal(pt.y, -3);

	point_2d_move(&pt, -7, 4);

	assert_int_equal(pt.x, -5);
	assert_int_equal(pt.y, 1);
}

static void test_point_2d_move_to(void** state)
{
	(void) state;

	struct point_2d pt = { 0, 0 };
	point_2d_move_to(&pt, -242, 87);

	assert_int_equal(pt.x, -242);
	assert_int_equal(pt.y, 87);

	point_2d_move_to(&pt, 52, -113);

	assert_int_equal(pt.x, 52);
	assert_int_equal(pt.y, -113);
}

static void test_point_2d_cmp(void** state)
{
	(void) state;

	struct point_2d pt1 = { 0, 0 };
	struct point_2d pt2 = { 1, 5 };
	assert_true(point_2d_cmp(&pt1, &pt2) < 0);

	struct point_2d pt3 = { 0, 2 };
	assert_true(point_2d_cmp(&pt1, &pt3) < 0);

	struct point_2d pt4 = { -1, 4 };
	assert_true(point_2d_cmp(&pt4, &pt3) < 0);

	struct point_2d pt5 = { 0, 0 };
	assert_true(point_2d_cmp(&pt1, &pt5) == 0);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_point_2d_move),
		cmocka_unit_test(test_point_2d_move_to),
		cmocka_unit_test(test_point_2d_cmp)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

