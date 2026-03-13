import csv
import time
import numpy as np

t, t_max, t_step = 0.01, 1.90, 0.01 # for custom looping
leastLoss, leastLossX= 1.0,2.0 # Loss is set to a range of 0-1
incorrectCount = 0
loss = []
actualResult = []

file = open("sensor.csv")
reader = csv.reader(file)
inputValue = next(reader)
inputValue = inputValue[1:]  # just the input values for testing, removes x
testValue = next(reader)
testValue = testValue[1:]  # just the results for checking, removes r
file.close()

predicted = np.empty((190, inputValue.__sizeof__()),
                     dtype=object)  # 2-D array to track the predictions for our x values.
results = []  # a 1-D array tracking the results from iteration to iteration. The index is x*100-1

pos_x, pos_y = 0, 0  # position within predicted

maxCorrect, index = -1, -1  # dummy maximum value and index

for i in np.arange(0.01, 1.90, 0.01):
    while pos_x < len(inputValue):
        element = float(inputValue[pos_x])
        if element < i:
            predicted[pos_y, pos_x] = 0
        if element >= i:
            predicted[pos_y, pos_x] = 1
        pos_x += 1
    pos_x = 0  # reset for next iteration
    # now to check for loss and total
    for x in testValue:
        if x == "noise":
            actualResult.append(0)
        else:
            actualResult.append(1)
    while pos_x < len(inputValue):
        predictedResult = predicted[pos_y, pos_x]
        if predictedResult != actualResult[pos_x]:
            incorrectCount += 1
        pos_x += 1
    # and store
    MAE = incorrectCount/len(inputValue)
    loss.append(MAE) # add to our list of loss
    if MAE < leastLoss:
        leastLoss = MAE
        leastLossX = i
    pos_y += 1
    pos_x = 0  # set pos_y for next row, reset pos_x
    print(f"Loss: {MAE:.4f}")
    print(f"Incorrect: {incorrectCount}/{len(inputValue)}")
    print(f"Position: {i}")
    MAE = 0
    incorrectCount = 0

print(f"Least Loss: {leastLoss:.4f}")
print(f"Least Loss X: {leastLossX:.4f}")