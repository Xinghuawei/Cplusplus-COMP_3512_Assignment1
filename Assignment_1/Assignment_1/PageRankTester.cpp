#include "PageRank.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>

using namespace std;
int main() {
	int count{ 0 };
	string in;
	
	cout << "Enter the file name: (test.txt or test2.txt)" << endl;
	cin >> in;

	//open file with input name
	fstream file(in);
	string line;

	//Count the number of lines in the file
	//Number of lines equals rows also equals columns
	while (file.get() != EOF) {
		getline(file, line);
		count++;
	}
	cout << "size is : ";
	cout << count << endl;

	//reset file pointing locationn
	fstream file2;
	file2.open(in);
	Matrix matG(count);
	int c;
	int row = 1;
	int col = 1;

	//get values from the file and insert into
	//matrix one by one.
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

	//output matrix G
	cout << matG << endl;


	//Initial Importance matrix S
	Matrix matS(count);

	int count1=0;

	//count number of 1's in one column
	//Count value is row number(column number)
	double *arr = new double[count];
	for (int i = 1; i <= count; i++) {
		count1 = 0;
		for (int k = 1; k <= count; k++) {
			if (matG.get_value(k, i) == 1) {
				count1++;
			}
		}
		arr[i] =count1;
	}

	//set values into matrix S
	//If one column does not has any 1, the 
	//value is 1/row(col).
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

	//print matrix S
	cout << "--------------------------" << endl;
	cout << "Importance matrix S: " << endl;
	cout << matS << endl;

	//Create matrix Q.
	//Every value in Q is 1/size.
	Matrix matQ(count);
	for (int i = 1; i <= count; i++) {
		for (int k = 1; k <= count; k++) {
			matQ.set_value(i, k, 1 / (double)count);
		}
	}

	//Print matrix Q.
	cout << "--------------------------" << endl;
	cout << "Matrix Q: " << endl;
	cout << matQ << endl;

	//Transitive matrix = 0.15*Matrix Q + Matrix S*0.85
	//Calculate matrix Q * 0.15 and set value into Q.
	//Print Q
	cout << "--------------------------" << endl;
	cout << "Matrix Q * 0.15: " << endl;
	matQ *= 0.15;
	cout << matQ << endl;

	//Calculate matrix S * 0.85 and set value into S.
	//Print S.
	cout << "--------------------------" << endl;
	cout << "Matrix S * 0.85: " << endl;
	matS *= 0.85;
	cout << matS << endl;

	//Transitive matrix = 0.15*Matrix Q + Matrix S*0.85
	//Print transitive matrix.
	cout << "--------------------------" << endl;
	cout << "transition matrix M: " << endl;
	Matrix matTransition = matQ + matS;
	cout << matTransition << endl;

	//Create vector represents rank with value of all 1's 
	vector<double> Rank(count,1.0);

	//Create vector represents a temp with size of size.
	//count is size.
	vector<double> RankCopy(count);

	//Print rank.
	cout << "--------------------------" << endl;
	cout << "Initial Matrix Rank: " << endl;
	for (int i = 0; i < count; i++) {
		cout<< Rank[i]<<endl;
	}
	cout << "--------------------------" << endl;
	
	//True then while loop continues.
	bool chain = true;

	//decide which for loop the loop terminate.
	//True then use RankCopy
	//False then use Rank
	bool whichone;

	//Multiply the transition matrix M by our column matrix rank, and then
	//multiply M by the result and then keep doing this until the and rank stops
	//changing
	while (chain==true) {
		
		for (int i = 1; i <= count; i++) {
			double sum = 0.0;
			for (int k = 1; k <= count; k++) {
				sum += (Rank[k - 1] * matTransition.get_value(i, k));
			}
			RankCopy[i - 1] = sum;
		}

		if (RankCopy != Rank) {
			Rank.clear();
			Rank.resize(count);
		}
		else {
			chain = false;
			whichone = true;
		}
		

		for (int i = 1; i <= count; i++) {
			double sum = 0.0;
			for (int k = 1; k <= count; k++) {
				sum += (RankCopy[k - 1] * matTransition.get_value(i, k));
			}
			Rank[i - 1] = sum;
		}

		if (RankCopy != Rank) {
			RankCopy.clear();
			RankCopy.resize(count);
		}
		else {
			chain = false;
			whichone = false;
		}
	}

	cout << "--------------------------" << endl;

	//Create a final vector to represents rank result.
	vector<double> final(count);

	//decide which for loop the loop terminate.
	//True then use RankCopy
	//False then use Rank
	if (whichone) {
		double sum = 0.0;
		for (int i = 0; i < count; i++) {
			cout << RankCopy[i] << endl;
			sum += RankCopy[i];
		}
		for (int j = 0; j < count; j++) {
			final[j] = RankCopy[j] / sum;
		}

	} else {
		double sum = 0.0;
		for (int i = 0; i < count; i++) {
			cout << Rank[i] << endl;
			sum += Rank[i];
		}
		for (int j = 0; j < count; j++) {
			final[j] = Rank[j] / sum;
		}
	}

	cout << "--------------------------" << endl;
	cout << "Final Rank : " << endl;

	//Print final rank.
	//i+65 is letter A and so on.
	for (int i = 0; i < count; i++) {
		char c = i + 65;
		cout << c << " = " << final[i] << endl;
	}

	//Output result to a txt file.
	ofstream outfile("PageRank.txt");
	
	//Print result.
	//i+65 is letter A and so on.
	for (int i = 0; i < count; i++) {
		char c = i + 65;
		outfile << c << " = " << final[i] << endl;
	}

	//close file.
	file.close();
	file2.close();
	outfile.close();

	system("PAUSE");
	return 0;
	
}