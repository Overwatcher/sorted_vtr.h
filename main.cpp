#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "sorted_vtr.h"
using namespace std;
int main () {
	srand(time(NULL));
	sorted_vtr<long> vect;
	for (long i = 0;  i <10000000; i++) {
		int error = vect.Insert(i);
		cout<<"STEP : "<<i<<endl;
		if (error != 0) { cout<<"ERROR : "<<error<<endl; return 1; }
	}
	FILE *fout = fopen("output.txt", "w");	
	for (long i = 0; i < vect.GetSize(); i++) {
		fprintf(fout, "%d ", vect[i]);
	}
	int a;
	cin>>a;
	fclose(fout);
	cin>>a;
	return 0;
}
