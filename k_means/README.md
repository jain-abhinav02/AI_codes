### K Means Algorithm
Each cluster is represented by the mean value of the objects in the cluster. 

---
Input: \
k: the number of clusters, \
D: a data set containing n objects. 

---
Output: A set of k clusters. 

---
Method: 
1. arbitrarily choose k objects from D as the initial cluster centers; 
2. repeat
3. (re)assign each object to the cluster to which the object is the most similar,
based on the mean value of the objects in the cluster;
4. update the cluster means, that is, calculate the mean value of the objects for
each cluster;
5. until no change;