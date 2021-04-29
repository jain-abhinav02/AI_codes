#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
int main()
{
    cout<<setprecision(5);
    int i,j;
    cout<<"Enter the number of points = ";
    int n; cin>>n;
    vector<double>x(n),y(n);
    cout<<"Enter the points\n";
    for(i=0;i<n;i++) cin>>x[i]>>y[i];
    cout<<"-----------------------------------\n";
    cout<<"x\ty\tx^2\txy\ty^2\n";
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_y2 = 0, sum_xy = 0;
    for(i=0;i<n;i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_x2 += x[i]*x[i];
        sum_y2 += y[i]*y[i];
        sum_xy += x[i]*y[i];
        cout<<x[i]<<"\t"<<y[i]<<"\t"<<x[i]*x[i]<<"\t"<<x[i]*y[i]<<"\t"<<y[i]*y[i]<<"\n";
    }
    cout<<endl;
    cout<<"Sum of x = "<<sum_x<<endl;
    cout<<"Sum of y = "<<sum_y<<endl;
    cout<<"Sum of x^2 = "<<sum_x2<<endl;
    cout<<"Sum of xy = "<<sum_xy<<endl;
    cout<<"Sum of y^2 = "<<sum_y2<<endl;
    cout<<endl;
    double byx = (n*sum_xy-sum_x*sum_y)/(n*sum_x2-sum_x*sum_x);
    double bxy = (n*sum_xy-sum_x*sum_y)/(n*sum_y2-sum_y*sum_y);
    double mean_y = sum_y/n;
    double mean_x = sum_x/n;
    cout<<"Mean of x = "<<mean_x<<endl;
    cout<<"Mean of y = "<<mean_y<<endl;
    cout<<endl; 
    cout<<"Regression line of y on x\n";
    cout<<"Regression coefficient byx = "<<byx<<endl;
    cout<<"y-"<<mean_y<<" = "<<byx<<"(x-"<<mean_x<<")"<<endl;
    cout<<"y = "<<mean_y-byx*mean_x<<" + ("<<byx<<")x"<<endl;
    cout<<endl;
    cout<<"Regression line of x on y\n";
    cout<<"Regression coefficient bxy = "<<bxy<<endl;
    cout<<"x-"<<mean_x<<" = "<<bxy<<"(y-"<<mean_y<<")"<<endl;
    cout<<"x = "<<mean_x-bxy*mean_y<<" + ("<<bxy<<")y"<<endl;
    cout<<endl;

}