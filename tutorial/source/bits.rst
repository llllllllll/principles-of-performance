Bits
====

A :ref:`"bit" <bit>` is the most fundamental unit for storing information. It
may either be true, often denoted as 1, or false, often denoted as 0. While we
can only store two states in a single bit, if we group them together we can
store exponentially more information.

1 bit (2 states):

- 0
- 1

2 bits (4 states):

- 00
- 01
- 10
- 11

3 bits (8 states):

- 000
- 001
- 010
- 011
- 100
- 101
- 110
- 111

The number of states representable by :math:`n` bits is :math:`2^{n}`.

Representing Non-Negative Integers with Bits
--------------------------------------------

We can uniquely represent non-negative integers using just bits with the
following formula:

Let :math:`s` be the number of bits and let :math:`B` be the sequence of bits:

.. math::

   n = \sum_{i=1}^{s}{B_i2^{i - 1}}


For example, to represent 13 in 8 bits, we would need:

.. math::

   0(2^{7}) + 0(2^{6}) + 0(2^{5}) + 0(2^{4}) + 1(2^{3}) + 1(2^{2}) + 0(2^{1}) +
   1(2^{0})

which can be written out as: ``00001101``.

Addition with Bits
------------------

We can use the same algorithm for addition that we learned in elementary school.

To walk through an example, we will try to add 13 and 4:

::

     1101
   +  100
   -------

::

     1101
   +  100
   -------
        1     (0 + 1) = 1

::

     1101
   +  100
   -------
       01     (0 + 1) = 1
              (0 + 0) = 0

::

     1
     1101
   +  100
   -------
      001     (0 + 1) = 1
              (0 + 0) = 0
              (1 + 1) = 10 = 0 carry 1

::

    11
     1101
   +  100
   -------
     0001     (0 + 1) = 1
              (0 + 0) = 0
              (1 + 1) = 10 = 0 carry 1
              (1 + 1) = 10 = 0 carry 1

::

    11
     1101
   +  100
   -------
    10001     (0 + 1) = 1
              (0 + 0) = 0
              (1 + 1) = 10 = 0 carry 1
              (1 + 1) = 10 = 0 carry 1
              (1 + 0) = 1


Representing Negative Numbers
-----------------------------

Singed Magnitude
~~~~~~~~~~~~~~~~

Given that there are only two states for the sign of a number (positive or
negative), you could reserve a particular bit to denote the sign, and then use
the remaining bits to denote the magnitude of the value. For example, using 0 to
denote positive and 1 to denote negative, in 8 bits we can represent values in
the range:

::

   01111111 = +127

   11111111 = -127

Unfortunately, this representation allows multiple representations for 0:

::

   00000000 = +0
   10000000 = -0

This representation will also complicate the algorithms needed to perform
arithmetic with signed numbers.

Two's Complement
~~~~~~~~~~~~~~~~

In order to simplify arithmetic and produce a unique representation for each
number, most computers use two's complement to represent negative integers. To
find the two's complement representation of a negative number, take the absolute
value, add one, and then do a binary negation. A binary negation is where you
flip every true bit to false, and every false bit to true. Because there could
be an infinite number of leading zeroes to negate, we need to ahead of time
decide the number of bits we will be working with. This is known as the
:ref:`"width" <bit-width>` of an integer.

For example, to represent -17 in 8 bits using two's complement:

::

   x = -17
   abs(x) = 17
   17 + 1 = 18
   bin(17) = 00010010
   ~00010010 = 11101101


The two's complement representation allows us to implement subtraction by
implementing it as addition of the unsigned interpretation of the two's
complement value. For example, let's subtract 4 from 13. We will do this by
adding -4 to 13.

::

   bin(13) = 00001101
   bin(4)  = 00000100

To negate a number with two's complement representation, either positive or
negative) is done by inverting all of the bits and then adding one. So to get -4
we would do:

::

   bin(4)      = 00000100
   ~bin(4)     = 11111011
   ~bin(4) + 1 = 11111100

Then we would do our addition from before:

::

    111111
     00001101
   + 11111100
   --------------
    100001001

Which when interpreted in base ten is 265. If we take the last 8 bits of the
result we get: ``00001001 = 9``. We know to take the last 8 bits because that is
the bit width of the integers.
