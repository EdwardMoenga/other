// Using the 'while' logical loop construct

#include <iostream>
using namespace std;

int main()
{
	// initialize output matrix
	int product[10][10], r1 = 3, c1 = 3, r2 = 3, c2 = 3, i, j, k;
	// initialize first matrix
	int a[3][3] = {{7, 4, 9}, {2, 1, 6}, {3, 5, 8}};
	// initialize second matrix
	int b[3][3] = {{5, 2, 8}, {3, 6, 1}, {9, 4, 7}};

	// Check if matrix rows and columns
	if (c1 != r2)
	{
		cout << "Columns of the first matrix should be equal to the rows of the second matrix";
	}
	else
	{
		// display first matrix
		cout << "First matrix:" << endl;
		i = 0;
		while (i < r1)
		{
			j = 0;
			while (j < c1)
			{
				cout << a[i][j] << " ";
				j++;
			}
			cout << endl;
			i++;
		}
		cout << endl;

		// display second matrix
		cout << "Second matrix:" << endl;
		i = 0;
		while (i < r2)
		{
			j = 0;
			while (j < c2)
			{
				cout << b[i][j] << " ";
				j++;
			}
			cout << endl;
			i++;
		}
		cout << endl;

		// initialize elements of matrix multiplication to 0
		i = 0;
		while (i < r1)
		{
			j = 0;
			while (j < c2)
			{
				product[i][j] = 0;
				j++;
			}
			i++;
		}

		// multiply first matrix and second matrix and store result in array
		i = 0;
		while (i < r1)
		{
			j = 0;
			while (j < c2)
			{
				k = 0;
				while (k < c1)
				{
					product[i][j] += a[i][k] * b[k][j];
					k++;
				}
				j++;
			}
			i++;
		}

		// display product matrix
		cout << "Product:" << endl;
		i = 0;
		while (i < r1)
		{
			j = 0;
			while (j < c2)
			{
				cout << product[i][j] << " ";
				j++;
			}
			cout << endl;
			i++;
		}
	}

	system("pause");

	return 0;
}