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

from sklearn.metrics import mean_squared_error as mse

#
# Complete the 'main' function below. 
# You can use the functions read_dataframe, read_matrix, 
# or read_list to read data from stdin.
#
# The function is expected to return a STRING.

def main():
    # init
    # print('===INIT===')
    data = read_list()
    day_count = len(data[1][0])
    # print(data)
    # print(day_count)
    # transpose
    data = list(map(list, zip(*data)))
    # convert to map
    data_map = {}
    for town_data in data:
        data_map[town_data[0]] = town_data[1]
    # print(data_map)
    # q1
    # print('===Q1===')
    max_var = (-1, 'N/A')
    for town in data_map:
        print(town, np.var(data_map[town]))
        max_var = max(max_var, (np.var(data_map[town]), town))
    q1 = max_var[1]
    # q2
    # print('===Q2===')
    # find median according to constraints
    q2 = str(round(np.median([
            data_map['NYC'][i] for i in range(day_count)
            if data_map['Town2'][i] >= 90 and data_map['Town2'][i] <= 100
        ])))
    # q3
    # print('===Q3===')
    q3 = 0
    # format data as required for sklearn
    nyc_temp = np.array(data_map['NYC']).reshape(-1, 1)
    regs = {}
    # print('NYC', nyc_temp)
    for town in data_map:
        # we aren't using nyc temp to predict nyc temp
        if town == 'NYC':
            continue
        # format data as required for sklearn
        town_temp = np.array(data_map[town]).reshape(-1, 1)
        # print(town, town_temp)
        # typical sklearn linear regression implementation
        reg = LinearRegression().fit(town_temp, nyc_temp)
        # print(reg.coef_)
        q3 += abs(reg.coef_[0][0])
        # save regression for q4
        regs[town] = reg
    q3 = str(round(q3))
    # q4
    # print('===Q4===')
    min_mse = (np.inf, 'N/A')
    for town in regs:
        town_temp = np.array(data_map[town]).reshape(-1, 1)
        pred_temp = regs[town].predict(town_temp)
        # print(town, pred_temp, mse(nyc_temp, pred_temp))
        min_mse = min(min_mse, (mse(nyc_temp, pred_temp), town))
    q4 = min_mse[1]
    # q5
    # print('===Q5===')
    min_mse2 = (np.inf, 'N/A')
    for town1 in regs:
        for town2 in regs:
            # to avoid wasting time
            if town1 <= town2:
                continue
            # print(town1,town2)
            towns_temp = np.array([data_map[town1],data_map[town2]]).T
            # print(town_temp)
            reg = LinearRegression().fit(towns_temp, nyc_temp)
            pred_temp = reg.predict(towns_temp)
            # print(pred_temp)
            cur_mse = (mse(nyc_temp, pred_temp), ','.join([town1,town2]))
            # print(cur_mse)
            min_mse2 = min(min_mse2, cur_mse)
    q5 = min_mse2[1]
    # exit
    # print(q1,q2,q3,q4,q5)
    return ','.join([q1,q2,q3,q4,q5])

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    result = main()

    if result is None:
        result = ''

    fptr.write(result + '\n')

    fptr.close()