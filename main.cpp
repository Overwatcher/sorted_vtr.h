#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "sorted_vtr.h"
using namespace std;
int main () {
	srand(time(NULL));
	sorted_vtr<int> vect;
	vect.Insert(1);
	vect.Insert(3);
	vect.Insert(3);
	vect.Insert(2);
	vect.Insert(0);
	cout<<"insert order:"<<endl;
	cout<<"1 3 3 2 0 "<<endl;
	cout<<"before"<<endl;
	for (unsigned int i = 0; i < 5; i++) {
		cout<<vect[i]<<' ';
	}
	cout<<"removing:"<<endl;
	cout<<"3?:BinSearch = "<<vect.BinSearch(3)<<"quantity"<<vect.Remove(3)<<endl;
//	cout<<"7?:BinSearch = "<<vect.BinSearch(7)<<"quantity"<<vect.Remove(7)<<endl;
	for (int i = 0; i < vect.GetSize(); i++) {
		cout<<vect[i]<< ' ';
	}
	cout<<"Inserting 1: "<<endl;
	vect.Insert(10);
	cout<<"after:"<<endl;
	for (int i = 0; i < vect.GetSize(); i++) {
		cout<<vect[i]<< ' ';
	}
	return 0;
}
