import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from mlxtend.evaluate import bias_variance_decomp
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import PolynomialFeatures

def runPolynomial(degree):
    polynomial_features = PolynomialFeatures(degree=degree) # select the degree and fit features
    x_poly_train = polynomial_features.fit_transform(X_train)
    x_poly_test = polynomial_features.transform(X_test)

    model.fit(x_poly_train,y_train) # train our regression onto the new features
    predict = model.predict(x_poly_test) # create a prediction list with test values

    mse, bias, var = bias_variance_decomp(model, x_poly_train, y_train, x_poly_test, y_test, loss='mse', num_rounds=200,
                                          random_seed=1) # calculate bias, variance and MSE

    sort_axis = np.argsort(X_test.flatten()) # I was having issues with data giving crazy lines, so I reordered the predicted points
    x_plot = X_test.flatten()[sort_axis]
    y_plot = predict[sort_axis]

    print(f"Degree {degree}") # printing and plotting
    print(f"MSE: {mse:.3f}")
    print(f"Bias: {bias:.3f}")
    print(f"Variance: {var:.3f}")
    plt.plot(x_plot, y_plot, label = f"Degree {degree} degree")

np.random.seed(0)
x = 2 - 3 * np.random.normal(0, 1, 100)
y = x - 2 * (x ** 2) + 0.5 * (x ** 3) + np.random.normal(-3, 3, 100)
x.reshape(-1,1)
y.reshape(-1,1)
plt.plot(x,y, 'ro')

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.1, random_state=1)

X_train = X_train.reshape(-1,1) # reshapes all data to be in a 2D array
X_test = X_test.reshape(-1,1)
Y_train = y_train.reshape(-1,1)
Y_test = y_test.reshape(-1,1)

model = LinearRegression() # create our model

runPolynomial(1)
runPolynomial(2)
runPolynomial(3)

plt.legend() # plot
plt.show()