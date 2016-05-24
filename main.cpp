#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "sorted_vtr.h"
using namespace std;
int main () {
	srand(time(NULL));
	sorted_vtr<int> vtr1;
	sorted_vtr<int> vtr2;
	for (int i = 0; i < 10; i++) {
		vtr1.Insert(i % 3);
		vtr2.InsertUnique(i % 3);
	}
	cout<<"vtr1:"<<endl;
	for (int i = 0; i < vtr1.GetSize(); i++) {
		cout<<vtr1[i]<<endl;
	}
	cout<<"vtr2:"<<endl;
	for (int i = 0; i < vtr2.GetSize(); i++) {
		cout<<vtr2[i]<<endl;
	}
	return 0;
}
