
#include "PageRank.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int main() {
	int count{ 0 };
	fstream file("test.txt");
	string line;
	while (file.get() != EOF) {
		getline(file, line);
		count++;
	}
	cout << "size: " << endl;
	cout << count << endl;

	fstream file2;
	file2.open("test.txt");
	Matrix matG(count);
	int c;
	int row = 1;
	int col = 1;
	while ((c = file2.get()) != EOF) {
		if ((c - '0') >= 0) {
			matG.set_value(row, col, (c - '0'));
			if (((col + 1) % (count + 1)) == 0) {
				col = 1;
				row++;
			}
			else {
				col++;
			}
		}
	}
	
	cout << matG << endl;
	
	Matrix matS(count);

	int count1=0;
	int zero = 0;
	double *arr = new double[count];
	for (int i = 1; i <= count; i++) {
		double sum = 0.0;
		count1 = 0;
		for (int k = 1; k <= count; k++) {
			if (matG.get_value(k, i) == 1) {
				count1++;
			}
		}
		arr[i] =count1;
	}

	for (int i = 1; i <= count; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int i = 1; i <= count; i++) {
		for (int k = 1; k <= count; k++) {
			if (matG.get_value(k, i) == 1) {
				matS.set_value(k, i, 1/(double)arr[i]);
			} 
			if (arr[i] == 0) {
				matS.set_value(k, i, 1 / (double)count);
			}
		}
	}


	cout << matS << endl;



	system("PAUSE");
	
	
}