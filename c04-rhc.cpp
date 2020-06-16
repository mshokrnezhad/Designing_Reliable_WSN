// Reliability HeuCal.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "iostream"
#include "fstream"
#include "vector"

using namespace std;

int main(int argc, char* argv[])
{
	double p_temp = atof(argv[1]);
	const double p = p_temp;

	ofstream rel;
	rel.open("rel.txt");

	vector<int> v;
	ifstream infile("sortdeg.txt");
	int i = 0;
	while (infile >> i)
	{
		v.push_back(i);
	}

	int n = v.size() - 1;
	double qdi = 0;
	double p1 = 1;
	double p2 = 1;
	double sum = 0;
	double u; //be jaye m[i] u gozashtim.

	for (int i = 1; i <= n; i++)
	{
		qdi = pow((1 - p), v.at(i));
		u = min(v.at(i), (i - 1));
		for (int j = 1; j <= u; j++)
		{
			p1 = p1*(1 - (pow((1 - p), (v.at(j) - 1))));
		}
		for (int k = u + 1; k <= i - 1; k++)
		{
			p2 = p1*(1 - (pow((1 - p), (v.at(k)))));
		}
		sum += qdi*p1*p2;
		qdi = 0;
		p1 = 1;
		p2 = 1;
	}

	rel << 1 - sum;

	rel.close();

	return 0;
}
