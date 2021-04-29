### DBSCAN : Density-Based Clustering Based on Connected Regions with High Density

Algorithm \
Input: \
D : a data set containing n objects, \
eps : the radius parameter, and \
MinPts : the neighborhood density threshold. \
Output : A set of density-based clusters. \
Method : 
1.  mark all objects as unvisited;
2.  do
3. randomly select an unvisited object p;
4. mark p as visited;
5. if the eps-neighborhood of p has at least MinPts objects
6. create a new cluster C, and add p to C;
7. let N be the set of objects in the eps-neighborhood of p;
8. for each point p0 in N
9. if p0 is unvisited
10. mark p0 as visited;
11. if the eps-neighborhood of p0 has at least MinPts points,
add those points to N;
12. if p0 is not yet a member of any cluster, add p0 to C;
13. end for
14. output C;
15. else mark p as noise;
16. until no object is unvisited;