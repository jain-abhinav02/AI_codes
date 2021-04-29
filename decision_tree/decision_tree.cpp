#include<bits/stdc++.h>
using namespace std;

class decision_calculator
{
private:
	int examples; //Total number of examples to classify
	int no_classes; //number of classes
	int branches; //number of branches to distribute
	vector<int> document_distribution; //store distribution of total document first value corresponding to total examples rest for the individual classes
	vector<vector<int> > branch_distribution; //store distribution on branch and class basis distribution[branch][0] contains branch total and later are belonging to classes
	bool branched_calculation;

public:
	decision_calculator(bool branched_calculation) {
		this->branched_calculation = branched_calculation;
		cout<<"Enter number of examples: ";
		cin>>this->examples;
		cout<<"Enter number of classes: ";
		cin>>this->no_classes;
		
		if(branched_calculation == true) {
			cout<<"Enter number of branches: ";
			cin>>this->branches;
		}


		this->document_distribution.resize(no_classes+1);

		if(branched_calculation == true) {
			this->branch_distribution.resize(branches);
			for(int i =0;i <branches; i++)
				this->branch_distribution[i].resize(no_classes+1);
		}

		this->input_distribution();
	}

	void input_distribution() {
		cout<<"Document Total. ";
		for(int i =0;i < no_classes;i++)
			cout<<"class"<<i+1<<" ";
		cout<<"\n";
		for(int i =0;i < no_classes+1; i++)
			cin>>document_distribution[i];

		if(branched_calculation == true) {
			cout<<"Branch Total. ";
			for(int i =0;i < no_classes;i++)
				cout<<"class"<<i+1<<" ";
			cout<<"\n";
			for(int i = 0;i < branches;i++) {
				cout<<"Branch "<<i+1<<"\n";
				for(int j = 0; j< no_classes+1; j++) {
					cin>>this->branch_distribution[i][j];
				}
			}
		}
	}

	/*ENTROPY FUNCTIONS START*/
	vector<double> calculate_entropy_all_branches();
	double calculate_entropy_document();
	double calculate_entropy(int branch_number);
	void entropy_calculations(); 

	inline double information_gain(double prob) {
		if(prob <= 0.0)
			return prob;
		return -1 * prob * log2(prob);
	}
	/* ENTROPY FUNCTIONS END */

	
	/* VARIANCE STARTS*/
	void variance_calculations();
	/* VARIANCE ENDS*/

	
	/*MISCLASSIFCATION STARTS */
	void misclassification_calculations();
	/*MISCLASSIFICATIN ENDS */

	
	~decision_calculator() {
		cout<<"END\n";
	}
	
};

//ENTROPY FUNCTIONS
double decision_calculator::calculate_entropy_document() {
	double entropy = 0.0;
	cout<<"ClassNo\tClass Prob\tClass Entropy\n";
	for(int i =0;i < no_classes; i++) {
		double prob = (double)document_distribution[i+1] / (double)document_distribution[0];
		double class_entropy = information_gain(prob);
		cout<<"C"<<i+1<<"\t"<<prob<<"\t\t"<<class_entropy<<"\n";
		entropy+=class_entropy;
	}
	cout<<"I(D) = "<<entropy<<endl;
	cout<<"-----------------------------------------------------\n";
	return entropy;
}

double decision_calculator::calculate_entropy(int branch_number) {
	double entropy = 0.0;
	cout<<"ClassNo\tClass Prob\tClass Entropy\n";
	for(int i =0;i < no_classes; i++) {
		double prob = (double)branch_distribution[branch_number][i+1] / (double)branch_distribution[branch_number][0];
		double class_entropy = information_gain(prob);
		cout<<"C"<<i+1<<"\t"<<prob<<"\t\t"<<class_entropy<<"\n";
		entropy+=class_entropy;
	}
	return entropy;
}

vector<double> decision_calculator::calculate_entropy_all_branches() {
		vector<double> braches_entropy(branches);
		for(int i =0;i < branches;i++) {
			braches_entropy[i] = calculate_entropy(i);
			cout<<"I(Branch"<<i+1<<")"<<" = "<<braches_entropy[i]<<"\n";
			cout<<"-----------------------------------------------------\n";
		}
		return braches_entropy;
}

void decision_calculator::entropy_calculations() {
		double doc_entropy = calculate_entropy_document();
		if(branched_calculation == true) {
			vector<double> braches_entropy = calculate_entropy_all_branches();
			//Retirn cahnge in entropy
			cout<<"Change in entropy= ";
			for(int i =0; i< branches; i++) {
				doc_entropy-=((double)branch_distribution[i][0] / (double)examples) * braches_entropy[i];
			}
			cout<<"DELTA(I(D)) = "<<doc_entropy<<endl;
		}
}

//ENTROPY FUNCTION ENDS

//VARIANCE FUNCTIONS
void decision_calculator::variance_calculations() {
	if(branched_calculation == false) {
		double doc_variance = 1.0;
		for(int  i =0;i<no_classes;i++) {
			double prob = (double) document_distribution[i+1] / (double) document_distribution[0];
			doc_variance-=(prob * prob);
		}
		doc_variance*=0.5;
		cout<<"VARIANCE(D) = "<<doc_variance<<endl;
	} else {
		double doc_variance = 1.0;
		for(int  i =0;i<no_classes;i++) {
			double prob = (double) document_distribution[i+1] / (double) document_distribution[0];
			doc_variance-=(prob * prob);
		}
		doc_variance*=0.5;
		cout<<"VARIANCE(D) = "<<doc_variance<<endl;

		vector<double> branches_variance(branches, 1.0);
		for(int i =0;i < branches; i++) {
			for(int  j =0;j<no_classes;j++) {
				double prob = (double) branch_distribution[i][j+1] / (double) branch_distribution[i][0];
				branches_variance[i]-=(prob * prob);
			}
		}
		for(int i =0;i<branches;i++) {
			branches_variance[i]*=0.5;
			cout<<"VARIANCE(Branch"<<i+1<<") = "<<branches_variance[i]<<"\n";
			doc_variance-=((double)branch_distribution[i][0] / (double)examples) * branches_variance[i];
		}
		cout<<"VARIANCE-DELTA(I(D)) = "<<doc_variance<<endl;
	}
}
//VARIANCE FUNCTIONS ENDS

//MISCLASSIFICATION FUNCTIONS
void decision_calculator::misclassification_calculations() {
	if(branched_calculation == false) {
		double doc_misclassification = 1.0;
		double max_val = 0.0;
		for(int  i =0;i<no_classes;i++) {
			double prob = (double) document_distribution[i+1] / (double) document_distribution[0];
			max_val= max(max_val, prob);
		}
		doc_misclassification-=max_val;
		cout<<"MISCLASSIFICATION(D) = "<<doc_misclassification<<endl;
	} else {
		double doc_misclassification = 1.0;
		double max_val = 0.0;
		for(int  i =0;i<no_classes;i++) {
			double prob = (double) document_distribution[i+1] / (double) document_distribution[0];
			max_val= max(max_val, prob);
		}
		doc_misclassification-=max_val;
		cout<<"MISCLASSIFICATION(D) = "<<doc_misclassification<<endl;

		vector<double> branches_misclassification(branches, 1.0);
		for(int i =0;i < branches; i++) {
			max_val = 0.0;
			for(int  j =0;j<no_classes;j++) {
				double prob = (double) branch_distribution[i][j+1] / (double) branch_distribution[i][0];
				max_val=max(max_val, prob);
			}
			branches_misclassification[i]-=max_val;
		}
		for(int i =0;i<branches;i++) {
			cout<<"MISCLASSIFICATION(Branch"<<i+1<<") = "<<branches_misclassification[i]<<"\n";
			doc_misclassification-=((double)branch_distribution[i][0] / (double)examples) * branches_misclassification[i];
		}
		cout<<"MISCLASSIFICATION-DELTA(I(D)) = "<<doc_misclassification<<endl;
	}
}
//MISCLASSIFICATION FUNCTIONS ENDS



int main() {
	bool branched_calculation;
	cout<<"Branched Calculation: (1 for yes 0 for no):";
	cin>>branched_calculation;

	decision_calculator* decision = new decision_calculator(branched_calculation);
	decision->entropy_calculations();
	cout<<"================================================================\n";
	decision->variance_calculations();
	cout<<"================================================================\n";
	decision->misclassification_calculations();
	cout<<"================================================================\n";
	delete(decision);

	return 0;
}