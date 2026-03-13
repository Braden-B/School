import pandas as pd
import numpy as np
import time


def heuristic_classifier(file_path):
    # 1. Start the timer
    start_time = time.time()

    # 2. Read the CSV file
    # Assuming the data has no header and contains 2 rows.
    # The instructions note: "first being the id that must be removed"
    # If it's literally rows, we read it and drop the first row/column accordingly.
    try:
        df = pd.read_csv(file_path, header=None)
    except FileNotFoundError:
        print(f"Error: {file_path} not found.")
        return

    # Assuming row 0 is ID, row 1 is Training Data (x), row 2 is Label (y)
    # Wait, the prompt states it contains 2 rows: training set and actual label.
    # But then says "first being the id that must be removed".
    # Let's assume Row 0 is ID, Row 1 is Data, Row 2 is Label.
    # If the file strictly has exactly 2 rows (Data and Label) but the first COLUMN is ID:
    # We will slice off the first column (index 0).

    # Let's drop the first column assuming it is the ID
    df = df.iloc[:, 1:]

    # Extract training data and labels
    # Using the assumption that row 0 is training data and row 1 is the actual label
    X = df.iloc[0].values.astype(float)
    y_true = df.iloc[1].values.astype(int)  # Assuming labels are 0 (noise) and 1 (signal)

    # 3. Setup the heuristic search parameters
    best_t = 0
    best_accuracy = -1
    best_predictions = []

    # 4. Iterative search for the best threshold 't'
    # Pseudo code: for t = 0.01 : 0.01 : 1.90
    # We use numpy's arange to handle floating point steps safely
    t_values = np.arange(0.01, 1.91, 0.01)

    for t in t_values:
        # Apply Assumption:
        # If value > t -> Class 1 (Signal)
        # If value <= t -> Class 0 (Noise)
        y_pred = (X > t).astype(int)

        # Calculate accuracy (comparing predictions to actual labels)
        correct_predictions = np.sum(y_pred == y_true)
        accuracy = correct_predictions / len(y_true)

        # Update best values if current t gives better accuracy
        if accuracy > best_accuracy:
            best_accuracy = accuracy
            best_t = t
            best_predictions = y_pred

    # 5. Stop the timer
    end_time = time.time()
    runtime = end_time - start_time

    # 6. Output the results
    print("----- Classification Results -----")
    print(f"Assumption:   x > t is Signal (1), x <= t is Noise (0)")
    print(f"Best Line:    x = {best_t:.2f}")
    print(f"Best Accuracy:{best_accuracy * 100:.2f}%")
    print(f"Process Time: {runtime:.6f} seconds")


# Run the function
if __name__ == "__main__":
    heuristic_classifier('sensor.csv')