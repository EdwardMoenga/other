#include <iostream>
using namespace std;

bool checkInteger(string input)
{
	bool isNeg = false;
	int itr = 0;
	if (input.size() == 0)
		return false;
	if (input[0] == '-')
	{
		isNeg = true;
		itr = 1;
	}

	for (int i = itr; i < input.size(); i++)
	{
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

int main()
{
	string calculateagain = "yes";
	int nScores = 0, iScore, i;
	double result = 0, avg = 0;
	bool isValid = true;

	do
	{
		do
		{
			isValid = true;
			cout << "Input number of scores: ";
			cin >> nScores;
			bool isInt = checkInteger(nScores);
			if (isInt)
			{
				cout << "\nError! Enter integers only.";
				isValid = false;
			}
		} while (isValid == false);

		for (i = 0; i < nScores; i++)
		{
			do
			{
				isValid = true;
				cout << "\nInput score between 1 and 100: ";
				cin >> iScore;
				if (cin.fail())
				{
					cout << "\nError! Enter integers only.";
					isValid = false;
				}
				if ((iScore < 0) || (iScore > 100))
				{
					cout << "\nError! Enter score between 1 and 100";
					isValid = false;
				}
			} while (isValid == false);

			result = (result + iScore);
		}

		if (nScores > 0)
		{
			avg = (result / nScores);
		}

		cout << "\nYour average : " << avg << "\n"
			 << endl;

		cout << "Do you want to calculate again? (yes/no) ";
		cin >> calculateagain;
	} while (calculateagain != "no");
	return 0;
}