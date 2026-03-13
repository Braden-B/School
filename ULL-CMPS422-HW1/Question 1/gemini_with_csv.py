import csv
import time

start_time = time.time_ns()
# 1. Start the runtime timer
filename = "sensor.csv"
# 2. Read from the CSV file (No hardcoding)
x_vals = []
r_vals = []

try:
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        data = list(reader)

        # Row 0 contains X values (skipping the first header element 'X')
        x_vals = [float(val) for val in data[0][1:] if val.strip()]
        # Row 1 contains r labels (skipping the first header element 'r')
        r_vals = [val.strip() for val in data[1][1:] if val.strip()]

except FileNotFoundError:
    print(f"Error: '{filename}' not found. Make sure the file is in the same directory.")

# 3. State our assumption explicitly
assumption_text = "Assumption: IF X >= w0 THEN 'signal', ELSE 'noise'"

best_w0 = 0.0
max_correct = -1
total_samples = len(x_vals)

# 4. Iterative heuristic search (t = 0.01 to 1.90 in 0.01 steps)
# Using integer range divided by 100 to avoid floating point precision drift
for t_step in range(1, 191):
    w0 = t_step / 100.0
    correct_predictions = 0

    # Test the current w0 against all samples using our fixed assumption
    for i in range(total_samples):
        predicted_class = 'signal' if x_vals[i] >= w0 else 'noise'

        if predicted_class == r_vals[i]:
            correct_predictions += 1

    # Keep track of the w0 that yields the highest accuracy
    if correct_predictions > max_correct:
        max_correct = correct_predictions
        best_w0 = w0

# 5. Stop the timer

# 6. Output the results
print(assumption_text)
print("-" * 50)
print(f"Best decision boundary (w0) : {best_w0:.2f}")
print(f"Maximum correct predictions : {max_correct} out of {total_samples}")
print(f"Best Classifier Accuracy    : {(max_correct / total_samples) * 100:.2f}%")
print(f"Process Run Time            : {((time.time_ns() - start_time)/1000)} ms")
