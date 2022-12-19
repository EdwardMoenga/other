/*******************************************************************
** Program: text_adventure.cpp
** Author: Your Name
** Date: 11/20/2022
** Description: The local middle school would like some text adventure games to keep their students occupied during down time. During your adventure game, you must get at least 5 user inputs. Create variables to store them. There must be at least two paths, with each has a depth of 3 (an if with a nested if that has a nested if) to complete the adventure, and there needs to be at least 2 options with each decision.
** Input: Users choices
** Output: Choice results
*******************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	cout << "##############################" << endl;
	cout << "# The game of Text Adventure #" << endl;
	cout << "##############################" << endl;
	cout << endl;

	int choice1, choice3;
	double wHeight, wWeight, wBMI;

	string choice2, playagain = "yes";

	do
	{
		cout << "Hello and welcome to the adventure!";

		cout << "\nThere are two ways in front of you. To go right enter 1, to go left enter 2: ";
		cin >> choice1;
		if (cin.fail())
		{
			cout << "\nData type error!";
			return 0;
		}
		else
		{
			if ((choice1 != 1) && (choice1 != 2))
			{
				cout << "\nInvalid choice!";
			}
			else
			{
				if (choice1 == 1)
				{
					cout << "\nYou chose to go right. \nYou have now entered Scandinavia and are being hunted by friendly oxen.";

					cout << "\nEnter b to be friend with the oxen, enter r to run from the oxen: ";
					cin >> choice2;
					if (cin.fail())
					{
						cout << "\nData type error!";
						return 0;
					}
					else
					{
						if ((choice2 != "b") && (choice2 != "r"))
						{
							cout << "\nInvalid choice!";
						}
						else
						{
							if (choice2 == "b")
							{
								cout << "\nYou attempted to be friend with the oxen. You think you can ride them.";

								cout << "\nEnter 1 to attempt to ride the oxen, enter 2 to walk away: ";
								cin >> choice3;
								if (cin.fail())
								{
									cout << "\nData type error!";
									return 0;
								}
								else
								{
									if ((choice3 != 1) && (choice3 != 2))
									{
										cout << "\nInvalid choice!";
									}
									else
									{
										if (choice3 == 1)
										{
											int iseed = time(NULL);
											srand(iseed);
											int randomNum = rand();
											cout << "\nRandom number = " << randomNum << "\n";

											if (randomNum % 2 == 0)
											{
												cout << "\nUnfortunately, fate was not on your side, and you are forced to walk away. \n:-(";
											}
											else
											{
												cout << "\nYeee Haaa!! Gitty up...";
											}
										}
										else
										{
											cout << "\nRealy? Walk away? I thought you had the b**ls \n:-(";
										}
									}
								}
							}
							else
							{
								cout << "\nRun oh cowardley one, RUN!! \n:-o";
							}
						}
					}
				}
				else
				{
					cout << "\nYou chose to go left. \nYou have now entered America and are fighting a strong warrior.";

					cout << "\nWhat is your height in meters? ";
					cin >> wHeight;
					if (cin.fail())
					{
						cout << "\nData type error!";
						return 0;
					}
					cout << "\nWhat is your weight in kilograms? ";
					cin >> wWeight;
					if (cin.fail())
					{
						cout << "\nData type error!";
						return 0;
					}

					wBMI = ((wWeight / wHeight) / wHeight);

					if ((wBMI >= 18.5) && (wBMI <= 24.9))
					{
						cout << "\nYour BMI (body mass index) is " << wBMI << ", which is normal weight, you beat the warrior and went home. \n:-)" << endl;
					}
					else
					{
						cout << "\nYour BMI (body mass index) is " << wBMI << ", you are not fit enough to face the warrior. \n:-(" << endl;
					}
				}
			}
		}

		cout << "\nThe adventure has ended." << endl;

		cout << "\n\nDo you want to try again? (yes/no) ";
		cin >> playagain;
	} while (playagain != "no");

	return 0;
}