/*******************************************************************
** Program: fraction.cpp
** Author: Your Name
** Date: 11/20/2022
** Description: Get the GCD of two numbers and print their values as fractions
** Input:
** Output:
*******************************************************************/

#include <iostream>
#include <algorithm>

using namespace std;

int gCD(int, int);
bool to_lowest_terms(int &, int &);

int gCD(int a, int b)
{
	return __gcd(a, b);
}

bool to_lowest_terms(int &numerator, int &denominator)
{
	if (denominator == 0)
	{
		cout << "\nError! Invalid denominator";
		return false;
	}

	rslt = gCD(numerator, denominator);

	numerator = numerator / rslt;
	denominator = denominator / rslt;

	return true;
}

int main()
{
	int rslt;
	string calculateagain = "yes";

	do
	{
		int num1, num2;

		cout << "Enter Two Numbers: ";
		cin >> num1 >> num2;
		if (cin.fail())
		{
			cout << "\nError! Enter integers only.";
			return 0;
		}
		else
		{
			if (to_lowest_terms(num1, num2))
			{
				cout << "\nResult = " << (num1) << "/" << (num2);
			}
			else
			{
				cout << "\nError!";
			}
		}
		cout << endl;

		cout << "Do you want to calculate again? (yes/no) ";
		cin >> calculateagain;
	} while (calculateagain != "no");
	return 0;
}