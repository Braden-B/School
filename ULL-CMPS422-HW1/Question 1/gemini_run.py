import pandas as pd
import numpy as np
import time

startTime = time.time_ns()

def find_best_classification_line():
    # 1. Allow a spot for input of a csv file name
    file_name = ("sensor.csv")

    try:
        # 2. Read the CSV file.
        # Note: The prompt mentions the file contains "two rows". If the data is strictly
        # in 2 rows instead of 2 columns, we read it without headers and transpose it (.T)
        df = pd.read_csv(file_name, header=None)

        # If your data is in columns rather than rows, you can remove the '.T' below.
        if df.shape[0] == 2:
            df = df.T

            # Extract features (x) and actual labels (y)
        # Assuming index 0 is the sensor data value and index 1 is the actual label
        x = df.iloc[:, 0].astype(float).values
        y = df.iloc[:, 1].values

        # Convert string labels to binary if necessary (Assuming 1 for Signal, 0 for Noise)
        # Adjust 'Signal' / 'Noise' depending on the exact string used in your CSV
        if isinstance(y[0], str):
            y = np.where(y == 'Signal', 1, 0)

        # 3. State and lock the Assumption
        # We assume that the right side of the vertical line (values >= t) is Signal (1)
        # and the left side of the vertical line (values < t) is Noise (0).
        print("-" * 50)
        print("ASSUMPTION SET:")
        print("Right side of line (x >= t) -> Classified as 'Signal' (1)")
        print("Left side of line  (x < t)  -> Classified as 'Noise' (0)")
        print("-" * 50)

        best_t = None
        best_accuracy = -1

        # 4. Iterative heuristic search
        # for t = 0.01 : 0.01 : 1.90
        # We use np.arange(0.01, 1.91, 0.01) to safely include 1.90 with floating point math
        for t in np.arange(0.01, 1.91, 0.01):

            # Apply our established assumption
            predictions = np.where(x >= t, 1, 0)

            # Evaluate the accuracy
            correct_predictions = np.sum(predictions == y)
            accuracy = correct_predictions / len(y)

            # Check if this t yields a better separation
            if accuracy > best_accuracy:
                best_accuracy = accuracy
                best_t = t

        # 5. Output the results
        print(f"\nSearch complete!")
        print(f"Best Decision Line (Vertical Threshold): t = {best_t:.2f}")
        print(f"Maximum Accuracy Achieved: {best_accuracy * 100:.2f}%")

    except FileNotFoundError:
        print(f"Error: The file '{file_name}' was not found. Please ensure it is in the same directory.")
    except Exception as e:
        print(f"An error occurred while processing the file: {e}")

    print((time.time_ns()-startTime)/1000)

if __name__ == "__main__":
    find_best_classification_line()