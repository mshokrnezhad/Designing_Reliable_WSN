// PTD.cpp : Defines the entry point for the console application.
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
	int r = 0;
	int M = 0;
	int R = 0;

	int clra = atoi(argv[1]);
	int clM = atoi(argv[2]);
	int clR = atoi(argv[3]);

	r = clra;
	R = clR;
	M = clM;

	int temp_N = 0;
	ifstream Nfile("N.txt");
	double j = 0;
	while (Nfile >> j)
	{
		temp_N = j;
	}
	int N = temp_N;

	const int findeg = 1;
	double r_x = 0;
	double r_y = 0;
	ofstream rawx;
	ofstream rawy;
	rawx.open("rawx.txt");
	rawy.open("rawy.txt");
	double xs[N];
	double ys[N];
	double max_x = 0;
	double max_y = 0;
	double min_x = R;
	double min_y = R;
	int counter = 0;
	double xr[M];
	double yr[M];
	int cr[M];
	int cs[M][N];
	int nr[N][M];
	int rn[M][N];
	int flag[M];
	int sum[N];

	ifstream xsfile("xs.txt");
	double a = 0;
	int b = 0;
	while (xsfile >> a)
	{
		xs[b] = a;
		b++;
	}
	ifstream ysfile("ys.txt");
	a = 0;
	b = 0;
	while (ysfile >> a)
	{
		ys[b] = a;
		b++;
	}

	for (int i = 0; i < M; i++)
	{
		xr[i] = -1;
		yr[i] = -1;
	}

	int globflag = 0;
	int degree = 0;
	while (globflag == 0)
	{
		degree++;
		globflag = 1;
		counter = 0;
		for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cr[j] = 0;
			cs[j][i] = 0;
			nr[i][j] = 0;
			rn[j][i] = 0;
			flag[j] = 0;
			if (xs[i] != -1)
				sum[i] = 0;
		}

		for (int i = 0; i < N; i++)
		{
			if (xs[i] != -1 && xs[i] >= max_x)
				max_x = xs[i];
			if (ys[i] != -1 && ys[i] >= max_y)
				max_y = ys[i];
			if (xs[i] != -1 && xs[i] <= min_x)
				min_x = xs[i];
			if (ys[i] != -1 && ys[i] <= min_y)
				min_y = ys[i];
		}

		max_x = max_x - r;
		max_y = max_y - r;
		min_x = min_x + r;
		min_y = min_y + r;

		if (max_x - min_x <= 0)
			r_x = 1;
		else
			r_x = ceil((max_x - min_x) / (2 * r)) + 1;
		if (max_y - min_y <= 0)
			r_y = 1;
		else
			r_y = ceil((max_y - min_y) / (2 * r)) + 1;

		if (r_x == 1 && r_y != 1)
		for (double y = 0; y < r_y; y++)
		for (int z = 0; z < M; z++)
		if (xr[z] == -1)
		{
			xr[z] = (max_x + min_x) / 2;
			yr[z] = min_y + (y * ((max_y - min_y) / (r_y - 1)));
			break;
		}
		if (r_y == 1 && r_x != 1)
		for (double x = 0; x < r_x; x++)
		for (int z = 0; z < M; z++)
		if (xr[z] == -1)
		{
			xr[z] = min_x + (x * ((max_x - min_x) / (r_x - 1)));
			yr[z] = (max_y + min_y) / 2;
			break;
		}

		if (r_y != 1 && r_x != 1)
		for (double x = 0; x < r_x; x++)
		for (double y = 0; y < r_y; y++)
		for (int z = 0; z < M; z++)
		if (xr[z] == -1)
		{
			xr[z] = min_x + (x * ((max_x - min_x) / (r_x - 1)));
			yr[z] = min_y + (y * ((max_y - min_y) / (r_y - 1)));
			break;
		}
		if (r_y == 1 && r_x == 1)
		for (int z = 0; z < M; z++)
		if (xr[z] == -1)
		{
			xr[z] = (max_x + min_x) / 2;
			yr[z] = (max_y + min_y) / 2;
			break;
		}

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < M; i++)
			if (xr[i] >= 0 && xs[j] != -1)
			{
				if (abs(xr[i] - xs[j]) <= r && abs(yr[i] - ys[j]) <= r)
				{
					cr[i]++;
					cs[i][j]++;
					nr[j][i] = 1;
					rn[i][j] = 1;
				}
			}
			else
				break;
		}

		int s1 = 0;
		int s2 = 0;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (rn[i][j] == 1)
				for (int l = 0; l < M; l++)
				{
					s1 += rn[l][j];
				}
				if (s1 > 1)
					cs[i][j] = 0;
				s1 = 0;
			}
			for (int j = 0; j < N; j++)
			{
				s2 += cs[i][j];
			}
			if (s2 == 0)
			{
				flag[i] = 1;
				for (int j = 0; j < N; j++)
				{
					rn[i][j] = 0;
				}
			}
			s2 = 0;
		}

		for (int j = 0; j < M; j++)
		{
			if (cr[j] == 0)
			{
				xr[j] = -1;
				yr[j] = -1;
			}
			if (flag[j] == 1)
			{
				xr[j] = -1;
				yr[j] = -1;
			}
			if (xr[j] >= 0)
				counter++;
		}

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < M; i++)
			{
				sum[j] += rn[i][j];
			}
		}

		for (int i = 0; i < N; i++)
		{
			if (sum[i] >= findeg)
			{
				xs[i] = -1;
				ys[i] = -1;
			}
			if (sum[i] < findeg)
				globflag = 0;
		}
	}

	int seed = 9300;
	for (int i = 0; i < M; i++)
	if (xr[i] >= 0)
	{
		rawx << xr[i] + (rand() % (5) - (3)) << endl;
		rawy << yr[i] + (rand() % (5) - (2)) << endl;

	}

	rawx.close();
	rawy.close();

	return 0;
}