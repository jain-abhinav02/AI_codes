#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
vector<vector<double> >points,dist;
double pt_dist(vector<double>&a, vector<double>&b)
{
    int n=a.size();
    double sum=0;
    for(int i=0;i<n;i++) sum+=(a[i]-b[i])*(a[i]-b[i]);
    sum = sqrt(sum);
    return sum;
}
double arr_min(vector<double>&arr)
{
    double mn=arr[0];
    for(int i=0;i<arr.size();i++) mn = min(mn, arr[i]);
    return mn;
}
double arr_max(vector<double>&arr)
{
    double mx=arr[0];
    for(int i=0;i<arr.size();i++) mx = max(mx, arr[i]);
    return mx;
}
double arr_avg(vector<double>&arr)
{
    double sum=0;
    int n=arr.size();
    for(int i=0;i<n;i++) sum+=arr[i];
    sum = sum/n;
    return sum;
}
vector<double> get_centroid(vector<int>&idx)
{
    int dims = points[0].size();
    vector<double>centroid(dims);
    int n=idx.size();
    int i,j;
    for(i=0;i<n;i++) for(j=0;j<dims;j++) centroid[j]+=points[idx[i]][j];
    for(j=0;j<dims;j++) centroid[j]/=n;
    return centroid;
}
double get_cluster_dist(vector<int>&a, vector<int>&b, int scheme)
{
    int i,j;
    int m = a.size();
    int n = b.size();
    vector<double>d;
    for(i=0;i<m;i++) for(j=0;j<n;j++) d.push_back(dist[a[i]][b[j]]);
    if(scheme==1) return arr_min(d);
    else if(scheme==2) return arr_max(d);
    else if(scheme==3) return arr_avg(d);
    else 
    {
        vector<double>centroid1 = get_centroid(a);
        vector<double>centroid2 = get_centroid(b);
        return pt_dist(centroid1, centroid2);
    }
}
void merge(vector<int>&a, vector<int>&b)
{
    for(int i=0;i<b.size();i++) a.push_back(b[i]);
}
int main()
{
    int i,j;
    cout<<setprecision(3);
    cout<<"Enter scheme\n1.min-link(single link) 2.max-link(complete link) 3.pairwise-average 4.centroid-dist\n";
    int scheme; cin>>scheme;
    cout<<"Enter the number of points: ";
    int n; cin>>n;
    dist.resize(n, vector<double>(n));
    cout<<"Enter 1.Points 2.Distance matrix\n";
    int input; cin>>input;
    if(input==1)
    {
        cout<<"Enter the number of dimensions: ";
        int dims; cin>>dims;
        vector<double>pt(dims);
        cout<<"Enter the points\n";
        for(i=0;i<n;i++)
        {
            for(j=0;j<dims;j++) cin>>pt[j];
            points.push_back(pt);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                dist[i][j] = pt_dist(points[i], points[j]);
            }
        }
    }
    else
    {
        for(i=0;i<n;i++) for(j=0;j<n;j++) cin>>dist[i][j];
    }
    vector<bool>valid(n,true);
    vector<int>label(n);
    for(i=0;i<n;i++) label[i] = i;
    vector<vector<int> >arr(n, vector<int>(1));
    for(i=0;i<n;i++) arr[i][0] = i;
    for(int step=0;step<n-1;step++)
    {
        cout<<"-----------------------------------\n";
        cout<<"Distance matrix\n";
        cout<<"  \t";
        for(i=0;i<n;i++) if(valid[i]) cout<<"C"<<label[i]+1<<"\t";
        cout<<endl;
        vector<vector<double> >cluster_dist(n, vector<double>(n,-1));
        for(i=0;i<n;i++)
        {
            if(!valid[i]) continue;
            cout<<"C"<<label[i]+1<<"\t";
            for(j=0;j<n;j++)
            {
                if(valid[j])
                {
                    cluster_dist[i][j] = get_cluster_dist(arr[i], arr[j], scheme);
                    cout<<cluster_dist[i][j]<<"\t";
                }
            }
            cout<<endl;
        }
        int ansx=-1,ansy=-1;
        double smallest = -1;
        for(i=0;i<n;i++) 
        {
            for(j=i+1;j<n;j++)
            {
                if(cluster_dist[i][j]==-1) continue;
                if(smallest==-1 || cluster_dist[i][j]<smallest)
                {
                    ansx=i;
                    ansy=j;
                    smallest = cluster_dist[i][j];
                }
            }
        }
        cout<<endl;
        cout<<"Smallest inter-cluster distance: "<<smallest<<endl;
        cout<<"Merge C"<<label[ansx]+1<<" and C"<<label[ansy]+1<<" to form C"<<n+step+1<<endl;
        valid[ansy]=false;
        label[ansx]=n+step;
        merge(arr[ansx], arr[ansy]);
    }
    cout<<"-----------------------------------\n";
}