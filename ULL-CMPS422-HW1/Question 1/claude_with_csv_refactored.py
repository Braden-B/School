import csv
import time
# --- Load data ---
start_time = time.time_ns()
with open("sensor.csv", "r") as f:
    rows = list(csv.reader(f))

X_vals = [float(v) for v in rows[0][1:]]
labels = [v.strip() for v in rows[1][1:]]
n = len(X_vals)

# --- Evaluate accuracy for a given threshold and left-side class ---
def evaluate(w, left_class):
    right_class = "signal" if left_class == "noise" else "noise"
    return sum(
        (left_class if x < w else right_class) == lbl
        for x, lbl in zip(X_vals, labels)
    ) / n

# --- Search: t = 0.01 to 1.90 in steps of 0.01 ---
best_accuracy, best_w, best_assumption = -1.0, None, None

t = 0.01
while round(t, 10) <= 1.90:
    for left_cls in ("noise", "signal"):
        acc = evaluate(t, left_cls)
        if acc > best_accuracy:
            best_accuracy  = acc
            best_w         = t
            best_assumption = f"left={left_cls}"
    t = round(t + 0.01, 10)

# --- Report ---
left_cls  = "noise" if "left=noise" in best_assumption else "signal"
right_cls = "signal" if left_cls == "noise" else "noise"

print(f"Best w={best_w:.2f} | {left_cls} if x<w, {right_cls} if x>=w | accuracy={best_accuracy*100:.1f}%\n")
print(f"  {'x':>6}  {'True':>8}  {'Predicted':>10}  Match")
print("  " + "-"*36)
for x, lbl in zip(X_vals, labels):
    pred = left_cls if x < best_w else right_cls
    print(f"  {x:>6.2f}  {lbl:>8}  {pred:>10}  {'✓' if pred == lbl else '✗'}")

print((time.time_ns()-start_time)/1000)