#!/bin/python3

import math
import os
import random
import re
import sys
import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression

def read_dataframe():
    # Return a pandas dataframe from stdin
    return pd.read_csv(sys.stdin)

def read_matrix():
    # Return column names and data as a matrix
    df = read_dataframe()
    return list(df.columns), df.values

def read_list():
    # Return column names and data as a list of lists
    # Each element in the list corresponds to columns in the data
    col_names, val = read_matrix()
    return col_names, val.T.tolist()

import random
from sklearn.metrics import r2_score as r2
import time

towns, data_map = {}, {}
nyc_temp = 0

def calc(used):
    global data_map, nyc_temp
    towns_temp = np.array([data_map[town] for town in used]).T
    reg = LinearRegression().fit(towns_temp, nyc_temp)
    pred_temp = reg.predict(towns_temp)
    cur_r2 = (r2(nyc_temp, pred_temp), ','.join(used))
    print(cur_r2)
    return cur_r2

def rand():
    global towns
    start = time.time()
    print('start', start)
    used = random.sample(towns, 5)
    max_r2 = calc(used)
    cycs = 1
    while (time.time() - start) / cycs * (cycs + 1) < 10:
        print('est', (time.time() - start) / cycs)
        print('cur', time.time())
        used = random.sample(towns, 5)
        max_r2 = max(max_r2, calc(used))
    return max_r2

def bash(used = [], prev = -1):
    global towns
    if len(used) == 5:
        return calc(used)
    max_r2 = (0, 'N/A')
    for i in range(prev + 1, len(towns)):
        max_r2 = max(max_r2, bash(used + [towns[i]], i))
    return max_r2

def greedy():
    global towns
    ref = []
    for town in towns:
        ref += [calc([town])]
    ref.sort(reverse=True)
    print(ref)
    return (sum([ref[i][0] for i in range(5)]), ','.join([ref[i][1] for i in range(5)]))
    
def main():
    global towns, data_map, nyc_temp, adj
    data = read_list()
    towns = list(data[0])
    towns.remove('NYC')
    day_count = len(data[1][0])
    data = list(map(list, zip(*data)))
    for town_data in data:
        data_map[town_data[0]] = town_data[1]
    nyc_temp = np.array(data_map['NYC']).reshape(-1, 1)
    rv = rand()
    print('rv', rv)
    return rv[1]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    result = main()

    fptr.write(result + '\n')

    fptr.close()
