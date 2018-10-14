import numpy as np


def rolling_sum(window_size, array):
    out = []
    for n in range(len(array) - window_size + 1):
        window = array[n:n + window_size]
        out.append(np.sum(window))

    return np.array(out)


if __name__ == '__main__':
    import cProfile

    array = np.random.random(10000)
    window_size = 20

    p = cProfile.Profile()
    p.enable()

    rolling_sum(20, array)

    p.disable()
    p.dump_stats('rolling_sum.stats')
