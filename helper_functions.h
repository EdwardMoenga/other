/*******************************************************************
** Program: helper_function.h
** Author: Your Name
** Date: 11/20/2022
** Description: Creating a header file for helper functions
** Input:
** Output:
*******************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// function prototypes
bool check_range(int, int, int);
int equality_test(int, int);
bool is_int(string);
bool is_float(string);
void string_to_int(string, int &);
void swap(int &, int &);
int word_count(string);

bool check_range(int lower_bound, int upper_bound, int test_value)
{
	if ((test_value <= upper_bound) && (test_value >= lower_bound))
		return true;
	else
		return false;
}

int equality_test(int num1, int num2)
{
	if (num1 < num2)
		return -1;
	if (num1 == num2)
		return 0;
	if (num1 > num2)
		return 1;
}

bool is_int(string num)
{
	for (int i = 0; i < num.length(); i++)
		if (isdigit(num[i]) == false)
			return false;

	return true;
}

bool is_float(string num)
{
	if (std::stof(num))
		return true;

	return false;
}

void string_to_int(string num, int &value)
{
	value = stoi(num);

	return;
}

void swap(int &num1, int &num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;

	return;
}

int word_count(string sentence)
{

	int words = 0;

	int lenOfSentence = sentence.size();

	for (int i = 0; i < lenOfSentence; i++)
	{
		if (sentence[i] == ' ')
		{
			words++;
		}
	}

	return words + 1;
}
