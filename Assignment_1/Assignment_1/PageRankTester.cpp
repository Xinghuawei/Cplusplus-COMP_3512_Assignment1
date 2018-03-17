
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
	
	cout << matG << endl;
	
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
	cout << matS << endl;

	Matrix matQ(count);
	for (int i = 1; i <= count; i++) {
		for (int k = 1; k <= count; k++) {
			matQ.set_value(i, k, 1 / (double)count);
		}
	}
	cout << matQ << endl;


	system("PAUSE");
	
	
}