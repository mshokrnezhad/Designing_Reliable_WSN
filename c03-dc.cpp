// DegCal.cpp : Defines the entry point for the console application.
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
	ofstream result;
	ofstream finalx;
	ofstream n;
	ofstream r;
	ofstream finaly;
	ofstream rawdeg;
	ofstream sortdeg;
	ofstream mindeg;
	ofstream mindegcount;
	r.open("r.txt");
	result.open("result.txt", std::ios_base::app);
	n.open("n.txt");
	finalx.open("finalx.txt");
	finaly.open("finaly.txt");
	rawdeg.open("rawdeg.txt");
	sortdeg.open("sortdeg.txt");
	mindeg.open("mindeg.txt");
	mindegcount.open("mindegcount.txt");

	vector<double> x;
	vector<double> y;
	vector<int> deg;
	vector<int> tempdeg;
	vector<int> highdeg;
	vector<int> mhighdeg;
	vector<int> sdeg;
	vector<int> sdegindex;
	double SR_temp = atoi(argv[1]);
	const double SR = SR_temp;
	double R_temp = (2 * SR) + 2;
	const double R = R_temp;

	vector<double> xs;
	vector<double> ys;

	ifstream infiley("rawy.txt");
	double j = 0;
	while (infiley >> j)
	{
		y.push_back(j);
	}
	ifstream infilex("rawx.txt");
	double i = 0;
	while (infilex >> i)
	{
		x.push_back(i);
	}
	ifstream xsf("xs.txt");
	double jxs = 0;
	while (xsf >> jxs)
	{
		xs.push_back(jxs);
	}
	ifstream ysf("ys.txt");
	double iys = 0;
	while (ysf >> iys)
	{
		ys.push_back(iys);
	}

	double degcon = 0;
	int k = 0;
	for (int i = 0; i < x.size(); i++)
	{
		k = 0;
		for (int j = 0; j < x.size(); j++)
		{
			if (i != j && abs(x.at(i) - x.at(j)) <= R && abs(y.at(i) - y.at(j)) <= R)
			{
				k++;
			}
		}
		degcon += k;
		deg.push_back(k);
		tempdeg.push_back(k);
	}

	double sp2dg = 0;
	double sdg = 0;
		for (int i = 0; i < deg.size(); i++)
	{
		sp2dg = sp2dg + pow(deg.at(i), 2);
		sdg = sdg + deg.at(i);

	}

	double var = (sp2dg - pow(sdg, 2) / deg.size()) / (deg.size() - 1);
	sdg = sdg / deg.size();
	
	double ssdeg = 0;
	for (int i = 0; i < deg.size(); i++)
	{
		ssdeg = ssdeg + abs(sdg - deg.at(i));
	}
	ssdeg = ssdeg / deg.size();

	int kk = 0;
	for (int i = 0; i < x.size(); i++)
	{
		kk = 0;
		for (int j = 0; j < x.size(); j++)
		{
			if (i != j && abs(x.at(i) - x.at(j)) <= 2 * R && abs(y.at(i) - y.at(j)) <= 2 * R)
			{
				kk++;
			}
		}
		highdeg.push_back(kk);
	}

	int bol = 1;
	while (bol == 1)
	{
		bol = 0;
		int max = 0;
		int index = 0;
		for (int h = 0; h<deg.size(); h++)
		{
			if (deg.at(h)>max)
			{
				max = deg.at(h);
				index = h;
			}
		}
		deg.erase(deg.begin() + index);
		deg.insert(deg.begin() + index, -1);
		sdeg.push_back(max);
		sdegindex.push_back(index);
		for (int h = 0; h < deg.size(); h++)
		{
			if (deg.at(h) != -1)
			{
				bol = 1;
			}
		}
	}

	int min01 = sdeg.at(sdeg.size() - 1);
	int min02 = sdeg.at(sdeg.size() - 2);
	int index01 = sdegindex.at(sdeg.size() - 1);
	int index02 = sdegindex.at(sdeg.size() - 2);

	int kkk = 0;
	int maxmindeg = 0;
	for (int i = 0; i < x.size(); i++)
	{
		kkk = 0;
		for (int j = 0; j<x.size(); j++)
		{
			if (abs(x.at(i) - x.at(j)) <= 2 * R && abs(y.at(i) - y.at(j)) <= 2 * R && tempdeg.at(i) == min01 && tempdeg.at(j) == min01)
			{
				kkk++;
			}
		}
		if (kkk>maxmindeg)
			maxmindeg = kkk;
		mhighdeg.push_back(kkk);
	}
	
	int maxmax = -1;
	int maxindex = -1;
	for (int i = sdeg.size() - 1; i >= 0; i--)
	{
		if (sdeg.at(i) == min01 && mhighdeg.at(sdegindex.at(i)) == maxmindeg)
		if (highdeg.at(sdegindex.at(i)) >= maxmax)
		{
			maxmax = highdeg.at(sdegindex.at(i));
			maxindex = sdegindex.at(i);

		}
	}

	int co = 1;
	for (int j = 0; j < x.size(); j++)
	if (abs(x.at(maxindex) - x.at(j)) <= 2 * R && abs(y.at(maxindex) - y.at(j)) <= 2 * R)
	{
		r << co << endl;
		n << co << endl;
		finalx << co << " " << x.at(j) << endl;
		finaly << co << " " << y.at(j) << endl;
		for (int d = 0; d < sdegindex.size(); d++)
		if (sdegindex.at(d) == j)
			rawdeg << co << " " << sdeg.at(d) << endl;
		co++;
	}
	
	int count = 0;
	for (int h = 0; h < sdeg.size(); h++)
	{
		if (sdeg.at(h) == min01)
			count++;
	}

	mindeg << min01;

	mindegcount << count;

	for (int h = 0; h < sdeg.size(); h++)
	{
		sortdeg << sdeg.at(h) << endl;
	}
	
	double rcon = 0;
	vector<double> rcount;
	for (int i = 0; i < xs.size(); i++)
	{
		rcon = 0;
		for (int j = 0; j < x.size(); j++)
		{
			if (abs(x.at(j) - xs.at(i)) <= SR && abs(y.at(j) - ys.at(i)) <= SR)
			{
				rcon++;
			}
		}
		rcount.push_back(rcon);
	}

	rcon = 0;
	for (int j = 0; j < xs.size(); j++)
	{
		rcon += rcount.at(j);
	}

	result << x.size() << " ";
	result << degcon / 2 << " ";
	result.precision(4);
	result << fixed << (degcon / 2) / (x.size()) << " ";
	result << fixed << (degcon) / (x.size()) << " ";
	result << fixed << var << " ";
	result << fixed << ssdeg << " ";
	result << min01 << " ";
	result << count << " ";
	result.precision(2);
	result << rcon / (double)xs.size() << " ";

	sortdeg.close();
	mindeg.close();
	mindegcount.close();
	rawdeg.close();
	finalx.close();
	finaly.close();
	r.close();
	n.close();
	result.close();

	return 0;
}