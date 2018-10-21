Principles of Performance
=========================

Today the quant finance and fintech sectors attract top talent from a wide range
of quantitative academic backgrounds, often outside of traditional computer
science. While this diversity has been advantageous in many respects, these
students and professionals can often find themselves mired by performance
related issues when they take their analyses from the classroom setting to the
marketplace and have to interface with real world data structures at scale. This
tutorial will cover the basic foundational concepts needed to effectively design
and implement scalable algorithms like those common to quant finance or related
financial technology applications.

Many common performance issues are rooted in a lack of knowledge about how a
computer actually performs computation. We will begin by covering how modern
computers physically execute code. This low level information will help us
reason about the behavior of our high level code later. We will then look at
Python's execution model with our new understanding of the machine. We will then
discuss how numpy allows us to take full advantage of the power of our computer
while staying in Python. Finally, we will look at tools for analyzing the
performance of Python programs and cover common issues and fixes.

By the end of this session, attendees will:

- Have a general understanding of how the processor works.
- Know about memory management and cache locality.
- Understand the reason Python is "slow".
- Understand how numpy makes Python fast.
- Be familiar with using cProfile to analyze programs.

Install Steps
-------------

Prior to the tutorial, attendees need to install a git and Python 3.6. After
that, run the following commands.

.. code-block:: bash

   $ git clone --recursive https://github.com/llllllllll/principles-of-performance.git
   $ cd principles-of-performance
   $ source etc/setup-env

The ``setup-env`` script will attempt to download the needed packages.
The ``setup-env`` should print a lot of stuff to the terminal. You can ignore
most of it but the last line should be:

.. code-block:: text

   Environment is setup correctly!

Viewing the Tutorial
--------------------

The tutorial is structured as a sphinx project. This allows the tutorial to be
viewed from a standard browser or hosted online.

The material can be viewed in a browser by opening
``tutorial/build/html/index.html``, for example:

.. code-block:: bash

   $ ${BROWSER} tutorial/build/html/index.html

Acknowledgments
---------------

The numpy examples are sourced from Scott Sanderson's
https://github.com/ssanderson/foundations-of-numerical-computing
