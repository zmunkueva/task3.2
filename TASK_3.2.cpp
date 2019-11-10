#include "pch.h"
#include <iostream>
#include "VecArrayStat.h"
using namespace std;

int main()
{
	VecArrayStat a("filename.txt");
	a.print();
	cout << "max =  " << a.get_max() << endl;
	cout << "min = " << a.get_min() << endl;
	double mean_ = a.mean();
	cout << "mean = " << mean_ << endl;
	double rms_ = a.rms();
	cout << " rms = " << rms_ << endl;
	return 0;
}
