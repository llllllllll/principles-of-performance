import pycallgrind

arr = list(range(10000))

with pycallgrind.callgrind('loop'):
    sum_ = 0
    for element in arr:
        sum_ += element
