import pandas as pd
import numpy as np

xy = np.arange(1, 1001)
log = np.log2(xy)
x2 = (xy / 200) ** 2

pd.DataFrame({
    '$O(n)$': xy / 50,
    '$O(ln(n))$': log,
    '$O(x^2)$': x2,
}).plot()