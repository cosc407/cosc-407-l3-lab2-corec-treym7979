# Prediction sheet — push by 0:20, before you compile

> Marked on **having predicted** and on reconciling it in S3.1 — **not on being
> right.** A confident wrong prediction you then explain is full marks. A blank
> page is none. A page timestamped after your first run is worse than none.
>
> Read `src/given.c` and `BRIEF.md`. Run nothing.

Cores:  4
Lab 0 spread:  4

> **P1.** `./bar given` on **one** thread — does it come out right? Yes/no, one
> sentence why.

Yes, because since there is only one thread there is no competition between the threads for any permits making the barrier work properly no matter what since it only has to deal with a single thread.

> **P2.** On **8** threads, pick one and commit to it: right answer / wrong
> answer / it stops. If wrong, roughly how big is `bad`? If it stops, say at
> which of the two waits in a round.

The code stops, the second wait would be the cause because since the barrier is not doing its purpose the threads are not synconised leading to the waits being blocked when they are needed.

> **P3.** Three runs at 8 threads — **identical** numbers, or different? Think
> about this one before you write it; it is the most useful line on the page.

Different numbers, since the barrier is failing in different ways i.e. letting different threads increment and decrement when they are not supposed to, but they are random threads not the same each time.

> **P4.** Seconds, before measuring. Orders of magnitude are what matter. `cpu`
> is process CPU time over all threads, so `cpu`/`time` is how many cores were
> busy — one number per box.

| | 1 thread: time | 8 threads: time | 8 threads: cpu/time |
|---|---|---|---|
| `given` |1 |8 | 4|
| `fixed` |1 |8 |4 |
| `alt` | 1|8 |4 |

> **P5.** Fastest and slowest at 8 threads? Name anything you expect to get
> **slower** as threads are added, and anything you expect to stop altogether.

I expect given and fixed to be the fastest at 8 threads, due to the constants. Where as the alt would be slower due to the constant change in output. As threads are added I expect to see time to go up due to the more proccessing/cpu needed to run through them.
