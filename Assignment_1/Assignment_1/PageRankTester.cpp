
#include "PageRank.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>

using namespace std;
int main() {
	int count{ 0 };
	fstream file("test.txt");
	string line;
	while (file.get() != EOF) {
		getline(file, line);
		count++;
	}
	cout << "size is : ";
	cout << count << endl;

	fstream file2;
	file2.open("test.txt");
	Matrix matG(count);
	int c;
	int row = 1;
	int col = 1;
	while ((c = file2.get()) != EOF) {
		if (!isspace(c)) {
			matG.set_value(row, col, (c - '0'));
			if ((col % count) != 0) {
				col++;
			}
			else {
				col = 1;
				row++;
			}
		}
	}
	cout << "--------------------------" << endl;
	cout << "connectivity matrix G: " << endl;

	cout << matG << endl;

	cout << "--------------------------" << endl;
	cout << "Initial Importance matrix S: " << endl;
	Matrix matS(count);
	cout << matS << endl;
	int count1=0;

	double *arr = new double[count];
	for (int i = 1; i <= count; i++) {
		count1 = 0;
		for (int k = 1; k <= count; k++) {
			if (matG.get_value(k, i) == 1) {
				count1++;
			}
		}
		arr[i] =count1;
		for (int i = 1; i <= count; i++) {
			for (int k = 1; k <= count; k++) {
				if (matG.get_value(k, i) == 1) {
					matS.set_value(k, i, 1 / arr[i]);
				}
				if (arr[i] == 0) {
					matS.set_value(k, i, 1 / (double)count);
				}
			}
		}
	}
	cout << "--------------------------" << endl;
	cout << "Importance matrix S: " << endl;
	cout << matS << endl;

	Matrix matQ(count);
	for (int i = 1; i <= count; i++) {
		for (int k = 1; k <= count; k++) {
			matQ.set_value(i, k, 1 / (double)count);
		}
	}
	cout << "--------------------------" << endl;
	cout << "Matrix Q: " << endl;
	cout << matQ << endl;
	cout << "--------------------------" << endl;
	cout << "Matrix Q * 0.15: " << endl;
	matQ *= 0.15;
	cout << matQ << endl;
	cout << "--------------------------" << endl;
	cout << "Matrix S * 0.85: " << endl;
	matS *= 0.85;
	cout << matS << endl;

	cout << "--------------------------" << endl;
	cout << "transition matrix M: " << endl;
	Matrix matTransition = matQ + matS;
	cout << matTransition << endl;

	vector<double> Rank(count,1.0);
	vector<double> RankCopy(count);
	cout << "--------------------------" << endl;
	cout << "Initial Matrix Rank: " << endl;
	for (int i = 0; i < count; i++) {
		cout<< Rank[i]<<endl;
	}
	cout << "--------------------------" << endl;
	
	bool chain = true;
	bool whichone;
	while (chain==true) {
		
		for (int i = 1; i <= count; i++) {
			double sum = 0.0;
			for (int k = 1; k <= count; k++) {
				sum += (Rank[k - 1] * matTransition.get_value(i, k));
			}
			RankCopy[i - 1] = sum;
			for (int j = 0; j < count; j++) {
				cout << RankCopy[j] << endl;
			}
		}
		if (RankCopy != Rank) {
			Rank.erase(Rank.begin(), Rank.begin() + count);
			Rank.resize(count);
		}
		else {
			chain = false;
			whichone = true;
			cout << "1" << endl;
		}
		

		for (int i = 1; i <= count; i++) {
			double sum = 0.0;
			for (int k = 1; k <= count; k++) {
				sum += (RankCopy[k - 1] * matTransition.get_value(i, k));
			}
			Rank[i - 1] = sum;
			for (int j = 0; j < count; j++) {
				cout << Rank[j] << endl;
			}
		}

		if (RankCopy != Rank) {
			RankCopy.erase(RankCopy.begin(), RankCopy.begin()+count);
			RankCopy.resize(count);
		}
		else {
			chain = false;
			whichone = false;
			cout << "2" << endl;
		}
	}

	cout << "--------------------------" << endl;
	if (whichone) {
		for (int i = 0; i < count; i++) {
			cout << RankCopy[i] << endl;
		}
	} else {
		for (int i = 0; i < count; i++) {
			cout << Rank[i] << endl;
		}
	}

	system("PAUSE");
	
	
}