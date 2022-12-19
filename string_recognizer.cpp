#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    int state = 0, i, len;
    string theString;
    cout << "Input: ";
    cin >> theString;
    len = theString.size();
    for (i = 0; i < len; i++)
    {
        if (state == 0 || state == 1 && theString[i] == 'a')
            state = 0;
        else if (state == 0 || state == 1 && theString[i] == 'b')
            state = 1;
        else if (state == 1 && theString[i] == 'a')
        {
            state = 2;
            break;
        }
        else if (theString[i] != 'a' || theString[i] != 'b')
        {
            state = 2;
            break;
        }
    }
    if (state == 1)
        cout << "'" << theString << "' is accepted under rule 'a*b+'" << endl;
    else
        cout << "'" << theString << "' is not recognized" << endl;

    system("pause");
}