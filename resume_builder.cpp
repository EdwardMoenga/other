/*******************************************************************
** Program: resume_builder.cpp
** Author: Your Name
** Date: 12/04/2022
** Description: Create a resume file based on the users input data. The output is a text tile named after the user's input name.
** Input: first name, last name, E-mail address, University/College, Major, Graduation year, GPA, Company/Employer, start date, end date, description, Work Experience
** Output: A text file named after the first name and last name containing all the input data and well formated
*******************************************************************/

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

// structs to be used
struct Edu
{
	char univ[128];	   // a c-string for university name
	char major[64];	   // a c-string for the major
	int graduate_year; // graduation year
	float GPA;		   // GPA
};

struct Basics
{
	char fname[64]; // a c-string for first name
	char lname[64]; // a c-string for last name
	char email[64]; // a c-string for email address
	Edu edu;		// an Edu object for ed. background
};

struct Exp
{
	char company[64];	 // a c-string for company name
	char start_date[64]; // a c-string for start date
	char end_date[64];	 // a c-string for end date
	char des[1024];		 // the description of the work experience
};

void get_skills(string sk[], int sk_size, int *sCount)
{
	int skillCount = 0;
	string temp = "";
	cout << "\nEnter your skills, one at a time : (Enter '.' to stop entering skills) " << endl;
	while (temp[0] != '.')
	{
		getline(cin, temp);
		sk[skillCount] = temp;
		skillCount++;
	}
	*sCount = skillCount - 1;
}

bool validateDate(string temp)
{
	if (isdigit(temp[0]) && (isdigit(temp[1])) && (temp[2] == '-') && (isdigit(temp[3])) && (isdigit(temp[4])) && (temp[5] == '-') && (isdigit(temp[6])) && (isdigit(temp[7])))
		return true;
	return false;
}

bool validateEmail(string temp)
{
	bool check_a = false;
	bool check_dot = false;
	for (char i : temp)
	{
		if (i == '@')
			check_a = true;
		if (i == '.')
			check_dot = true;
	}
	return check_a && check_dot;
}

void get_basics_and_edu(Basics *bc, Edu *ed)
{
	string temp;

	cout << "\nEnter your first name : ";
	getline(cin, temp);
	strcpy(bc->fname, temp.c_str());

	cout << "Enter your last name : ";
	getline(cin, temp);
	strcpy(bc->lname, temp.c_str());

	while (true)
	{
		cout << "Enter your E-mail address : ";
		getline(cin, temp);
		if (validateEmail(temp))
		{
			strcpy(bc->email, temp.c_str());
			break;
		}
		else
		{
			cout << "E-mail not valid! Try again." << endl;
		}
	}

	cout << "\nEnter your University/College : ";
	getline(cin, temp);
	strcpy(ed->univ, temp.c_str());

	cout << "Enter your Major : ";
	getline(cin, temp);
	strcpy(ed->major, temp.c_str());

	cout << "Enter your Graduation year : ";
	cin >> ed->graduate_year;
	cout << "Enter your GPA : ";
	cin >> ed->GPA;
	cin.ignore(1, '\n');
}

void get_one_exp(Exp *ex)
{
	string temp;
	cout << "\nEnter your Company/Employer : ";
	getline(cin, temp);
	strcpy(ex->company, temp.c_str());

	while (true)
	{
		cout << "Enter start date in dd-mm-yy format : ";
		getline(cin, temp);
		if (validateDate(temp))
		{
			strcpy(ex->start_date, temp.c_str());
			break;
		}
		else
		{
			cout << "\nDate not valid! Try again." << endl;
		}
	}

	while (true)
	{
		cout << "Enter end date in dd-mm-yy format : ";
		getline(cin, temp);
		if (validateDate(temp))
		{
			strcpy(ex->end_date, temp.c_str());
			break;
		}
		else
		{
			cout << "\nDate not valid! Try again." << endl;
		}
	}

	cout << "Enter description : ";
	getline(cin, temp);
	if (temp == "")
		strcpy(ex->des, "None");
	else
		strcpy(ex->des, temp.c_str());
}

void get_exp(Exp ex[], int ex_size, int *eCount)
{
	int expCount = 0;
	char conf;

	cout << "\nWork Experience : " << endl;
	while (true)
	{
		get_one_exp(&(ex[expCount]));
		expCount++;
		if (expCount == ex_size)
			break;
		cout << "\nDo you want to add more experiences? (y / n) : ";
		cin >> conf;
		cin.ignore(1, '\n');
		if (tolower(conf) != 'y')
			break;
	}
	*eCount = expCount;
}

void build_resume(ofstream &f, Basics b, Exp ex[], int ex_size, string sk[], int sk_size, Edu e)
{
	f << string(100, '-') << endl;
	f << string(25, ' ') << string(5, '=') << "   " << b.fname << " " << b.lname << " RESUME   " << string(5, '=') << endl;
	f << "\n\n\tBasic Information :- " << endl
	  << endl;
	f << setw(35) << "First Name "
	  << ": " << b.fname << endl;
	f << setw(35) << "Last Name "
	  << ": " << b.lname << endl;
	f << setw(35) << "Email Address "
	  << ": " << b.email << endl;

	f << "\n\n\tEducation Background :- " << endl
	  << endl;
	f << setw(35) << "University/College "
	  << ": " << e.univ << endl;
	f << setw(35) << "Major "
	  << ": " << e.major << endl;
	f << setw(35) << "Graduation year "
	  << ": " << e.graduate_year << endl;
	f << setw(35) << "GPA "
	  << ": " << e.GPA << endl;

	f << "\n\n\tWork Experience :- " << endl;
	for (int i = 0; i < ex_size; i++)
	{
		f << endl;
		f << setw(15) << i + 1 << "." << endl;
		f << setw(35) << "Company/Employer "
		  << ": " << ex[i].company << endl;
		f << setw(35) << "Start date "
		  << ": " << ex[i].start_date << endl;
		f << setw(35) << "End date "
		  << ": " << ex[i].end_date << endl;
		f << setw(35) << "Description "
		  << ": " << ex[i].des << endl;
	}

	f << "\n\n\tSkills  :- " << endl;
	for (int i = 0; i < sk_size; i++)
	{
		// f << endl;
		f << setw(15) << i + 1 << ". ";
		f << sk[i] << endl;
	}
}

int main()
{
	struct Exp *ex = new Exp[5];
	struct Basics bc;
	struct Edu ed;
	string *skills = new string[10];
	int skillCount = 0;
	int expCount = 0;

	get_basics_and_edu(&bc, &ed);
	get_exp(ex, 5, &expCount);
	get_skills(skills, 10, &skillCount);

	string ext = ".txt";
	string filename = bc.fname + bc.lname + ext;

	ofstream f;
	f.open(filename);
	build_resume(f, bc, ex, expCount, skills, skillCount, ed);
	f.close();

	delete[] ex;
	delete[] skills;
}