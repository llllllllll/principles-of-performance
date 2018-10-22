Python Overview
===============

.. note::

   Some of this content is specific to CPython, which is most common
   implementation of Python. This is the program that runs when you run ``$
   python`` in a terminal.

Python is a high level programming language, meaning that it is designed to
abstract away the details of the machine, and instead present a simpler
interface. The Python programming language provides a few important features
that make programming easier:

1. Automatic :ref:`Memory Management <memory-management>`.
2. Object oriented programming.
3. Dynamic typing.

Python Objects
--------------

In object oriented programming (OOP), :ref:`objects <object>` are values paired
with their operations. For example, to execute the code ``a + b``, we need to
inspect ``a`` at runtime and ask ``a`` how ``a`` it performs addition.

To store the behavior, Python has objects need to carry around a collection of
implementations for all of the operations they support in a way that may be
accessed dynamically. One way to do this, given a fixed set of operations which
may be performed, would be to use a :ref:`struct <struct>` to store the
addresses of the operations at fixed offsets from some base address. For
example:

.. code-block:: c

   struct type {
       pointer add_address;
       pointer sub_address;
       pointer mul_address;
       pointer div_address;
       ...
   };

Then, values can be a struct like:

.. code-block:: c

   struct value {
       pointer type;
       // type specific data goes here
   };

Because the size of each value differs depending on the type, which cannot be
known ahead of time because Python is dynamically typed, Python just refers to
all objects through a pointer to the ``value`` struct. All we know is that the
first member of the ``value`` struct will be a pointer to some collection of
functions which will be designed to know the true size of the object and how to
interpret the data. This means that at minimum we must do one :ref:`memory
dereference <dereference>` to perform any operation on a Python object.

Using this model, let's walk through the execution of:

.. code-block:: python

   a + b

1. :Ref:`Dereference <dereference>` ``a``.
2. :Ref:`Dereference <dereference>` ``a``\'s type.
3. Jump to the implementation of ``add`` for the type of a.
4. :Ref:`Dereference <dereference>` ``b``
5. Check if the type of ``b`` can be added to the type of ``a``.
   - If not, throw an exception.
6. :ref:`Allocate <allocation>` memory to store the result of the addition.
7. Perform the addition and store the result in the newly allocated memory.

Here is what all of the memory :ref:`dereferences <dereference>` look like for
``5 + 3``.

.. image:: _static/addition-dereferences.png

Overhead
~~~~~~~~

All of this extra "pointer chasing", runtime type checking, and allocation
*really* adds up. For example, let's inspect a simple dot product function:

.. code-block:: python

   def dot(xs, ys):
       out = 0
       ix = 0
       while ix < len(xs):
           x = xs[ix]
           y = ys[ix]
           out += x * y
           ix += 1
       return out

Let's see how this function performs:

.. code-block:: ipython

   In [2]: xs = [1, 2, 3]

   In [3]: ys = [4, 5, 6]

   In [4]: dot(xs, ys)
   Out[4]: 32

   In [5]: 1 * 4 + 2 * 5 + 3 * 6
   Out[5]: 32

   In [7]: xs = [random.random() for _ in range(10000)]

   In [8]: ys = [random.random() for _ in range(10000)]

   In [9]: dot(xs, ys)
   Out[9]: 2493.0449981169236

   In [10]: %timeit dot(xs, ys)
   1.52 ms ± 15.4 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)

1.5 milliseconds to take the dot product of 10000 elements, that seems pretty
quick, but what about a more pythonic implementation of ``dot``?

.. code-block:: python

   def pythonic_dot(xs, ys):
       return sum(x * y for x, y in zip(xs, ys))

.. code-block:: ipython

   In [12]: %timeit pythonic_dot(xs, ys)
   552 µs ± 8.65 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)

This function is shorter and better expresses our intent. It is also
considerably faster, why is that? In short, Python's built in function like
``zip`` and ``sum`` take advantage of the repetition of accessing
elements. Instead of constantly checking the object and saying, "how should I
retrieve elements from you", it asks the question once and re-uses the answer
many times. This reduces the over all number of memory accesses and instructions
needed.
