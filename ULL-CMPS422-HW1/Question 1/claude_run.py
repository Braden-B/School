import csv
import matplotlib.pyplot as plt

# ─────────────────────────────────────────────
# 1. READ sensor.csv MANUALLY (no outside libs
#    beyond csv which is stdlib)
# ─────────────────────────────────────────────
x_samples = []
y_labels  = []

with open("sensor.csv", "r") as f:
    reader = csv.reader(f)
    rows = list(reader)

# Row 0 → sensor readings (x), Row 1 → labels (y)
# Strips whitespace and converts to float/int
x_samples = [float(v.strip()) for v in rows[0] if v.strip() != ""]
y_labels  = [int(v.strip())   for v in rows[1] if v.strip() != ""]

n = len(x_samples)
print(f"Loaded {n} samples.")
print(f"Sample x values (first 10): {x_samples[:10]}")
print(f"Sample labels  (first 10): {y_labels[:10]}")

# ─────────────────────────────────────────────
# 2. HEURISTIC CLASSIFIER
#
#  Decision rule (our assumption):
#    x >= theta  →  Signal (label = 1)
#    x <  theta  →  Noise  (label = 0)
#
#  At each theta we count correct classifications
#  and track the best theta found so far.
# ─────────────────────────────────────────────

best_theta   = 0.0
best_correct = -1
accuracy_log = []   # stores (theta, accuracy) for every step

# Build the t range: 0.01, 0.02, ..., 1.90
t = 0.01
step = 0.01
results = []

while round(t, 10) <= 1.90:
    theta = t

    correct = 0
    for i in range(n):
        # Apply decision rule
        if x_samples[i] >= theta:
            predicted = 1   # Signal
        else:
            predicted = 0   # Noise

        if predicted == y_labels[i]:
            correct += 1

    accuracy = correct / n
    accuracy_log.append((round(theta, 2), accuracy))

    if correct > best_correct:
        best_correct = correct
        best_theta   = theta

    t = round(t + step, 10)

# ─────────────────────────────────────────────
# 3. REPORT RESULTS
# ─────────────────────────────────────────────
print("\n─── Heuristic Classifier Results ───")
print(f"Best theta (θ*)  : {best_theta:.2f}")
print(f"Correct samples  : {best_correct} / {n}")
print(f"Best accuracy    : {best_correct/n*100:.2f}%")

# Final classification using best_theta
print("\n─── Classification with θ* = {:.2f} ───".format(best_theta))
TP = TN = FP = FN = 0
for i in range(n):
    pred = 1 if x_samples[i] >= best_theta else 0
    actual = y_labels[i]
    if pred == 1 and actual == 1: TP += 1
    elif pred == 0 and actual == 0: TN += 1
    elif pred == 1 and actual == 0: FP += 1
    elif pred == 0 and actual == 1: FN += 1

print(f"True Positives  (Signal correctly classified)  : {TP}")
print(f"True Negatives  (Noise correctly classified)   : {TN}")
print(f"False Positives (Noise misclassified as Signal): {FP}")
print(f"False Negatives (Signal misclassified as Noise): {FN}")

# ─────────────────────────────────────────────
# 4. PLOT — Accuracy vs Theta
# ─────────────────────────────────────────────
thetas     = [a[0] for a in accuracy_log]
accuracies = [a[1] for a in accuracy_log]

plt.figure(figsize=(10, 5))
plt.plot(thetas, accuracies, color="steelblue", label="Accuracy at each θ")
plt.axvline(x=best_theta, color="red", linestyle="--",
            label=f"Best θ* = {best_theta:.2f} ({best_correct/n*100:.1f}%)")
plt.xlabel("θ (decision boundary)")
plt.ylabel("Classification Accuracy")
plt.title("Heuristic Linear Classifier — Accuracy vs θ")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("classifier_result.png", dpi=150)
plt.show()
print("\nPlot saved as classifier_result.png")

# ─────────────────────────────────────────────
# 5. SCATTER PLOT — Data with Decision Boundary
# ─────────────────────────────────────────────
signal_x = [x_samples[i] for i in range(n) if y_labels[i] == 1]
noise_x  = [x_samples[i] for i in range(n) if y_labels[i] == 0]

plt.figure(figsize=(10, 4))
plt.scatter(signal_x, [1]*len(signal_x), color="green", marker="|",
            s=200, label="Signal (label=1)", alpha=0.6)
plt.scatter(noise_x,  [0]*len(noise_x),  color="orange", marker="|",
            s=200, label="Noise (label=0)",  alpha=0.6)
plt.axvline(x=best_theta, color="red", linestyle="--",
            label=f"θ* = {best_theta:.2f}")
plt.xlabel("Sensor Value (x)")
plt.yticks([0, 1], ["Noise", "Signal"])
plt.title("Sensor Data with Best Decision Boundary")
plt.legend()
plt.grid(True, axis="x")
plt.tight_layout()
plt.savefig("data_boundary.png", dpi=150)
plt.show()
print("Scatter plot saved as data_boundary.png")