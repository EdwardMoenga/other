// Using the 'for' counting loop construct

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
      for (i = 0; i < r1; ++i)
      {
         for (j = 0; j < c1; ++j)
            cout << a[i][j] << " ";
         cout << endl;
      }
      cout << endl;

      // display second matrix
      cout << "Second matrix:" << endl;
      for (i = 0; i < r2; ++i)
      {
         for (j = 0; j < c2; ++j)
            cout << b[i][j] << " ";
         cout << endl;
      }
      cout << endl;

      // initialize elements of matrix multiplication to 0
      for (i = 0; i < r1; ++i)
      {
         for (j = 0; j < c2; ++j)
            product[i][j] = 0;
      }

      // multiply first matrix and second matrix and store result in array
      for (i = 0; i < r1; ++i)
      {
         for (j = 0; j < c2; ++j)
         {
            for (k = 0; k < c1; ++k)
               product[i][j] += a[i][k] * b[k][j];
         }
      }

      // display product matrix
      cout << "Product:" << endl;
      for (i = 0; i < r1; ++i)
      {
         for (j = 0; j < c2; ++j)
            cout << product[i][j] << " ";
         cout << endl;
      }
   }

   system("pause");

   return 0;
}