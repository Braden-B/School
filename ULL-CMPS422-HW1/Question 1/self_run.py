import csv
import time
import numpy as np


startTime = time.time_ns()

file = open("sensor.csv")
reader = csv.reader(file)
inputValue = next(reader)
inputValue = inputValue[1:] # just the input values for testing, removes x
testValue = next(reader)
testValue = testValue[1:] # just the results for checking, removes r
file.close()

predicted = np.empty((190, inputValue.__sizeof__()), dtype=object) # 2-D array to track the predictions for our x values.
results = []     # a 1-D array tracking the results from iteration to iteration. The index is x*100-1
sensitivity = [] # sensitivity tracking
fOneScore = [] # F-1 score tracking

pos_x, pos_y = 0, 0 # position within predicted

correctCount, truePositive, trueNegative, falsePositive, falseNegative = 0,0,0,0,0 # for tallying within results

maxCorrect, index = -1, -1 # dummy maximum value and index

for i in np.arange(0.01, 1.90, 0.01):
    while pos_x < 20:
        element=float(inputValue[pos_x])
        if element < i:
            predicted[pos_y, pos_x] = "noise"
        if element >= i:
            predicted[pos_y, pos_x] = "signal"
        pos_x += 1
    pos_x = 0 # reset for next iteration
    # now to check for correct
    while pos_x < 20:
        predictedResult = predicted[pos_y, pos_x]
        actualResult = testValue[pos_x]
        if predictedResult == actualResult:
            correctCount += 1
            if predictedResult == "noise":
                trueNegative += 1
            else:
                truePositive += 1
        elif predictedResult == "noise" and actualResult == "signal":
            falseNegative += 1
        else:
            falsePositive += 1
        pos_x += 1
    # and store
    results.append(correctCount)
    sensitivity.append(truePositive / (truePositive + falseNegative))
    fOneScore.append(2*truePositive / (2*truePositive + falsePositive + falseNegative))
    pos_y += 1
    pos_x = 0 # set pos_y for next row, reset pos_x
    correctCount, truePositive, trueNegative, falsePositive, falseNegative = 0, 0, 0, 0, 0

    for i in range(len(results)):
        if results[i] > maxCorrect:
            maxCorrect = results[i]
            index = i
            if i > index: # this chooses the highest valued index
                index = i
    print(f"Max Correct: {maxCorrect}")
    print(f"Accuracy: {(maxCorrect / 20) * 100}%")
    print(f"Index: {index}")
    print(f"X-Value: {(index - 1) / 100}") # does make index 0 appear as -0.01 for a few iterations
    print(f"Sensitivity {sensitivity[index]}")
    print(f"F-Score: {fOneScore[index]}")

print(f"Max Correct: {maxCorrect}")
print(f"Accuracy: {(maxCorrect/20)*100}%")
print(f"Index: {index}")
print(f"X-Value: {(index-1)/100}")
print(f"Time(ms): {((time.time_ns()-startTime)/1000000)}")






