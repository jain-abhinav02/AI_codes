#include<iostream>
#include<vector>
using namespace std;
int main()
{
    string s,t;
    cout<<"Enter the strings s and t\n";
    cin>>s>>t;
    int m = s.length();
    int n = t.length();
    vector<vector<int> >dist(m+1,vector<int>(n+1));
    int i,j;
    for(i=0;i<m+1;i++) dist[i][0] = i;
    for(j=0;j<n+1;j++) dist[0][j] = j;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            int mn=min(dist[i][j-1]+1,dist[i-1][j]+1);
            dist[i][j] = min(mn, dist[i-1][j-1]+(s[i-1]!=t[j-1]));
        }
    }
    cout<<"    ";
    for(j=1;j<=m;j++) cout<<t[j-1]<<" ";
    cout<<endl;
    for(i=0;i<m+1;i++)
    {
        cout<<(i==0?' ':s[i-1])<<" ";
        for(j=0;j<n+1;j++) cout<<dist[i][j]<<" ";
        cout<<endl;
    }
}