#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
void calc_prob(vector<double>&prob)
{
    cout<<"Probabilities\n";
    double sum = 0.0;
    int n = prob.size();
    for(int i=0;i<n;i++) sum += prob[i];
    for(int i=0;i<n;i++) 
    {
        prob[i] = prob[i]/sum;
        cout<<prob[i]<<"\t";
    }
    cout<<endl;
    cout<<"---------------------------------\n";
}
double information(vector<double>&prob)
{
    cout<<"Information/Entropy\n";
    int i, n=prob.size();
    double total_info = 0.0;
    for(i=0;i<n;i++)
    {
        double info=0.0;
        if(prob[i]!=0)  info = - ( prob[i] * log2(prob[i]) );
        cout<<info<<"\t";
        total_info += info;
    }
    cout<<endl<<total_info<<endl;
    cout<<"---------------------------------\n";
    return total_info;
}
double variance(vector<double>&prob)
{
    cout<<"Variance\n";
    int i, n=prob.size();
    double var = 1.0;
    for(i=0;i<n;i++)
    {
        cout<<prob[i]*prob[i]<<"\t";
        var -= prob[i]*prob[i];
    }
    var/=2.0;
    cout<<endl<<var<<endl;
    cout<<"---------------------------------\n";
    return var;
}
double misclassification(vector<double>&prob)
{
    cout<<"Misclassification\n";
    int i, n=prob.size();
    double ans = prob[0];
    for(i=0;i<n;i++)
    {
        if(prob[i]>ans) ans = prob[i];
    }
    cout<<"Max prob: "<<ans<<endl;
    ans = 1-ans;
    cout<<ans<<endl;
    cout<<"---------------------------------\n";
    return ans;
}
int main()
{
    cout<<setprecision(3);
    int i, n;
    cout<<"Enter the number of classes: ";
    cin>>n;
    vector<double>freq(n);
    cout<<"Enter the class frequencies\n";
    for(i=0;i<n;i++) cin>>freq[i];
    cout<<"---------------------------------\n";
    calc_prob(freq);
    information(freq);
    variance(freq);
    misclassification(freq);
}