Memory Management
=================

When dealing with memory, one of the things to do is keep track of which memory
is in use at any given time. Basically, when a program decides that it would
like to store some data, it needs to find a region in memory large enough to
store the given value or values, but is not currently being used to store a
value that we would like to read later. The term for this problem is
:ref:`"memory management" <memory-management>`, and it is broken into two
related parts:

- :ref:`allocation <allocation>`: reserving a region in memory for use
- :ref:`deallocation <deallocation>`: marking that a formerly allocated region
  is now again free to be used for a future allocation. This is also called
  "freeing memory".

.. note::

   There are many techniques for tracking this information with different
   performance trade-offs, for the rest of this content we will treat all
   allocators (algorithms for managing allocated and freed memory) as
   equivalent.

Virtual Memory
--------------

So far we have been discussing programs as though they are the only things
running; however, modern computers allow many programs to be run seemingly at
the same time. In order to prevent programs from reading or writing memory in
use by another program, modern CPUs support a feature called :ref:`"virtual
memory" <virtual-memory>`. The way virtual memory works is a device intercepts
every memory read or write coming from the program and remaps it to a different
address in the physical :ref:`main memory <main-memory>` or :ref:`processor
cache <cache>`. This device is referred to as an :ref:`"MMU" <MMU>`, which
stands for "Memory Management Unit". Nowadays, this device is built directly
into the CPU itself as they are deeply ingrained.

The operating system issues instructions that tell the :ref:`MMU` which virtual
memory space the program will be operating in. Once that is done the operating
moves the :ref:`instruction pointer <instruction-pointer>` to the program and
your program begins executing. The :ref:`MMU` will prevent the program from
reading any address which the program has not been assigned, and will issue a
hardware fault, which brings execution back to the operating system, if an
invalid memory access occurs. This is what prevents any random program from
reading your browser's memory to steal your password. The :ref:`MMU` can also be
used to enforce read only or no execute (memory cannot be used to store
instructions) on given regions of memory.

Due to virtual memory, two programs running at the same time on the same machine
may believe that they have been given the same :ref:`address
<address>`. The :ref:`MMU` will know that process :math:`A` address :math:`N`
maps to physical address :math:`P`, but process :math:`B` address :math:`N` maps
to some different physical address :math:`Q`.

Two Tiers of Allocation
-----------------------

Because processes can only access the memory that the :ref:`MMU` and operating
system have given it, the program needs some way of requesting memory from the
operating system. Every operating system exposes this functionality to programs
in some way. It is expensive to switch execution between the program and the
operating system, so often programs request large blocks of memory at once. The
program will then implement it's own :ref:`allocation <allocation>` algorithm to
distribute this memory as it needs.

When the process requests a large block of memory to distribute internally, it
may not release that right away. Just like :ref:`allocation <allocation>`,
:ref:`deallocation <deallocation>` requires telling the operating system and
:ref:`MMU` that the process is done with the memory. This is similarly
expensive to allocation. Therefore, processes often defer this if possible. This
can make it very difficult to tell how much memory a complicated program like
Python or R is using.
