import numpy as np


def _rolling_windows(window_size, array):
    orig_shape = array.shape
    if not orig_shape:
        raise IndexError("Can't restride a scalar.")
    elif orig_shape[0] <= window_size:
        raise IndexError(
            "Can't restride array of shape {shape} with"
            " a window length of {len}".format(
                shape=orig_shape,
                len=window_size,
            )
        )

    num_windows = (orig_shape[0] - window_size + 1)
    new_shape = (num_windows, window_size) + orig_shape[1:]

    new_strides = (array.strides[0],) + array.strides

    return np.ndarray(
        dtype=array.dtype,
        shape=new_shape,
        buffer=array,
        strides=new_strides,
    )


def rolling_sum(window_size, array):
    windows = _rolling_windows(window_size, array)
    return np.sum(windows, axis=1)


if __name__ == '__main__':
    import cProfile

    array = np.random.random(10000)
    window_size = 20

    p = cProfile.Profile()
    p.enable()

    rolling_sum(20, array)

    p.disable()
    p.dump_stats('rolling_sum.stats')
