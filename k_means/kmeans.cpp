#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
double euclid(vector<double>&a, vector<double>&b, double po=2)
{
    double dist = 0;
    for(int i=0;i<a.size();i++) dist+=pow(a[i]-b[i],po);
    return pow(dist, 1.0/po);
}
int argmin(vector<double>&a)
{
    int ans = 0;
    for(int i=0;i<a.size();i++) if(a[i]<a[ans]) ans = i;
    return ans;
}
vector<double> operator +(vector<double>&a, vector<double>&b)
{
    int n = a.size();
    vector<double>c(n);
    for(int i=0;i<n;i++) c[i]=a[i]+b[i];
    return c;
}
vector<double> operator /(vector<double>&a, double b)
{
    int n = a.size();
    vector<double>res(n);
    for(int i=0;i<n;i++) res[i] = a[i]/b;
    return res;
}
int main()
{
    cout<<setprecision(2);
    int k,n,d,i,j;
    cout<<"Enter the number of clusters k: ";
    cin>>k;
    cout<<"Enter the number of dimensions: ";
    cin>>d;
    cout<<"Enter the number of points: ";
    cin>>n;

    vector<vector<double> >points(n, vector<double>(d));
    cout<<"Enter the points:\n";
    for(i=0;i<n;i++) for(j=0;j<d;j++) cin>>points[i][j];

    vector<vector<double> >centres(k, vector<double>(d));
    cout<<"Enter initial cluster centres\n";
    for(i=0;i<k;i++) for(j=0;j<d;j++) cin>>centres[i][j];

    vector<int>assigned(n,-1);
    cout<<"--------------------------------------\n";
    while(1)
    {
        vector<vector<double> >dist(n, vector<double>(k));
        vector<int>new_assigned(n);
        for(i=0;i<n;i++) 
        {
            for(j=0;j<k;j++) 
            {
                dist[i][j] = euclid(points[i], centres[j]);    
            }
            int closest = argmin(dist[i]);
            new_assigned[i] = closest;
        }
        cout<<"\t";
        for(i=0;i<n;i++) cout<<"P"<<i+1<<"\t";
        cout<<endl;
        for(j=0;j<k;j++) 
        {
            cout<<"C"<<j+1<<"\t";
            for(i=0;i<n;i++) cout<<dist[i][j]<<"\t";
            cout<<endl;
        }

        vector<vector<double> >new_centres(k, vector<double>(d));
        cout<<"New clusters\n";
        for(i=0;i<k;i++)
        {
            double cnt = 0;
            cout<<"C"<<i+1<<": ";
            for(j=0;j<n;j++) if(new_assigned[j]==i)
            {
                cout<<j+1<<" ";
                cnt++;
                new_centres[i]=new_centres[i]+points[j];
            }
            new_centres[i]=new_centres[i]/cnt;
            cout<<endl;
        }
        cout<<"New centroids\n";
        for(i=0;i<k;i++)
        {
            cout<<i+1<<": (";
            for(j=0;j<d;j++) cout<<new_centres[i][j]<<(j==d-1?")":", ");
            cout<<endl;
        }
        for(i=0;i<n;i++) if(new_assigned[i]!=assigned[i]) break;
        cout<<"--------------------------------------\n";
        if(i==n) 
        {
            cout<<"Clusters unchanged\nStop\n";
            break;
        }
        centres = new_centres;
        assigned = new_assigned;
    }
}   