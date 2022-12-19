#include <iostream>
using namespace std;

int main()
{
	string calculateagain = "yes";
	int n, i, max, min;

	do
	{
		cout << "Enter an array size between 1 and 20: ";
		cin >> n;
		int arr[n];
		if (cin.fail())
		{
			cout << "\nError! Enter integers only.";
			return 0;
		}
		else
		{

			for (i = 0; i < n; i++)
			{
				arr[i] = rand() % 100 + 1;
			}
			max = arr[0];
			for (i = 0; i < n; i++)
			{
				if (max < arr[i])
					max = arr[i];
			}
			min = arr[0];
			for (i = 0; i < n; i++)
			{
				if (min > arr[i])
					min = arr[i];
			}
			cout << "Largest element : " << max << "\n";
			cout << "Smallest element : " << min << "\n\n";
			cout << "First element : " << arr[n - 1] << "\n";
			cout << "Last element : " << arr[0] << "\n";
			cout << "All the array elements : "
				 << "\n";
			for (int i = n - 1; i >= 0; i--)
				cout << arr[i] << ", ";
		}
		cout << "\n"
			 << endl;

		cout << "Do you want to calculate again? (yes/no) ";
		cin >> calculateagain;
	} while (calculateagain != "no");
	return 0;
}