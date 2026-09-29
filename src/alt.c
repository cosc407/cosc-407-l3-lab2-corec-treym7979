/* Lab 2, core C -- THE ALTERNATIVE named in BRIEF.md.
 *
 * The barrier the author of given.c rejected: a mutex, a condition variable, a
 * counter, and a generation number so that it is reusable. This is the version
 * class 6 derives and the one the library uses.
 *
 * It is correct. At low thread counts it will be the slowest of your three
 * columns, and the author of given.c was not wrong about that -- only about
 * what happens next. Do not tune it: it is evidence, not a submission.
 *
 * Two things that are not optional, and S2.3 may ask you which: the wake-up
 * has to reach every waiter, and the predicate has to be re-checked in a loop.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "barrier.h"

/* TODO: the barrier's state. What has to be shared between the threads, and
 *       what does each thread have to remember for itself? */

static void *create(int nthreads)
{
    /* TODO: allocate it, initialise everything, and return it. Anything a
     *       thread might lock or wait on has to be ready BEFORE the first
     *       thread can reach it. */
    (void)nthreads;
    return NULL;
}

static void wait_(void *p)
{
    /* TODO: the barrier. Write the invariant you are keeping in a comment
     *       above it, in one line, before you write the code -- your report
     *       and your oral both ask you to state it. */
    (void)p;
}

static void destroy(void *p)
{
    /* TODO: release what create() took. Every thread has been joined by the
     *       time this is called. */
    (void)p;
}

const bar_ops_t bar_alt = { "alt", create, wait_, destroy };
