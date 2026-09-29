/* Lab 2, core C -- YOUR MINIMAL CORRECTION.
 *
 * wait_() must work every time it is called, at 1, 2, 4 and 8 threads, and at
 * more threads than this machine has cores -- which is the case that matters
 * in this core, so run it there yourself before you believe the autograder.
 *
 * THE CONSTRAINT FROM YOUR BRIEF: keep the algorithm. The atomic counter, the
 * flipping sense flag, no mutex, no condition variable. Copy given.c's wait_()
 * across and change only what a waiting thread does while it waits. If that
 * alone fixes it, then the waiting was the defect, and you have a proof rather
 * than a story.
 *
 * Whatever number your fix needs, S2.3 asks what it should be compared
 * against and what happens at zero and at infinity. Pick it deliberately.
 *
 * Copy anything you like out of given.c. Do not edit it.
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

const bar_ops_t bar_fixed = { "fixed", create, wait_, destroy };
