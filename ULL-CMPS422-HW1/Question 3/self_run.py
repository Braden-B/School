import csv
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

initialFile = pd.read_csv('Question3.csv')
transposedFile = initialFile.T
transposedFile.to_csv('transposed.csv', header = False, index = False)
file = open('transposed.csv')
reader = csv.reader(file, delimiter=',')
xValues = next(reader)
yValues = next(reader)
xPlot = [float(x) for x in xValues]
yPlot = [float(y) for y in yValues]
xValues = np.array(xValues) # transform the 1d array of X values into a 2d array with X in one column and weights of 1 in another
xValues = xValues.astype(float)
xValues = np.c_[xValues, np.ones(len(xValues))]
yValues = np.array(yValues)
yValues = yValues.astype(float)

Loss = np.linalg.inv(xValues.T @ xValues) @ (xValues.T @ yValues)
w, b = Loss[0],Loss[1]

t = np.arange(0,1.01, 0.01)
results = [w*x**2+b for x in t]

# Verification
MAE = 0
errorList = []
for x in range(len(xPlot)): # calculate MAE
    error = results[x-1] - yPlot[x-1]
    MAE += abs(error)
    errorList.append(error)

plt.plot(t, results, label="Model") # plot the data, results and a graph of the error
plt.plot(xPlot, yPlot, 'ro', label="Data")
plt.plot(t, errorList, label="Error")
plt.legend()
plt.show()

print(f"MAE: {MAE}")


