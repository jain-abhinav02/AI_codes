#include <bits/stdc++.h>
using namespace std;

double inner_product(vector<double> &a, vector<double> &b)
{
	//Function assumes size of both vectors are same
	double sum = 0.0;
	for (int i = 0; i < a.size(); i++)
	{
		sum += (a[i] * b[i]);
	}
	return sum;
}

void update_weight(vector<double> &weight, vector<double> &update, int sign)
{
	//Function assumes size of both vectors are same
	for (int i = 0; i < weight.size(); i++)
	{
		weight[i] += sign * update[i];
	}
}

void print_vector(vector<double> &a)
{
	cout << "[ ";
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}

	cout << "]\n";
}

int main()
{
	int num_instances; // number of instances
	int vec_size;	   //Each instance size

	cout << "Enter number of instance:";
	cin >> num_instances;

	cout << "Enter size of each vector: ";
	cin >> vec_size;

	cout << "Enter instance\n";
	vector<vector<double> > instances(num_instances, vector<double>(vec_size));
	vector<double> labels(num_instances);

	for (int i = 0; i < num_instances; i++)
	{
		cout << "X" << i + 1 << ": ";
		for (int j = 0; j < vec_size; j++)
		{
			cin >> instances[i][j];
		}
		cout << "Y" << i + 1 << ": ";
		cin >> labels[i];
	}

	vector<double> weight(vec_size, 0.0);
	int update_no = 0;
	cout << "Weight[" << update_no << "] = ";
	print_vector(weight);
	cout << "==========================================================\n";

	while (1)
	{
		bool no_change = true;
		cout << "Ex\ty\tW*X\tUpdate\n";

		for (int i = 0; i < num_instances; i++)
		{
			double sum = inner_product(instances[i], weight);
			int sign = sum >= 0 ? 1 : -1;

			if (sign != labels[i])
			{
				update_no++;
				update_weight(weight, instances[i], labels[i]);
				cout << "X" << i + 1 << "\t" << labels[i] << "\t" << sum << "\t";
				cout << "Weight[" << update_no << "] = ";
				print_vector(weight);
				no_change = false;
			}
			else
			{
				cout << "X" << i + 1 << "\t" << labels[i] << "\t" << sum << "\t---\n";
			}
		}
		cout << "==========================================================\n";
		if (no_change == true)
			break;
	}

	//Final Answer
	cout << "FINAL ANSWER\n";
	cout << "Weight[" << update_no << "] = ";
	print_vector(weight);
	return 0;
}