import numpy as np
np.set_printoptions(precision = 3)

num_features = int(input("Enter the number of features: "))
num_samples = int(input("Enter the number of samples: "))
X = np.zeros((num_samples, num_features))

print("Enter the values")
for i in range(num_samples):
  X[i] = np.array(input().split())

mean = np.mean(X, axis = 0)
std = np.std(X, axis = 0)
print("Mean of all features",mean)
print("Std  of all features",std)
print("----------------------------")

X = (X-mean)/std
print("Input after normalization")
print(X)
print("----------------------------")

A = np.dot(np.transpose(X), X)/num_samples
print("Covariance matrix")
print(A)
print("----------------------------")

eig_values, eig_vectors = np.linalg.eig(A)
order = np.argsort(eig_values)[::-1][:num_features]
eig_values = eig_values[order]
eig_vectors = eig_vectors[:,order]
print("Eigen values")
print(eig_values)
print("Eigen vectors along columns")
print(eig_vectors)
print("----------------------------")

X_transformed = np.dot(X, eig_vectors)
print("Input transformed")
print(X_transformed)
print("----------------------------")