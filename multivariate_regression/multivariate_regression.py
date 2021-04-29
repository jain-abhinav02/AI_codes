import numpy as np

np.set_printoptions(precision=4)
def myformat(t):
  if t>=0:
    return "+ %0.3f"%t
  else:
    return "- %0.3f"%(-t)

m = int(input("Enter the number of input variables "))
n = int(input("Enter the number of points "))
data = np.ones((n,m+1))
y = np.zeros((n,))
print("Enter the points as x1 x2 ... xn y")
for i in range(n):
    sample = [float(num) for num in input().split()]
    data[i,1:] = sample[:-1]
    y[i] = sample[-1]
print("-------------------------------------------------------")
#print(data)
#print(y)

coeff = np.dot(np.transpose(data),data)

for i in range(m+1):
  for j in range(i,m+1):
    if i==0 and j==0:
      continue
    elif i==0:
      print("x",j,sep="",end="\t")
    elif i==j:
      print("x",i,"^2",sep="",end="\t")
    else:
      print("x",i,"x",j,sep="",end="\t")
for i in range(m+1):
  if i==0:
    print("y",sep="",end="\t")
  else :
    print("yx",i,sep="",end="\t")
print()
for k in range(n):
  for i in range(m+1):
    for j in range(i,m+1):
      if i==0 and j==0:
        continue
      print(data[k,i]*data[k,j],sep="",end="\t")
  for i in range(m+1):
    print(y[k]*data[k,i],sep="",end="\t")
  print()
print("Column wise sum")
for i in range(m+1):
  for j in range(i,m+1):
    if i==0 and j==0:
      continue
    print(np.sum(data[:,i]*data[:,j]),sep="",end="\t")
for i in range(m+1):
  print(np.sum(y*data[:,i]),sep="",end="\t")
print()
print()

B = np.dot(np.transpose(data), np.reshape(y, (n,1)))
for i in range(m+1):
  print(B[i,0],"=",end=" ")
  for j in range(m+1):
    print(coeff[i,j],"*a",j,sep="",end="")
    if j<m:
      print(" + ",end="")
    else:
      print("")
print()

print("Coefficient matrix C")
print(coeff)
print()
print("B")
print(B)
print()

det = np.linalg.det(coeff)
if det != 0:
  cofactor_mat = np.linalg.inv(coeff).T * np.linalg.det(coeff)
  print("Cofactor matrix of C")
  print(cofactor_mat)
  print()
  print("Det(C) = ",end=" ")
  print("%.3f"%det)
  print()
  print("Take transpose and divide by det to get inverse")
  print()
  print("Inverse of coefficient matrix")
  inv = np.linalg.inv(coeff)
  print(inv)
  print()
  print("X = C_inv * B")
  ans = np.dot(inv,B)
  print(ans)
  print()
  for i in range(m+1):
    print("a",i," = %.3f"%ans[i,0],sep="")
  print()
  print("y = ",end="")
  for i in range(m+1):
    print(myformat(ans[i,0]),sep="",end="")
    if i!=0:
      print("*x",i,sep="",end="")
    print(" ",end="")
    if i==m:
      print("")