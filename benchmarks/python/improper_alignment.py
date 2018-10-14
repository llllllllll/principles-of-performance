import numpy as np
import pycallgrind

arr = np.arange(10000 * 10000).reshape(10000, 10000)

with pycallgrind.callgrind('loop'):
    sum_ = arr.sum(axis=1)
