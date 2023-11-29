#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int getGraphSize(int minN)
{
	int n = 0;

	cout << "\n  Graph size(>" << minN << "): ";
	cin >> n;

	if (n <= minN)
	{
		cout << "  Wrong size of array.\n\n";
		return -1;
	}

	return n;
}

template<class T>
void matrixOut(vector<vector<T>> matrix, int n)
{
	cout << "\n  Matrix:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "  ";
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << "\t  ";
		cout << endl;
	}
}

vector<vector<double>> getRandMatrix(int n, bool isDouble, double& maxVal)
{
	vector<vector<double>> matrix(n, vector<double>(n, 0));

	int min = 0, max = 0;

	cout << "\n  Creating a random matrix...\n";
	cout << "  Minimal value = ";
	cin >> min;
	cout << "  Maximal value = ";
	cin >> max;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (isDouble)
				matrix[i][j] = min + rand() % ((max - min) * 10) / 10.0;
			else
				matrix[i][j] = min + rand() % (max - min);
		}

	maxVal = (double)max;
	return matrix;
}

void dijkstrasAlgorithm()
{
	double minValue, buff;
	int i = 3, z, j;

	int n = getGraphSize(i);
	if (n < 0)
		return;

	vector<int> a(n);
	vector<int> c(n);
	vector<double> b(n);

	vector<vector<double>> matrix = getRandMatrix(n, 0, buff);
	
	matrixOut(matrix, n);

	for (j = 0; j < n; j++)
	{
		a[j] = 0;
		c[j] = i;
		b[j] = matrix[i][j];
	}

	a[3] = 1;
	c[3] = 0;

	for (int m = 0; m < n; m++)
	{
		minValue = buff;
		for (int k = 0; k < n; k++)
			if ((a[k] == 0) && (b[k] < minValue))
			{
				j = k;
				minValue = b[k];
			}
		cout << "\n  Min value = " << minValue << " \tj = " << j;
		a[j] = 1;
		for (int k = 0; k < n; k++)
			if (b[k] > b[j] + matrix[j][k])
			{
				b[k] = b[j] + matrix[j][k];
				cout << "\n  k = " << k << "\tb[k] = " << b[k];
				c[k] = j;
			}
		cout << endl;
	}

	for (int k = 0; k < n; k++)
	{
		z = c[k];
		cout << "\n  k = " << k << " |";
		while (z != 0)
		{
			cout << " " << z;
			z = c[z];
		}
	}
	cout << "\n\n";
}

void primsAlgorithm() 
{
	int n = getGraphSize(1);
	if (n < 0)
		return;

	int m, j, j1, i, i1;
	double minValue, buff, L = 0.0;

	vector<vector<double>> matrix = getRandMatrix(n, 1, buff);

	matrixOut(matrix, n);

	vector<int> col (n);
	vector<vector<int>> result(2, vector<int>(n));

	for (i = 0; i < n; i++)
		col[i] = i;

	for (int k = 0; k < n - 1; k++)
	{
		minValue = buff;

		for (i1 = 0; i1 < n - 1; i1++)
			for (j1 = i1 + 1; j1 < n; j1++)
				if (matrix[i1][j1] < minValue && col[i1] != col[j1])
				{
					minValue = matrix[i1][j1];
					i = i1;
					j = j1;
				}

		L += minValue;
		result[0][k] = i;
		result[1][k] = j;

		j1 = col[j];
		for (m = 1; m < n; m++)
			if (col[m] == j1)
				col[m] = col[i];
	}

	cout << endl;
	for (i = 0; i < n - 1; i++)
		cout <<"  " << result[0][i] << " | " << result[1][i] << endl;
	cout << "\n  L = " << L << "\n\n";
}

void algorithmChoise()
{
	int n = 0;
	char answer = ' ';

	cout << "----------------------------------------------------------\n\n";

	cout << "Choose Algorithm.\n 1. Dijkstra's algorithm\n";
	cout << " 2. Prim's algorithm\nOr type any other symbol to stop program.\n";
	cout << "Your choice : ";
	cin >> answer;

	switch (answer) {
	default:
		return;
		break;
	case '1':
		dijkstrasAlgorithm();
		break;
	case '2':
		primsAlgorithm();
		break;
	}

	algorithmChoise();
}

int main()
{
	srand(time(NULL));

	algorithmChoise();
}