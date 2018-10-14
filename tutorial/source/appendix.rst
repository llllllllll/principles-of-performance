Appendix
========

Processor
---------

.. _CPU:

CPU
~~~

The CPU is the device that physically executes :ref:`instructions <instruction>`
to perform computation.

.. _mmu:

MMU
~~~

The MMU which stands for "Memory Management Unit". Nowadays, is a component that
intercepts every memory read or write coming from the program and remaps it from
the :ref:`virtual address <virtual-memory>` to the physical :ref:`main memory
<main-memory>` or :ref:`processor cache <cache>`. The MMU is also responsible
for enforcing that programs only access the memory they have been given so that
programs do not use other program's memory.

.. _virtual-memory:

Virtual Memory
~~~~~~~~~~~~~~

Virtual memory is a way of isolating the memory used by different programs
running on the same machine at the same time. Basically, each program sees a
subset of total memory available on the machine. The process can only read or
write address inside this space.

.. _x86:

x86
~~~

By far the most common instruction set architecture for personal computers and
servers. The instruction set architecture defines which :ref:`instructions
<instruction>` exist for the machine.

CPU
~~~

The CPU is the device that reads :ref:`instructions <instruction>`, interprets
the meaning, and performs the given computation. This is the component of the
computer that implements all of the logic.

.. _instruction:

Instruction
~~~~~~~~~~~

A single low level step that the computer can execute. This is the pair of the
operation along with the arguments to the operation.

.. _instruction-pointer:

Instruction Pointer
~~~~~~~~~~~~~~~~~~~

A special :ref:`register <register>` which stores the :ref:`address <address>`
of the next instruction to execute. The programmer cannot directly manipulate
this register.

.. _opcode:

Opcode
~~~~~~

A particular operation that the computer can execute decoupled from the
arguments. For example ``add`` or ``sub``.

.. _register:

Register
~~~~~~~~

A location to store a small value while performing operations. Except for
:ref:`mov`, most :ref:`instructions <instruction>` take registers for all inputs
and outputs. Registers live on the :ref:`CPU` itself, not in :ref:`memory
<main-memory>`.

.. _bitness:

Bitness
~~~~~~~

The number of bits in a value.

.. _word-size:

Word Size
~~~~~~~~~

The word size is the size of a :ref:`register <register>` on the
machine. However, "word" is often overloaded to mean 16 bit value. This comes
from the fact that the original :ref:`x86` processors were 16 bit. This is the
root of the terms:

- ``dword``: double word, 32 bit value
- ``qword``: quadruple word, 64 bit value

.. _mov:

``mov``
~~~~~~~

``mov`` is the :ref:`instruction <instruction>` that can load data from
:ref:`memory <main-memory>` into a :ref:`register <register>` or write data
from a :ref:`register <register>` back to :ref:`memory <main-memory>`.

Memory
------

.. _bit:

Bit
~~~

The most primitive unit for storing information, either true or false. Bits are
often denoted using 1 for true or 0 for false.

.. _byte:

Byte
~~~~

The smallest addressable number of :ref:`bits <bit>`. This is almost always
eight bits.

.. _memory-management:

Memory Management
~~~~~~~~~~~~~~~~~

Memory management is tracking which :ref:`addresses <address>` are in use so
that data is not overwritten while it is being used. This involves properly
:ref:`allocating <allocation>` and :ref:`deallocating <deallocation>` memory.

.. _allocation:

Allocation
~~~~~~~~~~

To allocate memory is reserve a section of memory for some period of time.

.. note:: See Also

   :ref:`deallocation`

.. _deallocation:

Deallocation
~~~~~~~~~~~~

To deallocate memory is to mark that previously :ref:`allocated <allocation>`
region of memory is no longer needed and can be reused in the future.

.. note:: See Also

   :ref:`allocation`

.. _address:

Address
~~~~~~~

An address is an integer which corresponds to a location in :ref:`memory
<main-memory>`.

.. _pointer:

Pointer
~~~~~~~

A pointer is a value that stores a :ref:`memory address <address>`. This can
either be the address of a single value, an :ref:`array <array>`, or a
:ref:`struct <struct>`.

.. _dereference:

Dereference
~~~~~~~~~~~

To "dereference" means to read the value stored at a particular :ref:`address
<address>`. For example, given memory that looks like:

.. code-block:: python

   memory = [1, 5, 3, 4, 5, 2, 8, 3]

Dereferencing address 4 (0-indexed) would be: ``memory[4] == 5``.

.. _bit-width:

Integer Width
~~~~~~~~~~~~~

The fixed number of :ref:`bits <bit>` in an integer. The common widths for
integers are: 8, 16, 32, and 64.

.. _main-memory:

Main Memory
~~~~~~~~~~~

Main memory, also just called "memory" or "RAM", is ephemeral storage available
to the processor for storing results of computations. This does not include
persistent storage like hard drives.

.. _l1:
.. _cache:

Processor Cache
~~~~~~~~~~~~~~~

The processor cache is a series of caches that reside on the :ref:`CPU`
itself. These caches are arranged from smallest and fastest to access to largest
and slowest to access. The common naming convention is:

- ``L1``: smallest and fastest
- ``L3`` or ``L4`` (depending on CPU): largest and slowest
- ``LL``: Last Level, always refers to the last level regardless of how many
  levels exist.

Often the ``L1`` cache is split into two distinct caches: one for instructions
and one for data.

.. _LL:

``LL``
~~~~~~

``LL``, short for "Last Level", always refers to the largest and slowest
:ref:`memory cache <cache>` level for a given machine.

.. _cache-line:

Cache Line
~~~~~~~~~~

A cache line is the unit of data transfer between :ref:`main memory
<main-memory>` and the :ref:`processor cache <cache>`, or between levels of the
cache. Instead of moving one byte at a time, movement is accelerated 

Data Structures
---------------

.. _array:

Array
~~~~~

An array is an ordered sequence of values. The defining characteristic of an
array is that the values are laid out next to each other in :ref:`memory
<main-memory>`. For example if the elements are 4 byte integers, and the first
element has an address of ``addr``, then the second element will have an address
of ``add + 4``, the third element will have an address of ``addr + 8``, and so
on. The address of element ``n`` of any array ``a`` is ``a + sizeof(element) *
n``. Element ``n`` of array ``a`` is often denoted as: ``a[n]``.

.. _struct:

Struct
~~~~~~

A struct, short for "structure", is a fixed-size collection of potentially
unrelated types. In a structure, the elements are laid out in a fixed order, for
example, imagine the struct:

.. code-block:: c

   {
       int32 a
       int8 b;
       int16 c;
   }

The bytes could be laid out like:

.. code-block:: python

   [a[0], a[1], a[2], a[3], b[0], c[0], c[1]]

though, for alignment reasons it could also be laid out like:

.. code-block:: python

   [a[0], a[1], a[2], a[3], b[0], padding, c[0], c[1]]

where padding is a wasted byte that serves to make the address of ``c`` a
multiple of 2.

Miscellaneous
-------------

.. _object:

Object
~~~~~~

An object, in terms of object oriented programming, is a value paired with the
set of operations that may be performed on the value.

.. _profiler:

Profiler
~~~~~~~~

A profiler is a tool that tracks the execution of a program to better understand
the behavior and performance of the program.
