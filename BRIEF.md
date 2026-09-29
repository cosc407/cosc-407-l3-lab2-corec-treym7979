# Sealed core **C**

Read `lab2-core.md` first. Other sections were given a different core.

**Every total this program prints is right.** Stop checking the answer; there is
nothing wrong with it. Nothing in this core is a race, and no test of
correctness will ever fail.

```sh
make
./bar given 1 2000
./bar given 8 2000
nproc                      # you are going to need this number
```

**A constraint on your fix.** `src/fixed.c` must keep the algorithm it was
given: the atomic counter, the flipping sense flag, no mutex, no condition
variable. Copy `given.c`'s `wait_` across and change **only what a waiting
thread does while it waits**. If that alone fixes it, then what was wrong *was*
the waiting — which is a proof instead of a story. Replacing the algorithm also
works, and it is the alternative, not the fix.

**The alternative** (`src/alt.c`): the barrier the author of `given.c` rejected
— **a mutex, a condition variable, a counter and a generation number**, the
version class 6 derives. It is correct, and at low thread counts it will be the
slowest of the three. Both it and your `fixed` are defensible answers, and
choosing between them is a judgement about what machine you are on.

**Your four questions, for this core**

- **S2.1 mechanism.** Name what a waiting thread in `given.c` is doing, in
  terms of the scheduler rather than the source: what does it hold, what is it
  competing with, and *who is it competing with*. One sentence, then the
  consequence in one more.
- **S2.2 proof.** A measurement. (1) `given`'s time **and `cpu`/`time`** at 1,
  2, 4, 8 threads, and then at 1×, 2× and 3× your core count — that sweep is
  the proof and nothing else is. Use `BAR_WATCHDOG` when the watchdog fires; it
  is not stuck. (2) Say what `cpu`/`time` would be for a barrier that blocks,
  and what it is here. (3) One sentence on why every run above was *correct*.
- **S2.3 minimality.** Your fix has a number in it — how long a thread waits
  before it gives up the core. Say what number you used, what it should be
  compared against, and what happens at both extremes: zero, and infinity.
- **S3.2 ship it.** You have two correct barriers with opposite failure modes:
  one is cheap until the machine is oversubscribed, the other pays the same
  price always. Which ships, **and what measurement would change your mind?**
  No second half, half the marks.

**No timing threshold is auto-checked for this core.** The size of the effect is
the size of your machine — on a two-core Codespace four threads is already
oversubscribed and on a lab PC it takes thirty-two — and a threshold would be
marking your hardware. Your sweep is the evidence and a person reads it. *"The
crossover was at N threads on this machine, and here is the sweep that shows
it"* is a full-marks answer whatever N is.

**One question you may get in the oral.** *Every number this program printed was
correct. Show me what it was doing wrong, and the one measurement that proves
it.*
