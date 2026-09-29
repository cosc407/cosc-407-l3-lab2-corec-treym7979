/* COSC 407/507 Lab 2, core C -- the barrier you were handed.
 *
 * *** DO NOT EDIT. *** It is hashed by the autograder, and your report has to
 * compare against the code you were handed. Work in fixed.c and alt.c.
 *
 * ---------------------------------------------------------------------------
 * What the author believed, in their own words:
 *
 *   "Locks and condition variables are for barriers you might wait at for a
 *    long time. This one is entered thousands of times a second and the wait
 *    is a few microseconds, so going through the kernel to sleep and be woken
 *    costs far more than the wait itself.
 *
 *    So: no mutex, no condition variable, no system call. An atomic counter, a
 *    sense flag that flips every round so the barrier is reusable without ever
 *    resetting anything, and a loop that reads the flag until it changes. It
 *    is correct -- the atomics do the ordering -- and it is the fastest
 *    barrier here. Adding threads only adds a few more reads of a flag that is
 *    already in cache, so it degrades gracefully however many threads you give
 *    it."
 *
 * Exactly one of the claims in that paragraph is false. Every total this
 * program prints is right, so it is not that one.
 * ---------------------------------------------------------------------------
 *
 * The algorithm is the standard centralised sense-reversing barrier: Mellor-
 * Crummey and Scott 1991, and Pacheco 4.8 calls the same trick a "flag".
 * `my_sense` is thread-local, so each thread remembers which way round it is
 * without any shared state to reset.
 */
#include <stdatomic.h>
#include <stdlib.h>

#include "barrier.h"

typedef struct {
    int        n;
    atomic_int count;      /* how many have arrived this round */
    atomic_int sense;      /* flips every round                */
} bar_t;

static _Thread_local int my_sense;     /* 0 for every new thread */

static void *create(int nthreads)
{
    bar_t *b = malloc(sizeof *b);
    if (b == NULL) {
        return NULL;
    }
    b->n = nthreads;
    atomic_init(&b->count, 0);
    atomic_init(&b->sense, 0);
    return b;
}

static void wait_(void *p)
{
    bar_t *b = (bar_t *)p;

    int local = !my_sense;             /* the value I am waiting to see */
    my_sense  = local;

    if (atomic_fetch_add(&b->count, 1) == b->n - 1) {
        /* last one in: re-arm the counter, THEN release everybody */
        atomic_store(&b->count, 0);
        atomic_store(&b->sense, local);
    } else {
        while (atomic_load(&b->sense) != local) {
            /* Spin. There is nothing in here on purpose: the whole claim of
             * this barrier is that reading a flag in a loop is the cheap way
             * to wait. */
        }
    }
}

static void destroy(void *p)
{
    free(p);
}

const bar_ops_t bar_given = { "given", create, wait_, destroy };
