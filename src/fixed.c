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
#include <stdatomic.h>

#include "barrier.h"

/* TODO: the barrier's state. What has to be shared between the threads, and
 *       what does each thread have to remember for itself? */
typedef struct {
    int n;
    atomic_int count;      /* how many have arrived this round */
    atomic_int sense;      /* flips every round                */
} bar_t;

static _Thread_local int my_sense; 

static void *create(int nthreads)
{
    /* TODO: allocate it, initialise everything, and return it. Anything a
     *       thread might lock or wait on has to be ready BEFORE the first
     *       thread can reach it. */
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
    /* TODO: the barrier. Write the invariant you are keeping in a comment
     *       above it, in one line, before you write the code -- your report
     *       and your oral both ask you to state it. */

    //invariant tracks the amount of threads at the current run through
    bar_t *b = (bar_t *)p;

    int local = !my_sense;             /* the value I am waiting to see */
    my_sense  = local;

    if (atomic_fetch_add(&b->count, 1) == b->n - 1) {
        /* last one in: re-arm the counter, THEN release everybody */
        atomic_store(&b->count, 0);
        atomic_store(&b->sense, local);
    } else {
        while (atomic_load(&b->sense) != local) {
            sched_yield();//lets other threads use CPU
        }
    }
}

static void destroy(void *p)
{
    /* TODO: release what create() took. Every thread has been joined by the
     *       time this is called. */
    free(p);
}

const bar_ops_t bar_fixed = { "fixed", create, wait_, destroy };
