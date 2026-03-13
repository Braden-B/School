import csv
import time

start_time = time.time_ns()
# ─────────────────────────────────────────────
# 1. Read sensor.csv manually (no sklearn, etc.)
# ─────────────────────────────────────────────
X_vals = []
labels = []

with open("sensor.csv", "r") as f:
    reader = csv.reader(f)
    rows = list(reader)

# Row 0: header "X" followed by float values
# Row 1: header "r" followed by class labels
X_vals = [float(v) for v in rows[0][1:]]
labels = [v.strip() for v in rows[1][1:]]

print("Loaded data:")
for x, r in zip(X_vals, labels):
    print(f"  x={x:.2f}  label={r}")

# ─────────────────────────────────────────────
# 2. Heuristic classifier
#
# Decision rule (vertical line):  x = w
#
# Assumption being tested:
#   LEFT  side (x <  w)  → predicted as "noise"
#   RIGHT side (x >= w)  → predicted as "signal"
#
# At every t we also evaluate the *flipped* assumption:
#   LEFT  → "signal", RIGHT → "noise"
# and keep whichever yields more correct predictions.
#
# This is necessary because we don't know in advance
# which side of the line corresponds to which class.
# ─────────────────────────────────────────────

best_accuracy  = -1.0
best_w         = None
best_assumption = None  # "left=noise" or "left=signal"

n = len(X_vals)

# Helper: count correct predictions given a rule
def evaluate(w, left_class):
    right_class = "signal" if left_class == "noise" else "noise"
    correct = 0
    for x, true_label in zip(X_vals, labels):
        predicted = left_class if x < w else right_class
        if predicted == true_label:
            correct += 1
    return correct / n  # accuracy as a fraction

# ─────────────────────────────────────────────
# 3. Iterate t = 0.01 to 1.90 in steps of 0.01
# ─────────────────────────────────────────────
print("\n--- Searching for best w ---")
print(f"{'t (w)':>8}  {'Acc(left=noise)':>16}  {'Acc(left=signal)':>17}")

t = 0.01
results = []

while round(t, 10) <= 1.90:
    w = t

    acc_A = evaluate(w, left_class="noise")   # Assumption A
    acc_B = evaluate(w, left_class="signal")  # Assumption B (flipped)

    results.append((round(w, 2), acc_A, acc_B))

    # Track global best across both assumptions
    if acc_A >= best_accuracy:
        best_accuracy   = acc_A
        best_w          = w
        best_assumption = "left=noise, right=signal"

    if acc_B > best_accuracy:
        best_accuracy   = acc_B
        best_w          = w
        best_assumption = "left=signal, right=noise"

    t = round(t + 0.01, 10)

# Print a condensed view (every 10th step) to avoid flooding output
for i, (w, aA, aB) in enumerate(results):
    if i % 10 == 0 or aA == best_accuracy or aB == best_accuracy:
        marker = " ← BEST" if (round(w,2) == round(best_w,2)) else ""
        print(f"  w={w:>5.2f}   left=noise: {aA:.4f}   left=signal: {aB:.4f}{marker}")

# ─────────────────────────────────────────────
# 4. Report result
# ─────────────────────────────────────────────
print("\n════════════════════════════════════════")
print(f"  Best  w (decision boundary) : {best_w:.2f}")
print(f"  Best assumption             : {best_assumption}")
print(f"  Best accuracy               : {best_accuracy*100:.1f}%")
print("════════════════════════════════════════")

# ─────────────────────────────────────────────
# 5. Show final classification at best w
# ─────────────────────────────────────────────
left_cls  = "noise"  if "left=noise"  in best_assumption else "signal"
right_cls = "signal" if left_cls == "noise" else "noise"

print(f"\nClassification at w = {best_w:.2f}  "
      f"(x < w → {left_cls}, x >= w → {right_cls}):\n")
print(f"  {'x':>6}  {'True':>8}  {'Predicted':>10}  {'Correct?':>8}")
print("  " + "-"*38)
correct_count = 0
for x, true_label in zip(X_vals, labels):
    predicted = left_cls if x < best_w else right_cls
    ok = "✓" if predicted == true_label else "✗"
    if predicted == true_label:
        correct_count += 1
    print(f"  {x:>6.2f}  {true_label:>8}  {predicted:>10}  {ok:>8}")

print(f"\n  Correctly classified: {correct_count}/{n} = {correct_count/n*100:.1f}%")
print((time.time_ns()-start_time)/1000)