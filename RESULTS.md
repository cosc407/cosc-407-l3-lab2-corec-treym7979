# Lab 2 results — sealed core

Name:  Trey Major
Student number:  78688181
Lab section:  L03
Core:  C
Machine:  Codespace - 4 cores
Cores:  4

## Tools and sources

Tools and sources: notes taken before lab and during class

> Mandatory, even if it says "none". **No AI in the lab, at all** — see the
> README. Missing declaration: zero until you supply one. False one: misconduct.

## S2 — the defect · 40 marks

Three or more runs of `./bar given`, including one thread:

```
mode=given threads=1 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0017 cpu=0.0018
mode=given threads=4 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0054 cpu=0.0192
mode=given threads=8 rounds=2000 bad=-1 firstbad=-1 checksum=unknown correct=no deadlock=yes time=5.0479 cpu=19.3209
```

**S2.1** Name the mechanism: which claim in `given.c`'s header is false, and
what is actually happening? State the barrier's invariant and say which half of
it this code does not keep.

That "Adding threads only adds a few more reads of a flag that is already in cache", which is false because adding more threads only causes more compition between the threads to modify the counter.

**S2.2** Prove it, in the form your `BRIEF.md` requires.

given's time for 8 cores is 5 seconds and the cpu is 19 using the calculation its using all 4 cores and deadlocks proving that his method while adding threads just does not work.

**S2.3** Minimality: what breaks if you do less, what it costs if you do more.

The entire code breaks if you do less because of the race that the threads take to try and one up each other leading to a deadlock.

## S3 — the measurement · 30 marks

`./bar all <t> <rounds>` at 1, 2, 4 and 8 threads. Pasted, not retyped. If a
mode stops, `all` stops with it — run the modes one at a time and paste those.

```
mode=given threads=1 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0016 cpu=0.0017
mode=fixed threads=1 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0016 cpu=0.0016
mode=alt threads=1 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0016 cpu=0.0017

mode=given threads=2 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0037 cpu=0.0072
mode=fixed threads=2 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0079 cpu=0.0131
mode=alt threads=2 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0484 cpu=0.0403

mode=given threads=4 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0058 cpu=0.0208
mode=fixed threads=4 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0181 cpu=0.0625
mode=alt threads=4 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0865 cpu=0.1472

mode=given threads=8 rounds=2000 bad=-1 firstbad=-1 checksum=unknown correct=no deadlock=yes time=5.0232 cpu=19.1950
mode=fixed threads=8 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0347 cpu=0.1352
mode=alt threads=8 rounds=2000 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.1962 cpu=0.3722
```

| threads | given: correct? | given: time | given: cpu | fixed: time | fixed: cpu | alt: time | alt: cpu |
|---|---|---|---|---|---|---|---|
| 1 |yes | 0.0016| 0.0017| 0.0016| 0.0016| 0.0016|0.0017 |
| 2 |yes |0.0037 | 0.0072| 0.0079| 0.0131| 0.0484| 0.0403|
| 4 |yes | 0.0058| 0.0208| 0.0181|0.0625 | 0.0865| 0.1472|
| 8 |no | 5.0232|19.1950 | 0.0347|0.1352 | 0.01962| 0.3722|

**S3.1** Reconcile with `PREDICTION.md`: quote what you predicted, say what
happened, account for the difference. If you were right, say what would have
made you wrong.

I was semi right in my prediction, I said one core would run the fastest which it did and 8 cores would take ore time and deadlock in given which it did in the end. that is what I predicted and it came true.

**S3.2** Which would you ship on this machine, **and what measurement would
change your mind?**

I would ship the whiole machine, if the threads came back as deadlocked obiously I would change my mind.

## S4 — explain-back · 15 marks

> Two or three sentences, your own words: someone who has not seen this code
> asks *what was wrong with it, and what did fixing it cost?*

The user did not account for the addition of threads leading to a deadlock at 8 or more threads. fixing was as simple as adding a clause so when a thread reaches a certain point it sleeps/slows down for other threads to catch up. the fixed costed little and made the code run faster and smoother espesially on the cpu.

## Anything you got stuck on

i accidentally did alt on fixed and didnt realise till later and had to spend time fixing making my responses smaller than i wanted.
