/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tests_Socket
*/

#include <criterion/criterion.h>
#include "list.h"

inline static int to_int(void *ptr)
{
    if (!ptr)
        return -1;
    return *(int *)(ptr);
}

Test(List, Basics)
{
    int x = 42;
    list_t l;

    cr_assert(init_list(&l));
    cr_assert_eq(l.size, 0);
    cr_assert(append_list(&l, &x));
    cr_assert_eq(l.size, 1);
    cr_assert_eq(to_int(pop_list(&l)), x);
    cr_assert_eq(l.size, 0);
}

Test(List, Advanced)
{
    int x = 24, y = 42;
    list_t l;

    cr_assert(init_list(&l));
    cr_assert_not(insert_list(&l, &x, 5));
    for (int i = 0; i < 10; ++i) {
        cr_assert(append_list(&l, &x));
        cr_assert_eq(to_int(at_list(&l, i)), x);
    }
    cr_assert_eq(l.size, 10);
    cr_assert(insert_list(&l, &y, 0));
    cr_assert_eq(to_int(at_list(&l, 0)), y);
    cr_assert_eq(l.size, 11);
    cr_assert(insert_list(&l, &y, 5));
    cr_assert_eq(l.size, 12);
    cr_assert_eq(to_int(at_list(&l, 5)), y);
    cr_assert_eq(to_int(erase_list(&l, 5)), y);
    cr_assert_eq(l.size, 11);
    clear_list(&l);
    cr_assert_eq(l.size, 0);
}
