/*******************************************************************
** Program: Monthly Mortgage Calculator
** Author: Your Name
** Date: 11/20/2022
** Description: For many of the millions of Americans carrying a mortgage or planning to own a home, calculating monthly mortgage payment is a necessary step. However, this monthly payment includes many parts, and the calculation can be time-consuming for many people. Thus, you are tasked to write a program to estimate the monthly mortgage payment for the user based on their inputs (Assuming fix-rate mortgage, which means pay the same amount each month). Additionally, the program needs to output
the total mortgage paid, principal paid, and interest paid at the end.
** Input:
• Home price (in dollars)
• Down payment (in dollars)
• Length of loan (in years)
• Annual interest rate (in percentage)
** Output:
• Monthly mortgage payment
• Total paid
• Principle paid
• Interest paid
*******************************************************************/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

double home_price, down_payment, loan_length, annual_interest_rate;
double mortgage_principal, monthly_interest_rate, monthly_payments, monthly_mortgage, total_paid, interest_paid;

void calculate_mortgage(double home_price, double down_payment, double loan_length, double annual_interest_rate)
{
	mortgage_principal = (home_price - down_payment);
	monthly_interest_rate = ((annual_interest_rate / 100) / 12);
	monthly_payments = (loan_length * 12);
	monthly_mortgage = ((mortgage_principal * (monthly_interest_rate * pow((1 + monthly_interest_rate), monthly_payments))) / (pow((1 + monthly_interest_rate), monthly_payments) - 1));
	total_paid = (monthly_mortgage * monthly_payments);
	interest_paid = (total_paid - mortgage_principal);
}

int main()
{
	int rslt;
	string calculateagain = "yes";

	do
	{
		cout << "Hello and welcome to the mortgage calculator!";

		cout << "\nEnter the home price, in dollars: ";
		cin >> home_price;
		if (cin.fail())
		{
			cout << "\nError! Enter float type values only.";
			return 0;
		}
		else
		{
			cout << "\nEnter the down payment, in dollars: ";
			cin >> down_payment;
			if (cin.fail())
			{
				cout << "\nError! Enter float type values only.";
				return 0;
			}
			else
			{
				cout << "\nEnter the length of loan, in years: ";
				cin >> loan_length;
				if (cin.fail())
				{
					cout << "\nError! Enter float type values only.";
					return 0;
				}
				else
				{
					cout << "\nEnter the Annual Interest Rate, in percentage: ";
					cin >> annual_interest_rate;
					if (cin.fail())
					{
						cout << "\nError! Enter float type values only.";
						return 0;
					}
					else
					{
					}
				}
			}
		}

		calculate_mortgage(home_price, down_payment, loan_length, annual_interest_rate);
		cout << "\nYour estimated monthly payment is: " << monthly_mortgage;
		cout << "\nTotal paid: " << total_paid;
		cout << "\nPrincipal paid: " << mortgage_principal;
		cout << "\nInterest paid: " << interest_paid;
		cout << "\n\nThank you for using the mortgage calculator.";
		cout << endl;

		cout << "\n\nDo you want to calculate again? (yes/no) ";
		cin >> calculateagain;
	} while (calculateagain != "no");
	return 0;
}