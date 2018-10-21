Profiling
=========

A :ref:`profiler <profiler>` is a tool that tracks the execution of a
program. This is most commonly used to understand and measure the performance of
a program.


cProfile
--------

cProfile is a :ref:`profiler <profiler>` that comes as part of the Python
standard library. This means it is always available and does not need to be
installed separately. cProfile is designed to trace the execution of a program
collection information about the call graph. cProfile operates at the
granularity of a function call. Here how to invoke cProfile:

.. code-block:: python

   import cProfile

   p = cProfile.Profile()
   p.enable()

   # code to trace
   # ...

   p.disable()
   p.dump_stats('/path/to/save/results')


pstats
------

cProfile only collects data, in order to analyze it we use a second tool called
``pstats``. pstats is an interactive command line tool for helping you explore
the call graph and relative timings of sections.

The key operations in pstats:

- stats
- sorting
- callees
- callers

stats
~~~~~

The ``stats`` command displays either the stats for a single function or the top
n values based on the sort.

::

   out.stats% stats 10

prints the top 10 values based on the current sort.

::

   out.stats% stats pattern1 pattern2 ...

prints the stats for functions whose ``filepath.py:line-number(function)``
matches all the patterns where patterns are regular expressions.

For example:

::

   Fri Oct 19 05:29:01 2018    out.stats

            314925129 function calls (314813999 primitive calls) in 352.943 seconds

      Ordered by: call count
      List reduced from 344 to 2 due to restriction <'bit_enum.py'>

      ncalls  tottime  percall  cumtime  percall filename:lineno(function)
    29290879   32.323    0.000   32.323    0.000 /home/joe/projects/python/slider/slider/bit_enum.py:47(<dictcomp>)
    29290879   96.887    0.000  144.744    0.000 /home/joe/projects/python/slider/slider/bit_enum.py:33(unpack)


   out.stats% stats bit_enum.py:47
   Fri Oct 19 05:29:01 2018    out.stats

            314925129 function calls (314813999 primitive calls) in 352.943 seconds

      Ordered by: call count
      List reduced from 344 to 1 due to restriction <'bit_enum.py:47'>

      ncalls  tottime  percall  cumtime  percall filename:lineno(function)
    29290879   32.323    0.000   32.323    0.000 /home/joe/projects/python/slider/slider/bit_enum.py:47(<dictcomp>)


   out.stats% stats bit_enum.py unpack
   Fri Oct 19 05:29:01 2018    out.stats

            314925129 function calls (314813999 primitive calls) in 352.943 seconds

      Ordered by: call count
      List reduced from 344 to 2 due to restriction <'bit_enum.py'>
      List reduced from 2 to 1 due to restriction <'unpack'>

      ncalls  tottime  percall  cumtime  percall filename:lineno(function)
    29290879   96.887    0.000  144.744    0.000 /home/joe/projects/python/slider/slider/bit_enum.py:33(unpack)



sorting
~~~~~~~

pstats allows you to sort functions by the following criteria:

- ``tottime``: The total time spent in this function excluding functions called
  by this function.
- ``cumtime``: The cumulative time spent in this function including the time
  spent in all functions called in this function.
- ``ncalls``: The total number of calls to the function.

Sorting by ``tottime`` is useful for finding the meaty functions where a lot of
work is actually being done. The highest ``tottime`` functions are worth
looking over to see if there are easy optimizations to make.

Sorting by ``cumtime`` is useful for getting a sense of the high level
operations that are taking a long time. This will help see the chain of events
that lead to the most time being spent.

Sorting by ``ncalls`` is useful for identifying algorithmic issues. If you see a
function with much higher than expected call count, it may indicate that your
high level algorithm is implemented incorrectly. Functions with a high
``tottime`` and high ``ncalls`` are especially important to look out for. For
example:

::

      ncalls  tottime  percall
    29290879   96.887    0.000

Here we are spending almost no time at all in any individual call, but summing
those near-zero values grows to a very large amount of time. Trying to micro
optimize this function may or may not help, but you should try to evaluate *why*
the function is being called so many times first.

callees
~~~~~~~

The callees command prints the stats for all the functions called by the target
function. The callee functions are printed in the order of the currently active
sort. This function is useful for understanding where a function's cumulative
time comes from.

Example:

::

  out.stats% callees _consume_actions
     Ordered by: cumulative time
     List reduced from 344 to 1 due to restriction <'_consume_actions'>

  Function                                                                                    called...
                                                                                                  ncalls  tottime  cumtime
  /home/joe/projects/python/slider/slider/replay.py:132(_consume_actions)  -> 29287456   96.881  144.685  /home/joe/projects/python/slider/slider/bit_enum.py:33(unpack)
                                                                                                29287456   12.551   12.551  /home/joe/projects/python/slider/slider/replay.py:43(__init__)
                                                                                                    3423    0.002    0.004  /home/joe/projects/python/slider/slider/replay.py:75(_consume_int)
                                                                                                    3423    0.025    8.845  /usr/lib64/python3.6/lzma.py:322(decompress)
                                                                                                29287456    7.258   13.943  <string>:12(__new__)
                                                                                                29287456    2.627    2.627  {method 'append' of 'list' objects}
                                                                                                29290879    8.439    8.439  {method 'split' of 'bytes' objects}

callers
~~~~~~~

The callers command prints the functions which called the target function. The
functions are printed in the order of the currently active sort. The callers
function is useful if you want to understand where a high ``ncalls`` function is
being called from.


Example::

   out.stats% callers unpack
      Ordered by: call count
      List reduced from 344 to 1 due to restriction <'unpack'>

   Function                                                                           was called by...
                                                                                          ncalls  tottime  cumtime
   /home/joe/projects/python/slider/slider/bit_enum.py:33(unpack)  <- 29287456   96.881  144.685  /home/joe/projects/python/slider/slider/replay.py:132(_consume_actions)
                                                                                            3423    0.006    0.059  /home/joe/projects/python/slider/slider/replay.py:626(parse)

Here we can see that there are 2 calls to ``unpack`` in ``replay.py``; however,
with ``callers`` it is clear that almost all of the calls are coming from
``_consume_actions``.
